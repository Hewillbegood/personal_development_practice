VERSION 5.00
Begin VB.Form Form1 
   BackColor       =   &H80000005&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "汇编指令To机器码"
   ClientHeight    =   4875
   ClientLeft      =   45
   ClientTop       =   435
   ClientWidth     =   4365
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   4875
   ScaleWidth      =   4365
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton Command2 
      BackColor       =   &H80000005&
      Caption         =   "转换"
      Height          =   435
      Left            =   3060
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   4320
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      BackColor       =   &H80000005&
      Caption         =   "清空"
      Height          =   435
      Left            =   1680
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   4320
      Width           =   1215
   End
   Begin VB.TextBox Text2 
      Height          =   1695
      Left            =   60
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   2460
      Width           =   4215
   End
   Begin VB.TextBox Text1 
      Height          =   1755
      Left            =   60
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "Form1.frx":0000
      Top             =   360
      Width           =   4275
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      Caption         =   "转换后的机器码："
      Height          =   180
      Left            =   60
      TabIndex        =   3
      Top             =   2220
      Width           =   1440
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H80000005&
      Caption         =   "输入要转换的汇编指令："
      Height          =   180
      Left            =   60
      TabIndex        =   2
      Top             =   120
      Width           =   1980
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Private Declare Function OpenProcess Lib "kernel32" (ByVal dwDesiredAccess As Long, ByVal bInheritHandle As Long, ByVal dwProcessId As Long) As Long
Private Declare Function WaitForSingleObject Lib "kernel32" (ByVal hHandle As Long, ByVal dwMilliseconds As Long) As Long
Private Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Private Const INFINITE = &HFFFFFFFF
Private Const SYNCHRONIZE = &H100000
Private Sub Command1_Click()
    Text1.Text = vbNullString
    Text2.Text = vbNullString
End Sub

Private Sub Command2_Click()
    Dim pid As Long, pHnd As Long
    If Len(Text1) Then
        Open App.Path & "\temp.asm" For Output As #1        '输出临时文件
        Print #1, Text1.Text                                '写入内存
        Close #1                                            '关闭文件
        If Len(Dir(App.Path & "\yasmw.exe")) Then           '检查文件是否存在
                                                            '隐藏运行nasmw进行转换工作
            pid = Shell("""" & App.Path & "\yasmw.exe""" & " -f bin " & """" & App.Path & "\temp.asm""" & " -o " & """" & App.Path & "\temp.bin""", vbHide)
            pHnd = OpenProcess(SYNCHRONIZE, 0, pid)         '打开进程
            If pHnd Then
                Call WaitForSingleObject(pHnd, INFINITE)    '等待执行完毕
                Call CloseHandle(pHnd)                      '关闭打开的句丙
                If Len(Dir(App.Path & "\temp.bin")) Then
                                                            '打开nasmw生成的文件并处理
                    Text2.Text = FoxHex(OpenFile2Hex(App.Path & "\temp.bin"))
                    If Len(Dir(App.Path & "\temp.asm")) Then
                        Kill App.Path & "\temp.asm"         '删除临时文件
                    End If
                End If
            End If
        End If
    End If
End Sub


Function Bin2Str(ByRef re() As Byte) As String
    Dim i As Long, tmpHex As String, RtnStr As String
    For i = LBound(re()) To UBound(re())
        tmpHex = Hex(re(i))
        RtnStr = RtnStr & IIf(re(i) < &H10, "0" & tmpHex, tmpHex)
    Next
    Bin2Str = RtnStr
End Function

Function FoxHex(Ans As String) As String
    Dim i As Long, tmpHex As String, RtnStr As String
    For i = 1 To Len(Ans) Step 2
        tmpHex = Mid$(Ans, i, 2)
        RtnStr = RtnStr & IIf(tmpHex = "66" Or tmpHex = "67", vbNullString, tmpHex)
    Next
    FoxHex = RtnStr
End Function

Function OpenFile2Hex(FileName As String) As String
    Dim FileSize As Long
    Dim DAT() As Byte
    Dim HexFile As String
    FileSize = FileLen(FileName)    '获取文件长度
    If FileSize Then
        ReDim DAT(FileSize - 1) As Byte '分配数组大小
        Open FileName For Binary As #1  '打开文件
        Get #1, , DAT                   '附给数组
        Close #1                        '关闭打开的文件
        OpenFile2Hex = Bin2Str(DAT)     '转换成16进制
    End If
End Function

Private Sub Form_Load()
Text1.Text = "Nop"
End Sub
