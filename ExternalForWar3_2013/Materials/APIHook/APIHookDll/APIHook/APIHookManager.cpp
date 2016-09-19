#include "StdAfx.h"
#include ".\apihookmanager.h"

#define SAFE_DELETE(p) if(p){delete p;p=NULL;}
#define HOOK_API(p,mod,func,proc) if(!p){p=new CAPIHook(mod,func,(PROC)CAPIHookManager::proc);}

CAPIHookManager::CAPIHookManager(void)
{
}

CAPIHookManager::~CAPIHookManager(void)
{
}

CAPIHookManager& CAPIHookManager::Instance()
{
	static CAPIHookManager obj;
	return obj ;
}

void CAPIHookManager::HookAPIs()
{
	HOOK_API(m_pHookMessageBoxA,"User32.dll","MessageBoxA",Hook_MessageBoxA);
	HOOK_API(m_pHookMessageBoxW,"User32.dll","MessageBoxW",Hook_MessageBoxW);
}

void CAPIHookManager::UnhookAPIs()
{
	SAFE_DELETE(m_pHookMessageBoxA);
	SAFE_DELETE(m_pHookMessageBoxW);
}

int WINAPI CAPIHookManager::Hook_MessageBoxA(HWND hwnd,PCSTR pszText,PCSTR pszCaption,UINT uType)
{
	CAPIHookManager * pThis = &CAPIHookManager::Instance() ;

	typedef int (WINAPI *PFN_MESSAGEBOXA)(HWND,PCSTR,PCSTR,UINT);

	// �õ� API ��ʵ�ĺ�����ַ
	PFN_MESSAGEBOXA pfnRealFunc = (PFN_MESSAGEBOXA)(pThis->m_pHookMessageBoxA->GetRealFunc()) ;

	// ����һ��,��ʾ����
	char achNewText[1024];
	sprintf(achNewText,"[Hook] %s",pszText);

	return pfnRealFunc(hwnd,achNewText,pszCaption,uType);
}

int WINAPI CAPIHookManager::Hook_MessageBoxW(HWND hwnd,PCWSTR pszText,PCWSTR pszCaption,UINT uType)
{
	CAPIHookManager * pThis = &CAPIHookManager::Instance() ;

	typedef int (WINAPI *PFN_MESSAGEBOXW)(HWND,PCWSTR,PCWSTR,UINT);

	// �õ� API ��ʵ�ĺ�����ַ
	PFN_MESSAGEBOXW pfnRealFunc = (PFN_MESSAGEBOXW)(pThis->m_pHookMessageBoxW->GetRealFunc()) ;

	// ����һ��,��ʾ����
	WCHAR wchNewText[1024];
	wsprintf(wchNewText,L"[Hook] %s",pszText);

	return pfnRealFunc(hwnd,wchNewText,pszCaption,uType);
}
