#if !defined(AFX_LOVEDLG1_H__8C83A60A_0C0B_41F5_88A5_B7F01083D874__INCLUDED_)
#define AFX_LOVEDLG1_H__8C83A60A_0C0B_41F5_88A5_B7F01083D874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoveDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLoveDlg dialog

class CLoveDlg : public CDialog
{
// Construction
public:
	CLoveDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoveDlg)
	enum { IDD = IDD_DIALOG2 };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoveDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOVEDLG1_H__8C83A60A_0C0B_41F5_88A5_B7F01083D874__INCLUDED_)
