// 画图工具View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__E92515F8_3133_4955_AA45_564CC95F4ABB__INCLUDED_)
#define AFX_VIEW_H__E92515F8_3133_4955_AA45_564CC95F4ABB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	UINT m_nLineWidth;
	virtual ~CMyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDot();
	afx_msg void OnQline();
	afx_msg void OnOption();
	afx_msg void OnColor();
	afx_msg void OnTriangle();
	afx_msg void OnSquare();
	afx_msg void OnCircle();
	afx_msg void OnEdge();
	afx_msg void OnFill();
	afx_msg void OnMove();
	afx_msg void OnFillin();
	afx_msg void OnNullbrush();
	afx_msg void OnColorbrush();
	afx_msg void OnEraser();
	afx_msg void OnEdgeandfill();
	afx_msg void OnFillchange();
	afx_msg void OnBiglittle();
	afx_msg void OnSpin();
	afx_msg void OnMenuitem32793();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CPtrArray m_ptrArray;
	UINT m_nFillColor;
	UINT IfFill;
	COLORREF m_clr2;
	COLORREF m_clr;
	BOOL m_nDraw;
	BOOL m_nMove;
	UINT m_nDrawType;
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
	CPoint trg;
	UINT IfSpin;
	float Ang;
	float ang;
	CPoint Cen;
	BOOL IfSpinning;
	UINT i;
	UINT a;
	CPoint Pot[1000][4];
};

#ifndef _DEBUG  // debug version in 画图工具View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__E92515F8_3133_4955_AA45_564CC95F4ABB__INCLUDED_)
