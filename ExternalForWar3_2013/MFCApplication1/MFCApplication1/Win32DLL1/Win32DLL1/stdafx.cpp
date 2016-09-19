// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Win32DLL1.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

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
	chMB(pszFuncName + CStringW(L" ʧ��: ") + cswLastError + L".");
}