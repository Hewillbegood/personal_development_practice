#include "StdAfx.h"
#include "APIHookProxy.h"

CAPIHookProxy::CAPIHookProxy(void)
{
	m_hHookDll = NULL;
}

CAPIHookProxy::~CAPIHookProxy(void)
{
	if(m_hHookDll)
	{
		FreeLibrary(m_hHookDll);
		m_hHookDll = NULL;
	}
}

CAPIHookProxy& CAPIHookProxy::Instance()
{
	static CAPIHookProxy obj;
	return obj;
}

BOOL CAPIHookProxy::HookAPIs()
{
	if(m_hHookDll==NULL)
	{
		m_hHookDll = LoadLibrary(_T("APIHookDll.dll"));
	}

	if(m_hHookDll==NULL) return FALSE;

	PFN_Hook pfnHook = (PFN_Hook)::GetProcAddress(m_hHookDll,"HookAPIs");
	if(pfnHook==NULL)
	{
		FreeLibrary(m_hHookDll);
		m_hHookDll = NULL;
		return FALSE;
	}

	pfnHook();
	return TRUE;
}

void CAPIHookProxy::UnhookAPIs()
{
	if(m_hHookDll==NULL) return;

	PFN_Unhook pfnUnhook = (PFN_Unhook)::GetProcAddress(m_hHookDll,"UnhookAPIs");
	if(pfnUnhook!=NULL)
	{
		pfnUnhook();
	}

	FreeLibrary(m_hHookDll);
	m_hHookDll = NULL;
}