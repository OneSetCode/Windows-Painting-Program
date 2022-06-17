// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__7CAD5FB1_7785_4ADF_8AFD_E8F90C850FBD__INCLUDED_)
#define AFX_GRAPH_H__7CAD5FB1_7785_4ADF_8AFD_E8F90C850FBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraph  
{
public:
	CPoint m_ptEnd;
	CPoint m_ptOrigin;
	UINT m_nDrawType;
	COLORREF m_clr2;
	COLORREF m_clr;
	CPoint trg;
	UINT m_nLineWidth;
	UINT IfFill;
	UINT IfSpin;
	float Ang;
	CPoint Cen;

	CGraph();
	CGraph(UINT m_nDrawType,CPoint m_ptOrigin,CPoint m_ptEnd,UINT m_nLineWidth,UINT IfFill,COLORREF m_clr,COLORREF m_clr2,CPoint trg,UINT IfSpin,float Ang,CPoint Cen);
	virtual ~CGraph();

};

#endif // !defined(AFX_GRAPH_H__7CAD5FB1_7785_4ADF_8AFD_E8F90C850FBD__INCLUDED_)
