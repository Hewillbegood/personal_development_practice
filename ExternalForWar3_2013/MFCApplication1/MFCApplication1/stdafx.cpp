
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// MFCApplication1.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

void DisplayANumber(WCHAR * pszTitle, int inNum) {
	CStringW cswNum;
	cswNum.Format(L"%d", inNum);
	chMB(pszTitle + cswNum);
}