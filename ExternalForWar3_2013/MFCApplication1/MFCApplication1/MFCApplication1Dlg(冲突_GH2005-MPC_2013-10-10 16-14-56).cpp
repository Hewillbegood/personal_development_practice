
// MFCApplication1Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
//#include "afxdialogex.h"
#include "Win32DLL1\Win32DLL1\Win32DLL1.h"
//#include <Tlhelp32.h>

#ifdef _DEBUG
#endif
#define new DEBUG_NEW

#define WM_MY_VIEWCOMPLETE (WM_USER + 100)
//#define DW_COUNT_WCHAR_LINE MAX_MODULE_NAME32 + 5 + MAX_PATH
#define WM_MY_INITDONE (WM_USER + 101)


// CMFCApplication1Dlg �Ի���

void DisplayLastError(WCHAR * pszFuncName)
{
	CStringW cswLastError;
	cswLastError.Format(L"%d", GetLastError());
	chMB(pszFuncName + CStringW(L" ʧ��: ") + cswLastError + L".");
}

CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent), hwndWar3(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_MY_VIEWCOMPLETE, OnViewComplete)
	ON_MESSAGE(WM_MY_INITDONE, OnInitDone)
END_MESSAGE_MAP()


// CMFCApplication1Dlg ��Ϣ�������

DWORD WINAPI RqstThreadFunc(PVOID);

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HANDLE hRqstThread = chBEGINTHREADEX(NULL, 0, RqstThreadFunc, this, 0, NULL);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void chMBAllModules(WCHAR * pszViewBase) {
//	PWSTR pwszCurr = pszViewBase;
//	CStringW cswResult(L"");
//	int count = 0;
//	while (CompareStringOrdinal(pwszCurr, 12, L"GH2005_FINAL",
//		12, TRUE) != CSTR_EQUAL) {
//		cswResult += pwszCurr + CStringW(L"\n");
//		pwszCurr += DW_COUNT_WCHAR_LINE;
//		count ++;
//		if (count == 50) {
//			break;
//		}
//	}
//	chMB(cswResult);
//	CStringW cswResult2(L"");
//	while (CompareStringOrdinal(pwszCurr, 12, L"GH2005_FINAL",
//		12, TRUE) != CSTR_EQUAL) {
//		cswResult2 += pwszCurr + CStringW(L"\n");
//		pwszCurr += DW_COUNT_WCHAR_LINE;
//	}
//	chMB(cswResult2);
//}
//

void SetHAHEText(int inGold, CWnd * pwndThis) {
	CStringW cswGold;
	cswGold.Format(L"%d", inGold);
	pwndThis->GetDlgItem(ID_HAHA)->SetWindowTextW(cswGold);
}

LRESULT CMFCApplication1Dlg::OnViewComplete(WPARAM, LPARAM)
{
	HANDLE hEvent = NULL;
	HANDLE hFileMapping = NULL;
	PVOID pvViewBase = NULL;
	__try {
		hEvent = OpenEventW(EVENT_MODIFY_STATE, FALSE, L"GH2005_KO_Event_1");

		// get view of file.
		hFileMapping = OpenFileMappingW(FILE_MAP_READ, FALSE, L"GH2005_KO_FileMapping_1");
		pvViewBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);
		int goldValue = * ((int * )pvViewBase);
		SetHAHEText(goldValue, this);
	}
	__finally {
		// cleanup.
		if (pvViewBase != NULL) {
			UnmapViewOfFile(pvViewBase);
		}
		if (hFileMapping !=NULL) {
			CloseHandle(hFileMapping);
		}
		// set event.
		SetEvent(hEvent);
		if (hEvent != NULL) {
			CloseHandle(hEvent);
		}
	}

	return 0;
}

LRESULT CMFCApplication1Dlg::OnInitDone(WPARAM, LPARAM) {

	// set the windows hook.
	DWORD dwWar3PID;
	DWORD dwWar3WndTID = GetWindowThreadProcessId(this->hwndWar3, &dwWar3PID);		
	HHOOK hhk = SetWindowsHookExW(WH_GETMESSAGE, GetMsgProc, GetModuleHandleW(
		L"Win32DLL1.dll"), dwWar3WndTID);

	// modify memory.
	HANDLE hWar3Process = NULL;
	__try {

		if ( (hWar3Process = OpenProcess(PROCESS_ALL_ACCESS | PROCESS_TERMINATE | 
			PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, dwWar3PID))
			== NULL ) {
			DisplayLastError(L"��ȡ War3 ���̾��");
			__leave;
		}

		// prepare bytes.
		DWORD dwOrignBaseAddr = 0x6f6aff2e;
		DWORD dwDestBaseAddr = 0x023705c0;

		BYTE b1[] = { 0xe9, 0x8d, 0x06, 0xcc, 0x92 };
		BYTE b2[] = { 0x89, 0x5E, 0x20, 0x66, 0x9C, 0x81, 0x3E, 0x51, 0xC3, 0x43, 0x18, 0x75, 0x41, 0x90,
			0x90, 0x90, 0x90, 0x81, 0x7E, 0x18, 0x04, 0x00, 0x00, 0x00, 0x75, 0x34, 0x90, 0x90, 0x90, 0x90,
			0x81, 0x7E, 0x1C, 0x04, 0x00, 0x00, 0x00, 0x75, 0x27, 0x90, 0x90, 0x90, 0x90, 0x81, 0x7E, 0x24,
			0x00, 0x00, 0x00, 0x00, 0x75, 0x1A, 0x90, 0x90, 0x90, 0x90, 0x81, 0x7E, 0x28, 0xD2, 0xAD, 0x1A,
			0xD2, 0x75, 0x0D, 0x90, 0x90, 0x90, 0x90, 0x56, 0xBE, 0xB0, 0x05, 0x37, 0x02, 0x89, 0x1E, 0x5E,
			0x66, 0x9D, 0x0F, 0x84, 0x29, 0xf9, 0x33, 0x6d, 0xE9, 0x18, 0xf9, 0x33, 0x6d };

		for (int i = 0; i < 5; i ++) {
			WriteProcessMemory(hWar3Process, (LPVOID)(dwOrignBaseAddr + i), b1 + i, 1, NULL);
		}

		for (int i = 0; i < 91; i ++) {
			WriteProcessMemory(hWar3Process, (LPVOID)(dwDestBaseAddr + i), b2 + i, 1, NULL);
		}
	}
	__finally {
		if (hWar3Process != NULL)
			CloseHandle(hWar3Process);	
	}

	return 0;
}

DWORD WINAPI RqstThreadFunc(PVOID pvParam) {
	#pragma chMSG(fix here later. for full running status checking.)

	CMFCApplication1Dlg * pDlg = (CMFCApplication1Dlg * )pvParam;
	CWnd * pTextBox = pDlg->GetDlgItem(IDC_HAHE);
	BOOL bRunning = FALSE;

	while (1) {
		pDlg->hwndWar3 = ::FindWindowExW(NULL, NULL, NULL, L"Warcraft III");
		if (pDlg->hwndWar3 == NULL) {
			pTextBox->SetWindowTextW(L"Warcraft III û������.");
			bRunning = FALSE;
		}
		else {
			pTextBox->SetWindowTextW(L"Warcraft III ��������.");
			if (!bRunning) {
				pDlg->PostMessageW(WM_MY_INITDONE);
			}
			bRunning = TRUE;
		}
		::Sleep(1000);
	}

	return 0;
}