// Win32DLL1.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Win32DLL1.h"

// ���ǵ���������һ��ʾ��
WIN32DLL1_API int nWin32DLL1=0;

// ���ǵ���������һ��ʾ��
WIN32DLL1_API int fnWin32DLL1(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� Win32DLL1.h
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