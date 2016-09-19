// Win32DLL1.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Win32DLL1.h"

// 这是导出变量的一个示例
WIN32DLL1_API int nWin32DLL1=0;

// 这是导出函数的一个示例
WIN32DLL1_API int fnWin32DLL1(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 Win32DLL1.h
CWin32DLL1::CWin32DLL1(int inInt)
	: insideInt(inInt)
{
	return;
}

void CWin32DLL1::TargetMB(int inInt) {
	DisplayANumber(L"TargetMB called: ", inInt);
}

WIN32DLL1_API LRESULT CALLBACK GetMsgProc(_In_  int code, _In_  WPARAM wParam,
										  _In_  LPARAM lParam)
{
	// nothing to do.
	return CallNextHookEx(NULL, code, wParam, lParam);
}