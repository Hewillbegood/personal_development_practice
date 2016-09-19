
#pragma once

class CAPIHook 
{
public:
	//=======================================================================
	//== ������ѹ��ӹ���
	//==   pchModName : ҪHook��API���ڵ�ģ����
	//==   pchFuncName: ҪHook��API������
	//==   pfnHookAddress: �����滻API�ĺ�����ַ
	//==   bInner: ��ʾ�����Ƿ����ù���
	//======================================================================
	CAPIHook(PSTR pchModName, PSTR pchFuncName, PROC pfnHookAddress,BOOL bInner=FALSE);

	// �������л�ԭAPI����
	~CAPIHook();

	// ��ȡ��APIʵ�ʵĵ�ַ
	PROC GetRealFunc();

private:
	// �Ѿ��ҹ���API�б�
	static CAPIHook* m_spHead;
	CAPIHook* m_pNext;

	// ����API���ӵ�����
	PCSTR m_pchModName;
	PCSTR m_pchFuncName;
	PROC  m_pfnRealAddress;
	PROC  m_pfnHookAddress;
	BOOL  m_bInner ;

private:
	// ����ģ���IAT
	static void WINAPI ReplaceAllModules(PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress);
	static void WINAPI ReplaceModule(HMODULE hModule,PCSTR pchModName,PROC pfnRealAddress,PROC pfnHookAddress);

private:
	// ��⵽���µ�ģ����ؽ���ʱ������ģ���IAT
	// �����ù��ӵ�ת�Ӻ����е���
	static void WINAPI UpdateModules(HMODULE hModule,DWORD dwFlags);

	static HMODULE ModuleFromAddress(PVOID pv);

	// ���ù��ӵ�ת�Ӻ���
	static HMODULE WINAPI LoadLibraryA(PCSTR pszModulePath);
	static HMODULE WINAPI LoadLibraryW(PCWSTR pszModulePath);
	static HMODULE WINAPI LoadLibraryExA(PCSTR pszModulePath,HANDLE hFile, DWORD dwFlags);
	static HMODULE WINAPI LoadLibraryExW(PCWSTR pszModulePath,HANDLE hFile, DWORD dwFlags);
	static FARPROC WINAPI GetProcAddress(HMODULE hModule, PCSTR pszProcName);

private:
	// ���õĹ���
	static CAPIHook m_sLoadLibraryA;
	static CAPIHook m_sLoadLibraryW;
	static CAPIHook m_sLoadLibraryExA;
	static CAPIHook m_sLoadLibraryExW;
	static CAPIHook m_sGetProcAddress;
};
