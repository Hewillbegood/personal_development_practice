// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 WIN32DLL1_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// WIN32DLL1_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef WIN32DLL1_EXPORTS
#define WIN32DLL1_API __declspec(dllexport)
#else
#define WIN32DLL1_API __declspec(dllimport)
#endif

// 此类是从 Win32DLL1.dll 导出的
class WIN32DLL1_API CWin32DLL1 {
public:
	CWin32DLL1(int inInt);
	// TODO: 在此添加您的方法。
	void TargetMB(int inInt);
private:
	int insideInt;
};

WIN32DLL1_API extern int nWin32DLL1;

WIN32DLL1_API int fnWin32DLL1(void);

// for dll injection.
WIN32DLL1_API LRESULT CALLBACK GetMsgProc(
	_In_  int code, _In_  WPARAM wParam, _In_  LPARAM lParam);