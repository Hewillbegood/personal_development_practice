#pragma once

class CAPIHookProxy
{
private:
	CAPIHookProxy(void);

public:
	~CAPIHookProxy(void);

	static CAPIHookProxy& Instance();
	BOOL HookAPIs();
	void UnhookAPIs();

private:
	typedef void (*PFN_Hook)();
	typedef void (*PFN_Unhook)();

	HINSTANCE	m_hHookDll;
};
