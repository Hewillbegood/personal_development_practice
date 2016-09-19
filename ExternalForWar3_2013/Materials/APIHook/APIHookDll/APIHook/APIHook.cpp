
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

// ��ʼ����̬��Ա
CAPIHook* CAPIHook::m_spHead = NULL;

CAPIHook CAPIHook::m_sLoadLibraryA("Kernel32.dll","LoadLibraryA",(PROC)CAPIHook::LoadLibraryA,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryW("Kernel32.dll","LoadLibraryW",(PROC)CAPIHook::LoadLibraryW,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryExA("Kernel32.dll","LoadLibraryExA",(PROC)CAPIHook::LoadLibraryExA,TRUE);
CAPIHook CAPIHook::m_sLoadLibraryExW("Kernel32.dll","LoadLibraryExW",(PROC)CAPIHook::LoadLibraryExW,TRUE);
CAPIHook CAPIHook::m_sGetProcAddress("Kernel32.dll","GetProcAddress",(PROC)CAPIHook::GetProcAddress,TRUE);


CAPIHook::CAPIHook(PSTR pchModName,PSTR pchFuncName,PROC pfnHookAddress,BOOL bInner) 
{
	// ���Լ����뵽�ҹ��б��ͷ����ͬʱNextָ���¼��һ��
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
		// ������ģ���IAT���е�ԭʼ��ַ����Hook�����ĵ�ַ
		ReplaceAllModules(m_pchModName,m_pfnRealAddress,m_pfnHookAddress);
	}
}

CAPIHook::~CAPIHook() 
{
	// ������ģ���IAT���е�Hook�����ĵ�ַ����ԭʼ��ַ����ԭIAT��
	ReplaceAllModules(m_pchModName,m_pfnHookAddress,m_pfnRealAddress);

	// �ӹҹ��б�������Լ�
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

// �滻����ģ���IAT��
void CAPIHook::ReplaceAllModules(PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress) 
{
	HMODULE hThisModule = ModuleFromAddress(ReplaceAllModules);

	// ��������������ģ��
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,GetCurrentProcessId());
	if(hSnapshot==INVALID_HANDLE_VALUE) return ;

	MODULEENTRY32 sModItem = {sizeof(sModItem)};
	if(::Module32First(hSnapshot,&sModItem))
	{
		do
		{
			// ������жϣ����ų��Ե�ǰģ���API hook,һ������£����ǻ�Ѹ�API hook�Ĵ������һ��������dll�С�
			if(sModItem.hModule!=hThisModule)
			{
				// �滻ģ���IAT
				ReplaceModule(sModItem.hModule,pchModName,pfnRealAddress,pfnHookAddress);
			}
		}
		while(::Module32Next(hSnapshot,&sModItem));
	}

	::CloseHandle(hSnapshot);
}

// �滻ָ��ģ���IAT��
void CAPIHook::ReplaceModule(HMODULE hModule,PCSTR pchModName,PROC pfnOld, PROC pfnNew) 
{
	ULONG ulSize;

	USES_CONVERSION ;

	// ��λģ��ĵ����
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc = NULL;
	pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule,TRUE,IMAGE_DIRECTORY_ENTRY_IMPORT,&ulSize);

	// û�е���� 
	if(pImportDesc==NULL) return;

	// ����ģ����Ϣ
	for(; pImportDesc->Name; pImportDesc++)
	{
		PSTR pszModName = (PSTR)((PBYTE)hModule + pImportDesc->Name);

		// �ҵ�ҪHook��ģ��
		if(lstrcmpiA(pszModName,pchModName)==0) 
		{
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImportDesc->FirstThunk);

			// ������ģ��ʹ�õ���API
			for(;pThunk->u1.Function;pThunk++) 
			{
				PROC* ppfn = (PROC*)&pThunk->u1.Function;
				BOOL bFound = (*ppfn == pfnOld);

				// �ҵ�������ҪHook��API��
				if(bFound) 
				{					
					// �滻IAT�еĵ�ַ
					if(!WriteProcessMemory(GetCurrentProcess(),ppfn,&pfnNew,sizeof(pfnNew),NULL))
					{
						// �滻ʧ��
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

// ������ģ�����������ʱ�򣬸�������ģ���IAT
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

// ��⵽����ģ�������������������ģ���IAT 
HMODULE WINAPI CAPIHook::LoadLibraryA(PCSTR pszModulePath) 
{
	HMODULE hModule = ::LoadLibraryA(pszModulePath);
	UpdateModules(hModule, 0);
	return (hModule);
}

// ��⵽����ģ�������������������ģ���IAT 
HMODULE WINAPI CAPIHook::LoadLibraryW(PCWSTR pszModulePath) 
{
	HMODULE hModule = ::LoadLibraryW(pszModulePath);
	UpdateModules(hModule, 0);
	return (hModule);
}

// ��⵽����ģ�������������������ģ���IAT 
HMODULE WINAPI CAPIHook::LoadLibraryExA(PCSTR pszModulePath,HANDLE hFile,DWORD dwFlags) 
{
	HMODULE hModule = ::LoadLibraryExA(pszModulePath, hFile, dwFlags);
	UpdateModules(hModule, dwFlags);
	return (hModule);
}

// ��⵽����ģ�������������������ģ���IAT 
HMODULE WINAPI CAPIHook::LoadLibraryExW(PCWSTR pszModulePath,HANDLE hFile,DWORD dwFlags) 
{
   HMODULE hModule = ::LoadLibraryExW(pszModulePath, hFile, dwFlags);
   UpdateModules(hModule, dwFlags);
   return (hModule);
}

// ��ͨ��GetProcAddress��ȡ������ַʱ�����ж��Ƿ��������Ѿ������˵�
// ����Ѿ��ڹ����б����ˣ�ֱ�ӷ��ع��ӵ�ַ
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
