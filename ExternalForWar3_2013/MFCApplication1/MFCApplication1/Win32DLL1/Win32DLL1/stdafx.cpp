// stdafx.cpp : 只包括标准包含文件的源文件
// Win32DLL1.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用

/* Quick Messagebox Macro, wchar_t edition */
inline void chMB(PCWSTR szMsg) {
   wchar_t szTitle[MAX_PATH];
   GetModuleFileNameW(NULL, szTitle, _countof(szTitle));
   MessageBoxW(GetActiveWindow(), szMsg, szTitle, MB_OK);
}

void DisplayANumber(WCHAR * pszTitle, int inNum) {
	CStringW cswNum;
	cswNum.Format(L"%d", inNum);
	chMB(pszTitle + cswNum);
}

void DisplayLastError(WCHAR * pszFuncName) {
	CStringW cswLastError;
	cswLastError.Format(L"%d", GetLastError());
	chMB(pszFuncName + CStringW(L" 失败: ") + cswLastError + L".");
}