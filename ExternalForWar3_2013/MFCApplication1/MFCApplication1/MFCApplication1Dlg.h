
// MFCApplication1Dlg.h : ͷ�ļ�
//

#pragma once


// CMFCApplication1Dlg �Ի���
class CMFCApplication1Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	friend DWORD WINAPI RqstThreadFunc(PVOID pvParam);

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnViewComplete(WPARAM, LPARAM);
	afx_msg LRESULT OnInitDone(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

private:
	HWND hwndWar3;
public:
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
};
