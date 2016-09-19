// Win32DLL1\dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <Windows.h>
#include <ImageHlp.h>
#pragma comment(lib,"imagehlp.lib")
#include "Win32DLL1.h"
#include "C:\Program Files (x86)\Microsoft Research\Detours Express 3.0\include\detours.h"
#include <d3dx9.h>

//#include <TlHelp32.h>
//#define COUNT_PAGE_LINE 200
#define WM_MY_VIEWCOMPLETE (WM_USER + 100)

//WCHAR * pszCurr = (WCHAR * )pvViewBase + offset;
//					/* stringZero copy */
//					CStringW cswName(me.szModule);
//					CStringW cswPath(me.szExePath);
//					CStringW cswResult = cswName + L" --- " + cswPath;
//					wcscpy_s(pszCurr, dwcWcharLine, cswResult);

//void GetcswResult(WCHAR * szMdl, WCHAR * szExe, WCHAR * pszC, DWORD dwc) {
//	// totally can't avoid this ugliness.
//	CStringW cswName(szMdl);
//	CStringW cswPath(szExe);
//	CStringW cswResult = cswName + L" --- " + cswPath;
//	wcscpy_s(pszC, dwc, cswResult);
//}
//
void GetCurrProcessName(WCHAR * pszBuff) {
	WCHAR pszTempBuff[MAX_PATH];
	GetModuleFileNameW(NULL, pszTempBuff, MAX_PATH);
	CString szProcessName(pszTempBuff);
	int nPos = szProcessName.ReverseFind('\\');
	szProcessName = szProcessName.Right(szProcessName.GetLength() - nPos - 1); 
	wcscpy_s(pszBuff, MAX_PATH, szProcessName);
}

DWORD WINAPI ReadMemThreadFunc(PVOID pvParam);

// Handle unexpected exceptions if the module is unloaded
LONG WINAPI InvalidReadExceptionFilter(PEXCEPTION_POINTERS pep) {

   // handle all unexpected exceptions because we simply don't patch
   // any module in that case
   LONG lDisposition = EXCEPTION_EXECUTE_HANDLER;

   // Note: pep->ExceptionRecord->ExceptionCode has 0xc0000005 as a value

   return(lDisposition);
}

void ReplaceIATEntryInOneMod(PCSTR pszCalleeModName, 
   PROC pfnCurrent, PROC pfnNew, HMODULE hmodCaller) {

   // Get the address of the module's import section
   ULONG ulSize;

   // An exception was triggered by Explorer (when browsing the content of 
   // a folder) into imagehlp.dll. It looks like one module was unloaded...
   // Maybe some threading problem: the list of modules from Toolhelp might 
   // not be accurate if FreeLibrary is called during the enumeration.
   PIMAGE_IMPORT_DESCRIPTOR pImportDesc = NULL;
   __try {
      pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR) ::ImageDirectoryEntryToData(
         hmodCaller, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);
   }
   __except (InvalidReadExceptionFilter(GetExceptionInformation())) {
      // Nothing to do in here, thread continues to run normally
      // with NULL for pImportDesc 
   }
   
   if (pImportDesc == NULL)
      return;  // This module has no import section or is no longer loaded


   // Find the import descriptor containing references to callee's functions
   for (; pImportDesc->Name; pImportDesc++) {
      PSTR pszModName = (PSTR) ((PBYTE) hmodCaller + pImportDesc->Name);
      if (lstrcmpiA(pszModName, pszCalleeModName) == 0) {

         // Get caller's import address table (IAT) for the callee's functions
         PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA) 
            ((PBYTE) hmodCaller + pImportDesc->FirstThunk);

         // Replace current function address with new function address
         for (; pThunk->u1.Function; pThunk++) {

            // Get the address of the function address
            PROC* ppfn = (PROC*) &pThunk->u1.Function;

            // Is this the function we're looking for?
            BOOL bFound = (*ppfn == pfnCurrent);
            if (bFound) {
               if (!WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew, 
                    sizeof(pfnNew), NULL) && (ERROR_NOACCESS == GetLastError())) {
                  DWORD dwOldProtect;
                  if (VirtualProtect(ppfn, sizeof(pfnNew), PAGE_WRITECOPY, 
                     &dwOldProtect)) {
                     WriteProcessMemory(GetCurrentProcess(), ppfn, &pfnNew, 
                        sizeof(pfnNew), NULL);
                     VirtualProtect(ppfn, sizeof(pfnNew), dwOldProtect, 
                        &dwOldProtect);
                  }
               }
               return;  // We did it, get out
            }
         }
      }  // Each import section is parsed until the right entry is found and patched
   }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: {
			// begin a new thread.
			HANDLE hReadMemThread = chBEGINTHREADEX(NULL, 0, ReadMemThreadFunc, NULL, 0, NULL);
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

//#pragma region(detour class preparation)
//class DetourDevice {
//public:
//	virtual COM_DECLSPEC_NOTHROW HRESULT STDMETHODCALLTYPE DetourPresent(
//		THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
//		CONST RGNDATA* pDirtyRegion) PURE {
//		Sleep(200);
//	}
//	#pragma chMSG(seems unfit.)
//	static HRESULT (STDMETHODCALLTYPE DetourDevice:: * RealPresent)(
//		THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
//		CONST RGNDATA* pDirtyRegion);
//};
//
//HRESULT (STDMETHODCALLTYPE DetourDevice:: * DetourDevice::RealPresent)(
//	THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
//	CONST RGNDATA* pDirtyRegion) =
//	(HRESULT (STDMETHODCALLTYPE DetourDevice:: *)(THIS_ CONST RECT* pSourceRect,
//	CONST RECT* pDestRect, HWND hDestWindowOverride,
//	CONST RGNDATA* pDirtyRegion))&IDirect3DDevice9::Present;
//#pragma endregion
//
//DWORD WINAPI ReadMemThreadFunc(PVOID pvParam) {
//		WCHAR pszBuff[MAX_PATH];
//		GetCurrProcessName(pszBuff);
//		if (CompareStringOrdinal(pszBuff, -1, L"War3.exe", -1, TRUE) == CSTR_EQUAL)
//		{
//			// detour commitment.
//			DetourTransactionBegin();
//			DetourUpdateThread(GetCurrentThread());
//			typedef HRESULT (STDMETHODCALLTYPE DetourDevice:: * PMFunc3D9) (
//				THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
//				CONST RGNDATA* pDirtyRegion);
//			PMFunc3D9 pmfuncPresent = &DetourDevice::DetourPresent;
//			PVOID * pvfuncPresent = (PVOID * )&pmfuncPresent;
//			DetourAttach((PVOID *)&DetourDevice::RealPresent, * pvfuncPresent);
//			if (DetourTransactionCommit() != NO_ERROR) {
//				chMB(L"DetourTransactionCommit fails.");
//			}

#pragma region(detour class preparation)
class DetourDevice {
public:
	HRESULT DetourPresent(
		THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
		CONST RGNDATA* pDirtyRegion) {
		IDirect3DDevice9 * pDevice = (IDirect3DDevice9 *)this;
		pDevice->BeginScene();

		// we can draw texts here.
		
		pDevice->EndScene();
		pDevice->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
		Sleep(300);
		return 0;
	}
#pragma chMSG(seems unfit.)
	static HRESULT(DetourDevice:: * RealPresent)(
		THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
		CONST RGNDATA* pDirtyRegion);
};

HRESULT (DetourDevice:: * DetourDevice::RealPresent)(
	THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion) =
	(HRESULT (DetourDevice:: * )(THIS_ CONST RECT* pSourceRect,
	CONST RECT* pDestRect, HWND hDestWindowOverride,
	CONST RGNDATA* pDirtyRegion))&IDirect3DDevice9::Present;
#pragma endregion

DWORD WINAPI ReadMemThreadFunc(PVOID pvParam) {
	WCHAR pszBuff[MAX_PATH];
	GetCurrProcessName(pszBuff);
	if (CompareStringOrdinal(pszBuff, -1, L"War3.exe", -1, TRUE) == CSTR_EQUAL)
	{
		// detour commitment.
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		typedef HRESULT(DetourDevice:: * PMFunc3D9) (
			THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride,
			CONST RGNDATA* pDirtyRegion);
		PMFunc3D9 pmfuncPresent = &DetourDevice::DetourPresent;
		PVOID * pvfuncPresent = (PVOID *)&pmfuncPresent;
		DetourAttach((PVOID * )&DetourDevice::RealPresent, *pvfuncPresent);
		if (DetourTransactionCommit() != NO_ERROR) {
			chMB(L"DetourTransactionCommit fails.");
		}
			
			/* create memory mapping view. */
			HANDLE hMapping = NULL;
			PVOID pvViewBase = NULL;
			__try {
		//		DWORD dwcWcharLine = MAX_MODULE_NAME32 + 5 + MAX_PATH;

				hMapping = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL,
					PAGE_READWRITE, 0, sizeof(int), L"GH2005_KO_FileMapping_1");
				if (hMapping == NULL)	{
					DisplayLastError(L"hMapping == NULL");
					__leave;
				}

				pvViewBase = MapViewOfFile(hMapping, FILE_MAP_WRITE, 0ul, 0ul, 0ul);
				if (pvViewBase == NULL) {
					DisplayLastError(L"pvViewBase == NULL");
					__leave;
				}

		//		/* fill the mapped view. */
		//		/* QueryFullProcessImageName available. */
		//		HANDLE hTh32Snapshot = INVALID_HANDLE_VALUE;
		//		#pragma chMSG(TH32CS_SNAPMODULE32 may cause a problem.)
		//		while ((hTh32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, 
		//			GetCurrentProcessId())) == INVALID_HANDLE_VALUE) {
		//			DWORD dwLastErr = GetLastError();
		//			DisplayLastError(L"CreateToolhelp32Snapshot");
		//		}

		//		MODULEENTRY32W me = { sizeof(me) };
		//		DWORD offset = 0;		// change 1 for one wchar_t.

		//		for (BOOL bOK = Module32FirstW(hTh32Snapshot, &me); bOK;
		//				bOK = Module32NextW(hTh32Snapshot, &me))
		//		{	// move each module's info to mapping file.
		//			if (offset >= (COUNT_PAGE_LINE - 1) * dwcWcharLine) {
		//				chMB(L"映射文件大小不足.");
		//				break;
		//			}
		//			else {
		//				WCHAR * pszCurr = (WCHAR * )pvViewBase + offset;
		//				/* stringZero copy */
		//				GetcswResult(me.szModule, me.szExePath, pszCurr, dwcWcharLine);
		//			}
		//			offset += dwcWcharLine;
		//		} // for
		//		CloseHandle(hTh32Snapshot);

		//		WCHAR * pszFin = (WCHAR * )pvViewBase + offset;
		//		wcscpy_s(pszFin, dwcWcharLine, L"GH2005_FINAL");

				// set an event object.
				HANDLE hEvent = CreateEventW(NULL, TRUE, FALSE, L"GH2005_KO_Event_1");

				while (1) {
					// fill the mapping file.
					* ((int * )pvViewBase) = * ((int *)0x023705b0);

					// sendmessage.
					if (!PostMessageW(FindWindowExW(NULL, NULL, NULL, L"GH2005_Window_1"), 
						WM_MY_VIEWCOMPLETE, NULL, NULL)) {
						DisplayLastError(L"PostMessageW");
						__leave;
					}

					WaitForSingleObject(hEvent, INFINITE);
					ResetEvent(hEvent);
					Sleep(500);
				}

				CloseHandle(hEvent);
			}
			__finally {
				if (pvViewBase != NULL) {
					UnmapViewOfFile(pvViewBase);
				}
				if (hMapping != NULL) {
					CloseHandle(hMapping);
				}
			}
		}
		// refresh function replacement, memory searching, drawing (and refreshing?).
		return 0;
}