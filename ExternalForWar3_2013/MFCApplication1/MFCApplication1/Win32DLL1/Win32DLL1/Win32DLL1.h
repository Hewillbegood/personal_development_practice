// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� WIN32DLL1_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// WIN32DLL1_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef WIN32DLL1_EXPORTS
#define WIN32DLL1_API __declspec(dllexport)
#else
#define WIN32DLL1_API __declspec(dllimport)
#endif

// �����Ǵ� Win32DLL1.dll ������
class WIN32DLL1_API CWin32DLL1 {
public:
	CWin32DLL1(int inInt);
	// TODO: �ڴ�������ķ�����
	void TargetMB(int inInt);
private:
	int insideInt;
};

WIN32DLL1_API extern int nWin32DLL1;

WIN32DLL1_API int fnWin32DLL1(void);

// for dll injection.
WIN32DLL1_API LRESULT CALLBACK GetMsgProc(
	_In_  int code, _In_  WPARAM wParam, _In_  LPARAM lParam);