//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_TESTDLG_H__EF210D70_94C0_4E0F_B3E0_2973E5A0D014__INCLUDED_)
#define AFX_TESTDLG_H__EF210D70_94C0_4E0F_B3E0_2973E5A0D014__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_DIALOG1 };
	UINT	m_nLineWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	afx_msg void OnBeforeDragOverLabel1(LPDISPATCH Cancel, LPDISPATCH Data, float X, float Y, long DragState, LPDISPATCH Effect, short Shift);
	afx_msg void OnBeforeDragOverLineWidth(LPDISPATCH Cancel, LPDISPATCH Data, float X, float Y, long DragState, LPDISPATCH Effect, short Shift);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__EF210D70_94C0_4E0F_B3E0_2973E5A0D014__INCLUDED_)
