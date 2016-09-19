
#include "stdafx.h"
#include "APIHook.h"
#include <StrSafe.h>
#include <Tlhelp32.h>
#include <atlconv.h>

#include <ImageHlp.h>
#pragma comment(lib, "ImageHlp")

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

// 初始化静态成员
CAPIHook* CAPIHook::m_spHead = NULL;

CAPIHook CAPIHook::m_sLoadLibraryA("Kernel32.dll","LoadLibraryA",(PROC)CAPIHook::LoadLibraryA,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryW("Kernel32.dll","LoadLibraryW",(PROC)CAPIHook::LoadLibraryW,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryExA("Kernel32.dll","LoadLibraryExA",(PROC)CAPIHook::LoadLibraryExA,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryExW("Kernel32.dll","LoadLibraryExW",(PROC)CAPIHook::LoadLibraryExW,TRUE);
CAPIHook CAPIHook::m_sGetProcAddress("Kernel32.dll","GetProcAddress",(PROC)CAPIHook::GetProcAddress,TRUE);


CAPIHook::CAPIHook(PSTR pchModName,PSTR pchFuncName,PROC pfnHookAddress,BOOL bInner) 
{
	// 把自己插入到挂钩列表的头部，同时Next指针记录下一个
	m_pNext  = m_spHead;
	m_spHead = this;

	m_bInner = bInner ;
	m_pchModName     = pchModName;
	m_pchFuncName    = pchFuncName;
	m_pfnHookAddress = pfnHookAddress;

	HINSTANCE hModInst = ::LoadLibraryA(m_pchModName);
	m_pfnRealAddress = ::GetProcAddress(hModInst, m_pchFuncName);

    if(m_pfnRealAddress)
	{
		// 把所有模块的IAT表中的原始地址换成Hook函数的地址
		ReplaceAllModules(m_pchModName,m_pfnRealAddress,m_pfnHookAddress);
	}
}

CAPIHook::~CAPIHook() 
{
	// 把所有模块的IAT表中的Hook函数的地址换成原始地址，还原IAT表
	ReplaceAllModules(m_pchModName,m_pfnHookAddress,m_pfnRealAddress);

	// 从挂钩列表中清除自己
	CAPIHook* pTemp = m_spHead; 
	if(pTemp == this) 
	{
		m_spHead = pTemp->m_pNext; 
	}
	else 
	{
		for(;(pTemp->m_pNext!=NULL);pTemp=pTemp->m_pNext) 
		{
			if(pTemp->m_pNext == this) 
			{ 
				pTemp->m_pNext = pTemp->m_pNext->m_pNext; 
				break;
			}
		}
	}
}

PROC CAPIHook::GetRealFunc()
{
	return m_pfnRealAddress;
}

HMODULE CAPIHook::ModuleFromAddress(PVOID pv) 
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((VirtualQuery(pv,&mbi,sizeof(mbi))!=0)?(HMODULE)mbi.AllocationBase:NULL);
}

// 替换所有模块的IAT表
void CAPIHook::ReplaceAllModules(PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress) 
{
	HMODULE hThisModule = ModuleFromAddress(ReplaceAllModules);

	// 遍历进程中所有模块
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetCurrentProcessId());
	if(hSnapshot==INVALID_HANDLE_VALUE) return ;

	MODULEENTRY32 sModItem = {sizeof(sModItem)};
	if(::Module32First(hSnapshot,&sModItem))
	{
		do
		{
			// 下面的判断，是排除对当前模块的API hook,一般情况下，我们会把该API hook的代码放在一个独立的dll中。
			if(sModItem.hModule!=hThisModule)
			{
				// 替换模块的IAT
				ReplaceModule(sModItem.hModule,pchModName,pfnRealAddress,pfnHookAddress);
			}
		}
		while(::Module32Next(hSnapshot,&sModItem));
	}

	::CloseHandle(hSnapshot);
}

// 替换指定模块的IAT表
void CAPIHook::ReplaceModule(HMODULE hModule,PCSTR pchModName,PROC pfnOld, PROC pfnNew) 
{
	ULONG ulSize;

	USES_CONVERSION ;

	// 定位模块的导入段
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = NULL;
	pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule,TRUE,IMAGE_DIRECTORY_ENTRY_IMPORT,&ulSize);

	// 没有导入段 
	if(pImportDesc==NULL) return;

	// 遍历模块信息
	for(; pImportDesc->Name; pImportDesc++)
	{
		PSTR pszModName = (PSTR)((PBYTE)hModule + pImportDesc->Name);

		// 找到要Hook的模块
		if(lstrcmpiA(pszModName,pchModName)==0) 
		{
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImportDesc->FirstThunk);

			// 遍历该模块使用到的API
			for(;pThunk->u1.Function;pThunk++) 
			{
				PROC* ppfn = (PROC*)&pThunk->u1.Function;
				BOOL bFound = (*ppfn == pfnOld);

				// 找到我们需要Hook的API项
				if(bFound) 
				{					
					// 替换IAT中的地址
					if(!WriteProcessMemory(GetCurrentProcess(),ppfn,&pfnNew,sizeof(pfnNew),NULL))
					{
						// 替换失败
						if(GetLastError()==ERROR_NOACCESS)
						{
							DWORD dwOldProtect;
							if(VirtualProtect(ppfn, sizeof(pfnNew), PAGE_WRITECOPY,&dwOldProtect)) 
							{
								WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew,sizeof(pfnNew), NULL);
								VirtualProtect(ppfn, sizeof(pfnNew), dwOldProtect,&dwOldProtect);
							}
						}
					}
					return;
				}
			}
		}
	}
}

//============================================================================================
//============================================================================================

// 再有新模块加载起来的时候，更新所有模块的IAT
void CAPIHook::UpdateModules(HMODULE hModule,DWORD dwFlags) 
{
	if ((hModule != NULL) &&
        (hModule != ModuleFromAddress(UpdateModules)) && 
        ((dwFlags & LOAD_LIBRARY_AS_DATAFILE) == 0)
       ) 
	{
		for(CAPIHook* pTemp=m_spHead;pTemp!=NULL;pTemp=pTemp->m_pNext) 
		{
			if(pTemp->m_pfnRealAddress != NULL) 
			{
				if(pTemp->m_bInner==FALSE)
				{
					ReplaceModule(hModule,pTemp->m_pchModName,pTemp->m_pfnRealAddress,pTemp->m_pfnHookAddress);  
				}
			}
		}
	}
}

// 检测到有新模块加载起来，更新所有模块的IAT 
HMODULE WINAPI CAPIHook::LoadLibraryA(PCSTR pszModulePath) 
{
	HMODULE hModule = ::LoadLibraryA(pszModulePath);
	UpdateModules(hModule, 0);
	return (hModule);
}

// 检测到有新模块加载起来，更新所有模块的IAT 
HMODULE WINAPI CAPIHook::LoadLibraryW(PCWSTR pszModulePath) 
{
	HMODULE hModule = ::LoadLibraryW(pszModulePath);
	UpdateModules(hModule, 0);
	return (hModule);
}

// 检测到有新模块加载起来，更新所有模块的IAT 
HMODULE WINAPI CAPIHook::LoadLibraryExA(PCSTR pszModulePath,HANDLE hFile,DWORD dwFlags) 
{
	HMODULE hModule = ::LoadLibraryExA(pszModulePath, hFile, dwFlags);
	UpdateModules(hModule, dwFlags);
	return (hModule);
}

// 检测到有新模块加载起来，更新所有模块的IAT 
HMODULE WINAPI CAPIHook::LoadLibraryExW(PCWSTR pszModulePath,HANDLE hFile,DWORD dwFlags) 
{
   HMODULE hModule = ::LoadLibraryExW(pszModulePath, hFile, dwFlags);
   UpdateModules(hModule, dwFlags);
   return (hModule);
}

// 当通过GetProcAddress获取导出地址时，先判断是否是我们已经拦截了的
// 如果已经在钩子列表中了，直接返回钩子地址
FARPROC WINAPI CAPIHook::GetProcAddress(HMODULE hModule, PCSTR pchProcName) 
{
	FARPROC pfn = ::GetProcAddress(hModule, pchProcName);

	CAPIHook* pTemp = m_spHead;
	for(;(pfn != NULL)&&(pTemp != NULL);pTemp=pTemp->m_pNext) 
	{
		if(pfn == pTemp->m_pfnRealAddress)
		{
			pfn = pTemp->m_pfnHookAddress;
			break;
		}
   }
   return (pfn);
}
