/********************************************************* {COPYRIGHT-TOP} *
* RealZYC Confidential
* OCO Source Materials
*
* (C) Copyright RealZYC Corp. 2011 All Rights Reserved.
*
* The source code for this program is not published or otherwise
* divested of its trade secrets, irrespective of what has been
* deposited with the China Copyright Office.
********************************************************** {COPYRIGHT-END} */
#include "stdafx.h"
#include "BaseHook.h"
/***************************************
*class BaseHook
****************************************/
/***************************************
* Static
****************************************/
#pragma region Static
HINSTANCE BaseHook::hangle_HinstDLL = NULL;
#pragma endregion
/***************************************
* Property
****************************************/
#pragma region Property
//Set / get the hook type
BaseHook::HookTypes BaseHook::GetHookType(){return int_HookType;}
void BaseHook::SetHookType(HookTypes HookType){int_HookType = HookType;}
//Set / get the hook object thread id, give 0 for all thread
DWORD BaseHook::GetThreadId(){return dword_ThreadId;}
void BaseHook::SetThreadId(DWORD ThreadId){dword_ThreadId = ThreadId;}
//Set / get whether the hook is running
bool BaseHook::GetEnabled(){return ( point_HookID != NULL );}
void BaseHook::SetEnabled(bool Enabled)
{
	if(Enabled != GetEnabled())
	{
		if(Enabled)Start();
		else Stop();
	}
}
//Set / get dll hinst
HINSTANCE BaseHook::GetHinstDll()
{
	try
	{
		return (hangle_HinstDLL != NULL)? hangle_HinstDLL: 
						GetModuleHandle((LPCTSTR)"WinHook");
	}
	catch(...)
	{
		return NULL;
	}
}
void BaseHook::SetHinstDll(HINSTANCE HinstDLL){hangle_HinstDLL = HinstDLL;}
#pragma endregion
/***************************************
* New
****************************************/
#pragma region New
/***************************************
/// <summary>
/// Initial function
/// </summary>
/// <param name="HookType">The hook type</param>
/// <param name="ThreadId">The hook object thread id, give 0 for all thread</param>
****************************************/	
BaseHook::BaseHook(BaseHook::HookTypes HookType, DWORD ThreadId)
{
	point_HookID = NULL;
	
	//******************************************//
	//��ʼ��ί��
	byte * DelegatePoint = DelegateThisCall;
	DelegateThisCall[0] = 0xb9; //__asm mov ecx, this
	DelegateThisCall[5] = 0xe9; //__asm jmp, CoreHookProcess
	__asm
	{
		push eax				//����eax
		push ebx				//����ebx
		mov eax, this			//ȡ��this��ַ
		mov ebx, DelegatePoint	//��ȡDelegateThisCall��ַ
		mov dword ptr [ebx+1], eax	//this ��ַ, ˫��(DWORD)
	}
	__asm //����jmp��ַ�ο�:http://zhidao.baidu.com/question/105950930.html
	{
		lea eax, CoreHookProcess		//ȡ��CoreHookProcess��ַ
		mov ebx, DelegatePoint			//��ȡjmp��ַ= DelegatePoint + 5
		add ebx, 5
		add ebx, 5
		sub eax, ebx					//JMP��ַ=Ŀ���ַ-(�����ַ+����ָ���ֽ���)
		mov dword ptr [ebx-4], eax		//CoreHookProcess ��ַ, ˫��(DWORD)
		pop ebx					//��ԭebx
		pop eax					//��ԭeax
	}
	//******************************************//
	SetHook(HookType, ThreadId);
}
//Dispose function
BaseHook::~BaseHook(void)
{
	SetEnabled(false);
}
#pragma endregion
/***************************************
* Sub / Function
****************************************/
#pragma region Sub / Function
/***************************************
///<summary>
/// The defination of core hook process
///</summary>
///<param name="nCode">Specifies the hook code passed to the current hook procedure. The next hook procedure uses this code to determine how to process the hook information</param>
///<param name="wParam">Specifies the wParam value passed to the current hook procedure. The meaning of this parameter depends on the type of hook associated with the current hook chain</param>
///<param name="lParam">Specifies the lParam value passed to the current hook procedure. The meaning of this parameter depends on the type of hook associated with the current hook chain</param>
///<returns>The nCode, use 0 to pass the information to next hook, others to ignore the current information</returns>
///<remarks>Use for SetWindowsHookEx</remarks>
****************************************/
LRESULT /*CALLBACK*/ BaseHook::CoreHookProcess(int nCode, WPARAM wParam, LPARAM lParam)
{
	//����ģʽ�����ʹ��__stdcall (������CALLBACK�ؼ���)��
	//									��ôthisָ����ͨ��push this�����͵�, �Ƿ�����ʱ�������ջ�Ĳ�ƽ��, ���ں�������ʱ����
	//                       ���ʹ��__thiscall����ôthisָ����ͨ��ecx�������͵�, ���������ջ�仯, ���Գɹ�
	//�ο��ԣ�http://wenku.baidu.com/view/ad102ccf05087632311212ad.html
	LRESULT Result = this->HookProcess(nCode, wParam, lParam); //��ʱ����ʱ, ����������thisָ��,�ɹ�����
	if(Result == NULL)
		Result = CallNextHookEx(point_HookID, nCode, wParam, lParam);
	return Result; //����ע�͵�CALLBACK�����������ջ��ƽ������⣬�������غ��ޱ���
}
/***************************************
/// <summary>
/// Set the hook data
/// </summary>
/// <param name="HookType">The hook type</param>
/// <param name="ThreadId">The hook object thread id, give 0 for all thread</param>
/// <remarks>Restart the hook after the hook data changed</remarks>
****************************************/
void BaseHook::SetHook(BaseHook::HookTypes HookType, DWORD ThreadId)
{
	int_HookType = HookType;
	dword_ThreadId = ThreadId;
}
/***************************************
/// <summary>
/// Start the hook
/// </summary>
/// <remarks>Check the Enabled for operation result</remarks>
****************************************/
void BaseHook::Start()
{
	try
	{
		if(GetEnabled())SetEnabled(false);
		HINSTANCE hMod = NULL;
		if(GetThreadId() == 0)
		{
			hMod = GetHinstDll();
		}
		else
		{
			if(GetCurrentThreadId() == GetThreadId())
			{
				hMod = NULL;
			}
			else hMod = GetHinstDll();
		}
		//===============================================================
		//�����Ա����ָ��ת��Ϊһ�㺯��ָ��
		LRESULT (CALLBACK * PCoreHookProcess)(int nCode, WPARAM wParam, LPARAM lParam);
		byte * DelegatePoint = DelegateThisCall;
		__asm  //����������
		{
			push eax											//����eax
			mov eax, DelegatePoint
			mov PCoreHookProcess, eax				//��ί�е�ַǿ��ת����PCoreHookProcess
			pop eax											//��ԭeax
		}
		//===============================================================
		point_HookID = SetWindowsHookEx(GetHookType(), 
			PCoreHookProcess,
			hMod, 
			GetThreadId());
	}
	catch(...)
	{
		point_HookID = NULL;
	}
}
/***************************************
/// <summary>
/// Stop the hook
/// </summary>
/// <remarks>Check the Enabled for operation result</remarks>
****************************************/
void BaseHook::Stop()
{
	try
	{
		UnhookWindowsHookEx(point_HookID);
	}
	catch(...)
	{
	}
	point_HookID = NULL;
}
/***************************************
/// <summary>
/// The user defined hook process
/// </summary>
/// <param name="nCode">Specifies the hook code passed to the current hook procedure. The next hook procedure uses this code to determine how to process the hook information</param>
/// <param name="wParam">Specifies the wParam value passed to the current hook procedure. The meaning of this parameter depends on the type of hook associated with the current hook chain</param>
/// <param name="lParam">Specifies the lParam value passed to the current hook procedure. The meaning of this parameter depends on the type of hook associated with the current hook chain</param>
/// <returns>The nCode, use 0 to pass the information to next hook, others to ignore the current information</returns>
/// <remarks>Use for CoreHookProcess</remarks>
****************************************/
LRESULT /*CALLBACK*/ BaseHook::HookProcess(int nCode, WPARAM wParam, LPARAM lParam)
{
	return NULL;
}
#pragma endregion
