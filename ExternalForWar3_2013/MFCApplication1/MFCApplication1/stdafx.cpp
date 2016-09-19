
// stdafx.cpp : 只包括标准包含文件的源文件
// MFCApplication1.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

void DisplayANumber(WCHAR * pszTitle, int inNum) {
	CStringW cswNum;
	cswNum.Format(L"%d", inNum);
	chMB(pszTitle + cswNum);
}