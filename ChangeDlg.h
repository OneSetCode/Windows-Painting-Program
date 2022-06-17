#if !defined(AFX_CHANGEDLG_H__D44C56F6_5FB8_4F98_B44C_581F1D29A696__INCLUDED_)
#define AFX_CHANGEDLG_H__D44C56F6_5FB8_4F98_B44C_581F1D29A696__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChangeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChangeDlg dialog

class CChangeDlg : public CDialog
{
// Construction
public:
	CChangeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChangeDlg)
	enum { IDD = IDD_DIALOG3 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChangeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChangeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANGEDLG_H__D44C56F6_5FB8_4F98_B44C_581F1D29A696__INCLUDED_)
