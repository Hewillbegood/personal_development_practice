// ATM_GH2005.cpp: ����Ŀ�ļ���

#include "stdafx.h"
#include "Form1.h"

using namespace ATM_GH2005;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// �ڴ����κοؼ�֮ǰ���� Windows XP ���ӻ�Ч��
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// ���������ڲ�������
	Application::Run(gcnew Form1());
	return 0;
}
