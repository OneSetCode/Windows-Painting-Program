; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "画图工具.h"
LastPage=0

ClassCount=8
Class1=CMyApp
Class2=CMyDoc
Class3=CMyView
Class4=CMainFrame

ResourceCount=6
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_DIALOG2
Class6=CTestDlg
Resource3=IDD_ABOUTBOX
Class7=CLoveDlg
Resource4=IDD_Useless
Resource5=IDD_DIALOG1
Class8=CChangeDlg
Resource6=IDD_DIALOG3

[CLS:CMyApp]
Type=0
HeaderFile=画图工具.h
ImplementationFile=画图工具.cpp
Filter=N

[CLS:CMyDoc]
Type=0
HeaderFile=画图工具Doc.h
ImplementationFile=画图工具Doc.cpp
Filter=N

[CLS:CMyView]
Type=0
HeaderFile=画图工具View.h
ImplementationFile=画图工具View.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMyView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=ID_MENUITEM32793




[CLS:CAboutDlg]
Type=0
HeaderFile=画图工具.cpp
ImplementationFile=画图工具.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=IDM_OnOption
Command18=IDM_COLOR
Command19=IDM_NULLBRUSH
Command20=IDM_COLORBRUSH
Command21=IDM_DOT
Command22=IDM_QLINE
Command23=IDM_LINE
Command24=IDM_SQUARE
Command25=IDM_RECTANGLE
Command26=IDM_CIRCLE
Command27=IDM_ELLIPSE
Command28=IDM_TRIANGLE
Command29=IDM_ERASER
Command30=IDM_EDGEANDFILL
Command31=IDM_FILLCHANGE
Command32=IDM_MOVE
Command33=IDM_BIGLITTLE
Command34=IDM_SPIN
Command35=ID_MENUITEM32793
CommandCount=35

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CTestDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LABEL2,{978C9E23-D4B0-11CE-BF2D-00AA003F40D0},1342177280
Control4=IDC_LINE_WIDTH,edit,1350631552

[CLS:CTestDlg]
Type=0
HeaderFile=TestDlg.h
ImplementationFile=TestDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestDlg
VirtualFilter=dWC

[CLS:CLoveDlg]
Type=0
HeaderFile=LoveDlg1.h
ImplementationFile=LoveDlg1.cpp
BaseClass=CDialog
Filter=D
LastObject=CLoveDlg
VirtualFilter=dWC

[DLG:IDD_Useless]
Type=1
Class=CLoveDlg
ControlCount=3
Control1=IDCANCEL,button,1342242816
Control2=IDC_FILLCOLOR,button,1342242816
Control3=IDC_BUTTON2,button,1342242816

[DLG:IDD_DIALOG2]
Type=1
Class=CLoveDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DIALOG3]
Type=1
Class=CChangeDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CChangeDlg]
Type=0
HeaderFile=ChangeDlg.h
ImplementationFile=ChangeDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CChangeDlg

