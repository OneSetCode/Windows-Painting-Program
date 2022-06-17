// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "»­Í¼¹¤¾ß.h"
#include "Graph.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CGraph::CGraph()
{

}

CGraph::CGraph(UINT m_nDrawType,CPoint m_ptOrigin,CPoint m_ptEnd,UINT m_nLineWidth,UINT IfFill,COLORREF m_clr,COLORREF m_clr2,CPoint trg,UINT IfSpin,float Ang,CPoint Cen)
{
	this->m_nDrawType=m_nDrawType;
	this->m_ptOrigin=m_ptOrigin;
	this->m_ptEnd=m_ptEnd;
	this->m_clr=m_clr;
	this->m_clr2=m_clr2;
	this->trg=trg;
	this->m_nLineWidth=m_nLineWidth;
	this->IfFill=IfFill;
	this->IfSpin=IfSpin;
	this->Ang=Ang;
	this->Cen=Cen;
}

CGraph::~CGraph()
{

}
