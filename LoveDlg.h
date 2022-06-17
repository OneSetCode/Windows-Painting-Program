#if !defined(AFX_LOVEDLG_H__F556B44F_C4CB_4767_8A5A_1379B98061AF__INCLUDED_)
#define AFX_LOVEDLG_H__F556B44F_C4CB_4767_8A5A_1379B98061AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LoveDlg.h : header file
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
		// NOTE: the ClassWizard will add data members here
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

#endif // !defined(AFX_LOVEDLG_H__F556B44F_C4CB_4767_8A5A_1379B98061AF__INCLUDED_)
