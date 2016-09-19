
#pragma once

class CAPIHook 
{
public:
	//=======================================================================
	//== 在这里把钩子挂上
	//==   pchModName : 要Hook的API所在的模块名
	//==   pchFuncName: 要Hook的API的名字
	//==   pfnHookAddress: 用来替换API的函数地址
	//==   bInner: 表示区分是否内置钩子
	//======================================================================
	CAPIHook(PSTR pchModName, PSTR pchFuncName, PROC pfnHookAddress,BOOL bInner=FALSE);

	// 在析构中还原API钩子
	~CAPIHook();

	// 获取到API实际的地址
	PROC GetRealFunc();

private:
	// 已经挂钩的API列表
	static CAPIHook* m_spHead;
	CAPIHook* m_pNext;

	// 具体API钩子的数据
	PCSTR m_pchModName;
	PCSTR m_pchFuncName;
	PROC  m_pfnRealAddress;
	PROC  m_pfnHookAddress;
	BOOL  m_bInner ;

private:
	// 更新模块的IAT
	static void WINAPI ReplaceAllModules(PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress);
	static void WINAPI ReplaceModule(HMODULE hModule,PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress);

private:
	// 检测到有新的模块加载进来时，更新模块的IAT
	// 在内置钩子的转接函数中调用
	static void WINAPI UpdateModules(HMODULE hModule,DWORD dwFlags);

	static HMODULE ModuleFromAddress(PVOID pv);

	// 内置钩子的转接函数
	static HMODULE WINAPI LoadLibraryA(PCSTR pszModulePath);
	static HMODULE WINAPI LoadLibraryW(PCWSTR pszModulePath);
	static HMODULE WINAPI LoadLibraryExA(PCSTR pszModulePath,HANDLE hFile, DWORD dwFlags);
	static HMODULE WINAPI LoadLibraryExW(PCWSTR pszModulePath,HANDLE hFile, DWORD dwFlags);
	static FARPROC WINAPI GetProcAddress(HMODULE hModule, PCSTR pszProcName);

private:
	// 内置的钩子
	static CAPIHook m_sLoadLibraryA;
	static CAPIHook m_sLoadLibraryW;
	static CAPIHook m_sLoadLibraryExA;
	static CAPIHook m_sLoadLibraryExW;
	static CAPIHook m_sGetProcAddress;
};
