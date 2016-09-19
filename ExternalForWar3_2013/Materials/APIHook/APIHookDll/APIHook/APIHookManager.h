#pragma once

#include "APIHook.h"
#include "winsock.h"

class CAPIHookManager
{
private:
	CAPIHookManager(void);

public:
	~CAPIHookManager(void);

	static CAPIHookManager& Instance();

	void HookAPIs();
	void UnhookAPIs();

private:
	// Hookת�Ӻ���
	static int WINAPI Hook_MessageBoxA(HWND hwnd,PCSTR pszText,PCSTR pszCaption,UINT uType);
	static int WINAPI Hook_MessageBoxW(HWND hwnd,PCWSTR pszText,PCWSTR pszCaption,UINT uType);

private:
	CAPIHook *	m_pHookMessageBoxA ;
	CAPIHook *	m_pHookMessageBoxW ;
};
