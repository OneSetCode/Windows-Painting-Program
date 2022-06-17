// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "»­Í¼¹¤¾ß.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog


CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_nLineWidth = 0;
	//}}AFX_DATA_INIT
}


void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
	DDV_MinMaxUInt(pDX, m_nLineWidth, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BEGIN_EVENTSINK_MAP(CTestDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CTestDlg)
	ON_EVENT(CTestDlg, IDC_LABEL1, 3 /* BeforeDragOver */, OnBeforeDragOverLabel1, VTS_DISPATCH VTS_DISPATCH VTS_R4 VTS_R4 VTS_I4 VTS_DISPATCH VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTestDlg::OnBeforeDragOverLabel1(LPDISPATCH Cancel, LPDISPATCH Data, float X, float Y, long DragState, LPDISPATCH Effect, short Shift) 
{
	// TODO: Add your control notification handler code here
	
}
