// 画图工具View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "画图工具.h"
#include <math.h>
#include <stdio.h>

#include "画图工具Doc.h"
#include "画图工具View.h"
#include "testdlg.h"
#include "lovedlg.h"
#include "changedlg.h"
#include "Graph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(IDM_LINE, OnLine)
	ON_COMMAND(IDM_RECTANGLE, OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, OnEllipse)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_DOT, OnDot)
	ON_COMMAND(IDM_QLINE, OnQline)
	ON_COMMAND(IDM_OnOption, OnOption)
	ON_COMMAND(IDM_COLOR, OnColor)
	ON_COMMAND(IDM_TRIANGLE, OnTriangle)
	ON_COMMAND(IDM_SQUARE, OnSquare)
	ON_COMMAND(IDM_CIRCLE, OnCircle)
	ON_COMMAND(IDM_MOVE, OnMove)
	ON_COMMAND(IDM_NULLBRUSH, OnNullbrush)
	ON_COMMAND(IDM_COLORBRUSH, OnColorbrush)
	ON_COMMAND(IDM_ERASER, OnEraser)
	ON_COMMAND(IDM_EDGEANDFILL, OnEdgeandfill)
	ON_COMMAND(IDM_FILLCHANGE, OnFillchange)
	ON_COMMAND(IDM_BIGLITTLE, OnBiglittle)
	ON_COMMAND(IDM_SPIN, OnSpin)
	ON_COMMAND(ID_MENUITEM32793, OnMenuitem32793)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	// TODO: add construction code here
	m_nDrawType=0;
	m_nFillColor=0;
	m_nDraw=FALSE;
	m_nMove=FALSE;
	m_nLineWidth=1;
	m_clr=RGB(0,0,0);
	m_clr2=NULL;
	IfSpinning=FALSE;
	i=0;
	a=0;
}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	CPoint trag[3];
	float sn;
	float cs;

	int n=0;
	for(n=0;n<m_ptrArray.GetSize();n++)
	{
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		pDC->SelectObject(pBrush);
		CPen pen(PS_SOLID,((CGraph*)m_ptrArray.GetAt(n))->m_nLineWidth,((CGraph*)m_ptrArray.GetAt(n))->m_clr);
		pDC->SelectObject(&pen);
		CBrush brush(((CGraph*)m_ptrArray.GetAt(n))->m_clr2);
		if(((CGraph*)m_ptrArray.GetAt(n))->IfFill==1)
		{
			pDC->SelectObject(brush);
		}

		int nGraphicsMode = SetGraphicsMode(pDC->GetSafeHdc(), GM_ADVANCED);
		XFORM xform;

		//pDC->SetBkMode(TRANSPARENT);
		//pDC->BeginPath();

		if(((CGraph*)m_ptrArray.GetAt(n))->IfSpin==1)
		{
			cs=float(cos(((CGraph*)m_ptrArray.GetAt(n))->Ang));
			sn=float(sin(((CGraph*)m_ptrArray.GetAt(n))->Ang));
			xform.eM11 = float(cs);
			xform.eM12 = float(sn);
			xform.eM21 = float(-sn);
			xform.eM22 = float(cs);
			xform.eDx = float(((CGraph*)m_ptrArray.GetAt(n))->Cen.x - cs*((CGraph*)m_ptrArray.GetAt(n))->Cen.x + sn*((CGraph*)m_ptrArray.GetAt(n))->Cen.y);
			xform.eDy = float(((CGraph*)m_ptrArray.GetAt(n))->Cen.y - cs*((CGraph*)m_ptrArray.GetAt(n))->Cen.y - sn*((CGraph*)m_ptrArray.GetAt(n))->Cen.x);
			SetWorldTransform(pDC->GetSafeHdc(), &xform);
		}

		switch(((CGraph*)m_ptrArray.GetAt(n))->m_nDrawType)
		{
		case 1:
			pDC->SetPixel(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin,((CGraph*)m_ptrArray.GetAt(n))->m_clr);
			break;
		case 2:
			pDC->MoveTo(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin);
			pDC->LineTo(((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin,((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin,((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd));
			break;
		case 5:
			trag[0]=((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin;
			trag[1]=((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd;
			trag[2]=((CGraph*)m_ptrArray.GetAt(n))->trg;
			pDC->Polygon(trag,3);
			break;
		case 6:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin,((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd));
			break;
		case 7:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(n))->m_ptOrigin,((CGraph*)m_ptrArray.GetAt(n))->m_ptEnd));
			break;
		}

		if(((CGraph*)m_ptrArray.GetAt(n))->IfSpin==1)
		{
			xform.eM11 = (float)1.0; 
			xform.eM12 = (float)0;
			xform.eM21 = (float)0;
			xform.eM22 = (float)1.0;
			xform.eDx = (float)0;
			xform.eDy = (float)0;
			SetWorldTransform(pDC->GetSafeHdc(), &xform);
			SetGraphicsMode(pDC->GetSafeHdc(), nGraphicsMode); 
		}

		//pDC->EndPath();
		//Rgin[n].CreateFromPath(pDC);
		
		if(IfSpinning==TRUE)
		{
			CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			pDC->SelectObject(pBrush);
			CPen pent(PS_DASH,1,RGB(200,200,200));
			pDC->SelectObject(&pent);
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(n))->Cen.x-120,((CGraph*)m_ptrArray.GetAt(n))->Cen.y-120,((CGraph*)m_ptrArray.GetAt(n))->Cen.x+120,((CGraph*)m_ptrArray.GetAt(n))->Cen.y+120));
			CPen pen1(PS_SOLID,1,RGB(255,0,0));
			pDC->SelectObject(&pen1);
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(n))->Cen.x-10,((CGraph*)m_ptrArray.GetAt(n))->Cen.y-130,((CGraph*)m_ptrArray.GetAt(n))->Cen.x+10,((CGraph*)m_ptrArray.GetAt(n))->Cen.y-110));
		}
	}
}


/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers


void CMyView::OnOption() 
{
	// TODO: Add your command handler code here
	CTestDlg dlg;
	dlg.m_nLineWidth=m_nLineWidth;
	if(IDOK==dlg.DoModal())
	{
		m_nLineWidth=dlg.m_nLineWidth;
	}
}



void CMyView::OnColor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult=m_clr;
	if(IDOK==dlg.DoModal())
	{
		m_clr=dlg.m_cc.rgbResult;
	}
}


void CMyView::OnNullbrush() 
{
	// TODO: Add your command handler code here
	m_nFillColor=0;
	m_clr2=NULL;
}


void CMyView::OnColorbrush() 
{
	// TODO: Add your command handler code here
	m_nFillColor=1;	
	CColorDialog dlg;
	dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult=m_clr2;
	if(IDOK==dlg.DoModal())
	{
		m_clr2=dlg.m_cc.rgbResult;
	}
}


void CMyView::OnEraser() 
{
	// TODO: Add your command handler code here
	m_nDrawType=0;
	m_clr=RGB(255,255,255);
	m_nLineWidth=10;
}




void CMyView::OnDot() 
{
	// TODO: Add your command handler code here
    m_nDrawType=1;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnQline() 
{
	// TODO: Add your command handler code here
	m_nDrawType=0;	
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnLine() 
{
	// TODO: Add your command handler code here
	m_nDrawType=2;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnRectangle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=3;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnSquare() 
{
	// TODO: Add your command handler code here
	m_nDrawType=6;
	IfSpinning=FALSE;
	Invalidate();
}



void CMyView::OnEllipse() 
{
	// TODO: Add your command handler code here
	m_nDrawType=4;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnCircle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=7;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnTriangle() 
{
	// TODO: Add your command handler code here
    m_nDrawType=5;	
	IfSpinning=FALSE;
	Invalidate();
}

void CMyView::OnEdgeandfill() 
{
	// TODO: Add your command handler code here
	m_nDrawType=8;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnFillchange() 
{
	// TODO: Add your command handler code here
    m_nDrawType=9;
	IfSpinning=FALSE;
	Invalidate();
}

void CMyView::OnMove() 
{
	// TODO: Add your command handler code here
	m_nDrawType=10;
	IfSpinning=FALSE;
	Invalidate();
}

void CMyView::OnBiglittle() 
{
	// TODO: Add your command handler code here
	m_nDrawType=11;
	IfSpinning=FALSE;
	Invalidate();
}


void CMyView::OnSpin() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	m_nDrawType=12;
	IfSpinning=TRUE;
	Invalidate();
}

void CMyView::OnMenuitem32793() 
{
	// TODO: Add your command handler code here
	m_ptrArray.RemoveAll();
	RedrawWindow();
	m_nDrawType=0;
	m_nFillColor=0;
	m_nDraw=FALSE;
	m_nMove=FALSE;
	m_nLineWidth=1;
	m_clr=RGB(0,0,0);
	m_clr2=NULL;
	IfSpinning=FALSE;
	i=0;
	a=0;
}


CPoint pt1[1000][10];//0为鼠标选中的位置,1,2,3为放缩时辅助记忆点
int sz[1000][10];//0为是否被选中
COLORREF color[1000];
CPoint trag[3];


void CMyView::OnLButtonDown(UINT nFlags, CPoint point)  
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	if(m_nDrawType!=5)
	{
		if(m_nDrawType!=8)
		{
			m_ptOrigin=point;
			m_nDraw=TRUE;

			if(m_nDrawType==10)
			{
				int c=a-1;
				bool xy=FALSE;

				CPoint el;
				CPoint er;
				CPoint eu;
				CPoint ed;
				float ea;
				float eb;
				float ec;
				CPoint e1;
				CPoint e2;
				float sum;

				while(c>=0 && xy==FALSE)
				{
					CRgn rgn1;
					CPoint pt=point;
					CPoint pa[4];
					CPoint pb[3];
					switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
					{
					case 0:
						break;
					case 1:
						rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+10);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(255,0,0);

							Invalidate();
								
							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 2:
						pa[0].x=Pot[c][0].x;
						pa[0].y=Pot[c][0].y-10;
						pa[1].x=Pot[c][0].x;
						pa[1].y=Pot[c][0].y+10;
						pa[2].x=Pot[c][1].x;
						pa[2].y=Pot[c][1].y+10;
						pa[3].x=Pot[c][1].x;
						pa[3].y=Pot[c][1].y-10;
						rgn1.CreatePolygonRgn(pa,4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(255,0,0);
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 3:
						rgn1.CreatePolygonRgn(Pot[c],4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 4:
						el.x=(Pot[c][0].x+Pot[c][3].x)/2;
						el.y=(Pot[c][0].y+Pot[c][3].y)/2;
						er.x=(Pot[c][1].x+Pot[c][2].x)/2;
						er.y=(Pot[c][1].y+Pot[c][2].y)/2;
						eu.x=(Pot[c][0].x+Pot[c][1].x)/2;
						eu.y=(Pot[c][0].y+Pot[c][1].y)/2;
						ed.x=(Pot[c][2].x+Pot[c][3].x)/2;
						ed.y=(Pot[c][2].y+Pot[c][3].y)/2;
						ea=sqrt((er.x-el.x)*(er.x-el.x)+(er.y-el.y)*(er.y-el.y))/2;
						eb=sqrt((eu.x-ed.x)*(eu.x-ed.x)+(eu.y-ed.y)*(eu.y-ed.y))/2;
						ec=sqrt(sqrt((ea*ea-eb*eb)*(ea*ea-eb*eb)));
						e1.x=(ec/ea)*(er.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
						e1.y=(ec/ea)*(er.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
						e2.x=(ec/ea)*(el.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
						e2.y=(ec/ea)*(el.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
						sum=sqrt((pt.x-e1.x)*(pt.x-e1.x)+(pt.y-e1.y)*(pt.y-e1.y))+sqrt((pt.x-e2.x)*(pt.x-e2.x)+(pt.y-e2.y)*(pt.y-e2.y));

						if(sum<=2*ea)
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 5:
						rgn1.CreatePolygonRgn(Pot[c],3,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 6:
						rgn1.CreatePolygonRgn(Pot[c],4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					case 7:
						rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							xy=TRUE;
							sz[c][0]=1;
							pt1[c][0]=point;
						}
						break;
					}
					c--;
				}
			}


			if(m_nDrawType==11)
			{
				int c=a-1;
				bool xy=FALSE;

				CPoint el;
				CPoint er;
				CPoint eu;
				CPoint ed;
				float ea;
				float eb;
				float ec;
				CPoint e1;
				CPoint e2;
				float sum;

				while(c>=0 && xy==FALSE)
				{
					CRgn rgn1;
					CPoint pt=point;
					CPoint pa[4];
					CPoint pb[3];
					switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
					{
					case 0:
						break;
					case 1:
						rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+10);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(255,0,0);
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
								
							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 2:
						pa[0].x=Pot[c][0].x;
						pa[0].y=Pot[c][0].y-10;
						pa[1].x=Pot[c][0].x;
						pa[1].y=Pot[c][0].y+10;
						pa[2].x=Pot[c][1].x;
						pa[2].y=Pot[c][1].y+10;
						pa[3].x=Pot[c][1].x;
						pa[3].y=Pot[c][1].y-10;
						rgn1.CreatePolygonRgn(pa,4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(255,0,0);
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 3:
						rgn1.CreatePolygonRgn(Pot[c],4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 4:
						el.x=(Pot[c][0].x+Pot[c][3].x)/2;
						el.y=(Pot[c][0].y+Pot[c][3].y)/2;
						er.x=(Pot[c][1].x+Pot[c][2].x)/2;
						er.y=(Pot[c][1].y+Pot[c][2].y)/2;
						eu.x=(Pot[c][0].x+Pot[c][1].x)/2;
						eu.y=(Pot[c][0].y+Pot[c][1].y)/2;
						ed.x=(Pot[c][2].x+Pot[c][3].x)/2;
						ed.y=(Pot[c][2].y+Pot[c][3].y)/2;
						ea=sqrt((er.x-el.x)*(er.x-el.x)+(er.y-el.y)*(er.y-el.y))/2;
						eb=sqrt((eu.x-ed.x)*(eu.x-ed.x)+(eu.y-ed.y)*(eu.y-ed.y))/2;
						ec=sqrt(sqrt((ea*ea-eb*eb)*(ea*ea-eb*eb)));
						e1.x=(ec/ea)*(er.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
						e1.y=(ec/ea)*(er.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
						e2.x=(ec/ea)*(el.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
						e2.y=(ec/ea)*(el.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
						sum=sqrt((pt.x-e1.x)*(pt.x-e1.x)+(pt.y-e1.y)*(pt.y-e1.y))+sqrt((pt.x-e2.x)*(pt.x-e2.x)+(pt.y-e2.y)*(pt.y-e2.y));

						if(sum<=2*ea)
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 5:
						rgn1.CreatePolygonRgn(Pot[c],3,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
							pt1[c][3]=((CGraph*)m_ptrArray.GetAt(c))->trg;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 6:
						rgn1.CreatePolygonRgn(Pot[c],4,1);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					case 7:
						rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y);
						if(rgn1.PtInRegion(pt))
						{
							color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
							((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(200,200,200);
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
							Invalidate();

							pt1[c][0]=point;
							pt1[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
							pt1[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

							xy=TRUE;
							sz[c][0]=1;
						}
						break;
					}
					c--;
				}
			}


			if(m_nDrawType==12)
			{
				int c=a-1;
				bool xy=FALSE;
				while(c>=0 && xy==FALSE)
				{
					CPoint pt=point;
					double dis=sqrt((pt.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+(pt.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y+120)*(pt.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y+120));
					CBrush brush1(RGB(255,0,0));
					dc.SelectObject(brush1);

					if(dis<10)
					{
						dc.Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(c))->Cen.x-10,((CGraph*)m_ptrArray.GetAt(c))->Cen.y-130,((CGraph*)m_ptrArray.GetAt(c))->Cen.x+10,((CGraph*)m_ptrArray.GetAt(c))->Cen.y-110));
						pt1[c][0]=point;

						xy=TRUE;
						sz[c][0]=1;
					}
					c--;
				}
			}

		}
		else
		{
			CRect m_client;
		}
	}
	else
	{
		if(i==0)
		{
			m_ptOrigin=point;
			trag[0]=point;
		}
		if(i==1)
		{
			m_ptEnd=point;
			trag[1]=point;
		}
		if(i==2)
		{
			trg=point;
			trag[2]=point;
		}
		i++;
	}
	CView::OnLButtonUp(nFlags, point);
}



void CMyView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
    if(m_nDrawType==0)
	{    
		CPen pen(PS_SOLID,m_nLineWidth,m_clr);
	    dc.SelectObject(&pen);
	    if(m_nDraw==TRUE)
		{
		    dc.MoveTo(m_ptOrigin); 
			dc.LineTo(point);
			m_ptOrigin=point;
		}

		CView::OnMouseMove(nFlags, point);
	}
}


void CMyView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	IfFill=0;
	if(m_nDraw==TRUE)
	{
		m_clr=RGB(0,0,0);
		m_nLineWidth=1;
	}
	m_nDraw=FALSE;
	CClientDC dc(this);
	CPen pen(PS_SOLID,m_nLineWidth,m_clr);
	dc.SelectObject(&pen);
	CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	CBrush brush(m_clr2);
	switch(m_nDrawType)
	{
	case 0:
		a++;
		break;
	case 1:
		dc.SetPixel(point,m_clr);

		a++;
		break;
	case 2:
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);

		Cen.x=(m_ptOrigin.x+point.x)/2;
		Cen.y=(m_ptOrigin.y+point.y)/2;

		m_ptEnd=point;
		Ang=0;

		Pot[a][0]=m_ptOrigin;
		Pot[a][1]=m_ptEnd;
		
		a++;

		break;
	case 3:
		if(m_nFillColor==1)
		{
			dc.SelectObject(brush);
			IfFill=1;
		}
		dc.Rectangle(CRect(m_ptOrigin,point));

		m_ptEnd=point;

		Pot[a][0]=m_ptOrigin;
		Pot[a][1].x=m_ptEnd.x;
		Pot[a][1].y=m_ptOrigin.y;
		Pot[a][2]=m_ptEnd;
		Pot[a][3].x=m_ptOrigin.x;
		Pot[a][3].y=m_ptEnd.y;

		a++;

		Cen.x=(m_ptOrigin.x+point.x)/2;
		Cen.y=(m_ptOrigin.y+point.y)/2;

		Ang=0;

		break;
	case 4:
		if(m_nFillColor==1)
		{
			dc.SelectObject(brush);
			IfFill=1;
		}
		dc.Ellipse(CRect(m_ptOrigin,point));

		Cen.x=(m_ptOrigin.x+point.x)/2;
		Cen.y=(m_ptOrigin.y+point.y)/2;

		m_ptEnd=point;
		Ang=0;

		Pot[a][0]=m_ptOrigin;
		Pot[a][1].x=m_ptEnd.x;
		Pot[a][1].y=m_ptOrigin.y;
		Pot[a][2]=m_ptEnd;
		Pot[a][3].x=m_ptOrigin.x;
		Pot[a][3].y=m_ptEnd.y;

		a++;

		break;
	case 5:
		if(i==3)
		{
			if(m_nFillColor==1)
			{
				dc.SelectObject(brush);
				IfFill=1;
			}
			dc.Polygon(trag,3);

			Pot[a][0]=m_ptOrigin;
			Pot[a][1]=m_ptEnd;
			Pot[a][2]=trg;

			a++;
			Cen.x=(trag[0].x+trag[1].x+trag[2].x)/3;
			Cen.y=(trag[0].y+trag[1].y+trag[2].y)/3;
			Ang=0;
		}
		
		break;
	case 6:
		if(m_nFillColor==1)
		{
			dc.SelectObject(brush);
			IfFill=1;
		}
		dc.Rectangle(CRect(m_ptOrigin.x,m_ptOrigin.y,m_ptOrigin.x+point.y-m_ptOrigin.y,point.y));

		point.x=m_ptOrigin.x+point.y-m_ptOrigin.y;

		Cen.x=(m_ptOrigin.x+point.x)/2;
		Cen.y=(m_ptOrigin.y+point.y)/2;

		m_ptEnd=point;
		Ang=0;

		Pot[a][0]=m_ptOrigin;
		Pot[a][1].x=m_ptEnd.x;
		Pot[a][1].y=m_ptOrigin.y;
		Pot[a][2]=m_ptEnd;
		Pot[a][3].x=m_ptOrigin.x;
		Pot[a][3].y=m_ptEnd.y;

		a++;

		break;
	case 7:
		if(m_nFillColor==1)
		{
			dc.SelectObject(brush);
			IfFill=1;
		}
		dc.Ellipse(CRect(m_ptOrigin.x,m_ptOrigin.y,m_ptOrigin.x+point.y-m_ptOrigin.y,point.y));

		point.x=m_ptOrigin.x+point.y-m_ptOrigin.y;

		Cen.x=(m_ptOrigin.x+point.x)/2;
		Cen.y=(m_ptOrigin.y+point.y)/2;

		m_ptEnd=point;
		Ang=0;

		Pot[a][0]=m_ptOrigin;
		Pot[a][1].x=m_ptEnd.x;
		Pot[a][1].y=m_ptOrigin.y;
		Pot[a][2]=m_ptEnd;
		Pot[a][3].x=m_ptOrigin.x;
		Pot[a][3].y=m_ptEnd.y;

		a++;

		break;
	}


	if(m_nDrawType==1||m_nDrawType==2||m_nDrawType==3||m_nDrawType==4||m_nDrawType==6||m_nDrawType==7)
	{
		CGraph *pGraph=new CGraph(m_nDrawType,m_ptOrigin,m_ptEnd,m_nLineWidth,IfFill,m_clr,m_clr2,trg,IfSpin,Ang,Cen);
		m_ptrArray.Add(pGraph);
	}

	if(m_nDrawType==5)
	{
		if(i==3)
		{
			CGraph *pGraph=new CGraph(m_nDrawType,m_ptOrigin,m_ptEnd,m_nLineWidth,IfFill,m_clr,m_clr2,trg,IfSpin,Ang,Cen);
			m_ptrArray.Add(pGraph);
			i=0;
		}	
	}


	if(m_nDrawType==8)
	{
		int c=a-1;
		bool xy=FALSE;
		while(c>=0 && xy==FALSE)
		{
			CRgn rgn1;
			CPoint pt=point;
			CPoint pa[4];
			CPoint pb[3];

			CPoint el;
			CPoint er;
			CPoint eu;
			CPoint ed;
			float ea;
			float eb;
			float ec;
			CPoint e1;
			CPoint e2;
			float sum;

			switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
			{
			case 0:
				break;
			case 1:
				rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+10);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();
						
					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 2:
				pa[0].x=Pot[c][0].x;
				pa[0].y=Pot[c][0].y-10;
				pa[1].x=Pot[c][0].x;
				pa[1].y=Pot[c][0].y+10;
				pa[2].x=Pot[c][1].x;
				pa[2].y=Pot[c][1].y+10;
				pa[3].x=Pot[c][1].x;
				pa[3].y=Pot[c][1].y-10;
				rgn1.CreatePolygonRgn(pa,4,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 3:
				rgn1.CreatePolygonRgn(Pot[c],4,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 4:
				el.x=(Pot[c][0].x+Pot[c][3].x)/2;
				el.y=(Pot[c][0].y+Pot[c][3].y)/2;
				er.x=(Pot[c][1].x+Pot[c][2].x)/2;
				er.y=(Pot[c][1].y+Pot[c][2].y)/2;
				eu.x=(Pot[c][0].x+Pot[c][1].x)/2;
				eu.y=(Pot[c][0].y+Pot[c][1].y)/2;
				ed.x=(Pot[c][2].x+Pot[c][3].x)/2;
				ed.y=(Pot[c][2].y+Pot[c][3].y)/2;
				ea=sqrt((er.x-el.x)*(er.x-el.x)+(er.y-el.y)*(er.y-el.y))/2;
				eb=sqrt((eu.x-ed.x)*(eu.x-ed.x)+(eu.y-ed.y)*(eu.y-ed.y))/2;
				ec=sqrt(sqrt((ea*ea-eb*eb)*(ea*ea-eb*eb)));
				e1.x=(ec/ea)*(er.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				e1.y=(ec/ea)*(er.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
				e2.x=(ec/ea)*(el.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				e2.y=(ec/ea)*(el.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
				sum=sqrt((pt.x-e1.x)*(pt.x-e1.x)+(pt.y-e1.y)*(pt.y-e1.y))+sqrt((pt.x-e2.x)*(pt.x-e2.x)+(pt.y-e2.y)*(pt.y-e2.y));

				if(sum<=2*ea)
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();
					xy=TRUE;
				}
				break;
			case 5:
				rgn1.CreatePolygonRgn(Pot[c],3,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 6:
				rgn1.CreatePolygonRgn(Pot[c],4,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 7:
				rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			}
			c--;
		}
	}

	if(m_nDrawType==9)
	{
		int c=a-1;
		bool xy=FALSE;

		CPoint el;
		CPoint er;
		CPoint eu;
		CPoint ed;
		float ea;
		float eb;
		float ec;
		CPoint e1;
		CPoint e2;
		float sum;

		while(c>=0 && xy==FALSE)
		{
			CRgn rgn1;
			CPoint pt=point;
			CPoint pa[4];
			CPoint pb[3];
			switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
			{
			case 0:
				break;
			case 1:
				rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+10,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+10);
				if(rgn1.PtInRegion(pt))
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;

					xy=TRUE;
				}
				break;
			case 2:
				pa[0].x=Pot[c][0].x;
				pa[0].y=Pot[c][0].y-10;
				pa[1].x=Pot[c][0].x;
				pa[1].y=Pot[c][0].y+10;
				pa[2].x=Pot[c][1].x;
				pa[2].y=Pot[c][1].y+10;
				pa[3].x=Pot[c][1].x;
				pa[3].y=Pot[c][1].y-10;
				rgn1.CreatePolygonRgn(pa,4,1);
				if(rgn1.PtInRegion(pt))
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=RGB(254,2,1);
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=dlg.m_cc.rgbResult;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr==RGB(254,2,1))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];
					}

					Invalidate();

					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;

					xy=TRUE;
				}
				break;
			case 3:
				rgn1.CreatePolygonRgn(Pot[c],4,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(201,200,199);
					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=dlg.m_cc.rgbResult;
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==RGB(201,200,199))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
						if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						{
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;
						}
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 4:
				el.x=(Pot[c][0].x+Pot[c][3].x)/2;
				el.y=(Pot[c][0].y+Pot[c][3].y)/2;
				er.x=(Pot[c][1].x+Pot[c][2].x)/2;
				er.y=(Pot[c][1].y+Pot[c][2].y)/2;
				eu.x=(Pot[c][0].x+Pot[c][1].x)/2;
				eu.y=(Pot[c][0].y+Pot[c][1].y)/2;
				ed.x=(Pot[c][2].x+Pot[c][3].x)/2;
				ed.y=(Pot[c][2].y+Pot[c][3].y)/2;
				ea=sqrt((er.x-el.x)*(er.x-el.x)+(er.y-el.y)*(er.y-el.y))/2;
				eb=sqrt((eu.x-ed.x)*(eu.x-ed.x)+(eu.y-ed.y)*(eu.y-ed.y))/2;
				ec=sqrt(sqrt((ea*ea-eb*eb)*(ea*ea-eb*eb)));
				e1.x=(ec/ea)*(er.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				e1.y=(ec/ea)*(er.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
				e2.x=(ec/ea)*(el.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				e2.y=(ec/ea)*(el.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
				sum=sqrt((pt.x-e1.x)*(pt.x-e1.x)+(pt.y-e1.y)*(pt.y-e1.y))+sqrt((pt.x-e2.x)*(pt.x-e2.x)+(pt.y-e2.y)*(pt.y-e2.y));

				if(sum<=2*ea)
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(201,200,199);
					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=dlg.m_cc.rgbResult;
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==RGB(201,200,199))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
						if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						{
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;
						}
					}

					Invalidate();

					xy=TRUE;
				}
				break;
			case 5:
				rgn1.CreatePolygonRgn(Pot[c],3,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(201,200,199);
					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=dlg.m_cc.rgbResult;
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==RGB(201,200,199))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
						if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						{
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;
						}
					}

					Invalidate();


					xy=TRUE;
				}
				break;
			case 6:
				rgn1.CreatePolygonRgn(Pot[c],4,1);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(201,200,199);
					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=dlg.m_cc.rgbResult;
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					}

					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==RGB(201,200,199))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
						if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						{
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;
						}
					}

					Invalidate();


					xy=TRUE;
				}
				break;
			case 7:
				rgn1.CreateEllipticRgn(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x,((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y);
				if(rgn1.PtInRegion(pt))
				{
					color[c]=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=RGB(201,200,199);
					((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					Invalidate();

					CColorDialog dlg;
					dlg.m_cc.Flags |=CC_RGBINIT | CC_FULLOPEN;
					dlg.m_cc.rgbResult=((CGraph*)m_ptrArray.GetAt(c))->m_clr2;
					if(IDOK==dlg.DoModal())
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=dlg.m_cc.rgbResult;
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=1;
					}


					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==RGB(201,200,199))
					{
						((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
						if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						{
							((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;
						}
					}

					Invalidate();


					xy=TRUE;
				}
				break;
			}
			c--;
		}
	}

	if(m_nDrawType==10)
	{
		int c=a-1;
		bool xy=FALSE;
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		dc.SelectObject(pBrush);
		while(c>=0 && xy==FALSE)
		{
			CPoint pt=point;
			switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
			{
			case 0:
				break;
			case 1:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];

					xy=TRUE;
					sz[c][0]=0;

					Invalidate();
				}
				break;
			case 2:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];

					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			case 3:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];
					Pot[c][2]+=point-pt1[c][0];
					Pot[c][3]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			case 4:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;


					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];
					Pot[c][2]+=point-pt1[c][0];
					Pot[c][3]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			case 5:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->trg+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];
					Pot[c][2]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			case 6:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;


					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];
					Pot[c][2]+=point-pt1[c][0];
					Pot[c][3]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			case 7:
				if(sz[c][0]==1)
				{
					((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin+=point-pt1[c][0];
			        ((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->Cen+=point-pt1[c][0];
					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;


					xy=TRUE;
					sz[c][0]=0;

					Pot[c][0]+=point-pt1[c][0];
					Pot[c][1]+=point-pt1[c][0];
					Pot[c][2]+=point-pt1[c][0];
					Pot[c][3]+=point-pt1[c][0];

					Invalidate();
				}
				break;
			}
			c--;
		}
	}

	if(m_nDrawType==11)
	{
		int c=a-1;
		bool xy=FALSE;
		CBrush *pBrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		dc.SelectObject(pBrush);
		while(c>=0 && xy==FALSE)
		{
			CPoint pt=point;
			switch(((CGraph*)m_ptrArray.GetAt(c))->m_nDrawType)
			{
			case 0:
				break;
			case 1:
				break;
			case 2:
				if(sz[c][0]==1)
				{ 
					if(abs(point.x-pt1[c][0].x)>abs(point.y-pt1[c][0].y))
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=point.x-pt1[c][0].x;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=point.x-pt1[c][0].x;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.x-pt1[c][0].x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.x-pt1[c][0].x);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
					}

					else
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=point.y-pt1[c][0].y;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=point.y-pt1[c][0].y;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.y-pt1[c][0].y);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.y-pt1[c][0].y);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.y-pt1[c][0].y)*(pt1[c][2].x-pt1[c][0].x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
					}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr=color[c];

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		

					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			case 3:
				if(sz[c][0]==1)
				{ 
					if(abs(point.x-pt1[c][0].x)>abs(point.y-pt1[c][0].y))
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=point.x-pt1[c][0].x;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=point.x-pt1[c][0].x;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.x-pt1[c][0].x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.x-pt1[c][0].x);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
					}

					else
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=point.y-pt1[c][0].y;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=point.y-pt1[c][0].y;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.y-pt1[c][0].y);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.y-pt1[c][0].y);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.y-pt1[c][0].y)*(pt1[c][2].x-pt1[c][0].x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
					}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x;
					Pot[c][1].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y;
					Pot[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
					Pot[c][3].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x;
					Pot[c][3].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][2].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][2].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][3].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][3].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		


					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			case 4:
				if(sz[c][0]==1)
				{ 
					if(abs(point.x-pt1[c][0].x)>abs(point.y-pt1[c][0].y))
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=point.x-pt1[c][0].x;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=point.x-pt1[c][0].x;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.x-pt1[c][0].x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.x-pt1[c][0].x);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
					}

					else
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=point.y-pt1[c][0].y;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=point.y-pt1[c][0].y;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.y-pt1[c][0].y);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.y-pt1[c][0].y);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.y-pt1[c][0].y)*(pt1[c][2].x-pt1[c][0].x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
					}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x;
					Pot[c][1].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y;
					Pot[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
					Pot[c][3].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x;
					Pot[c][3].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][2].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][2].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][3].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][3].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		

					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			case 5:
				if(sz[c][0]==1)
				{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							int f;
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=0;
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=1;
							if(((CGraph*)m_ptrArray.GetAt(c))->trg.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=2;

							switch(f)
							{
							case 0:
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->trg.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->trg.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;

							case 1:
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->trg.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->trg.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;

							case 2:
								((CGraph*)m_ptrArray.GetAt(c))->trg.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->trg.y+=(point.x-pt1[c][0].x)*(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;
							}
						}


						else
						{
							int f;
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=0;
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=1;
							if(((CGraph*)m_ptrArray.GetAt(c))->trg.x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
								f=2;

							switch(f)
							{
							case 0:
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->trg.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->trg.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;

							case 1:
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->trg.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->trg.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;

							case 2:  
								((CGraph*)m_ptrArray.GetAt(c))->trg.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->trg.y+=-(point.x-pt1[c][0].x)*(pt1[c][3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x=((CGraph*)m_ptrArray.GetAt(c))->Cen.x+(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y=((CGraph*)m_ptrArray.GetAt(c))->Cen.y+(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								break;
							}
						}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
					Pot[c][2]=((CGraph*)m_ptrArray.GetAt(c))->trg;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][2].x=(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->trg.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][2].y=(((CGraph*)m_ptrArray.GetAt(c))->trg.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->trg.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;

				
					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			case 6:
				if(sz[c][0]==1)
				{ 
					if(abs(point.x-pt1[c][0].x)>abs(point.y-pt1[c][0].y))
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=point.x-pt1[c][0].x;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=point.x-pt1[c][0].x;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.x-pt1[c][0].x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.x-pt1[c][0].x);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
					}

					else
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=point.y-pt1[c][0].y;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=point.y-pt1[c][0].y;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.y-pt1[c][0].y);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.y-pt1[c][0].y);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.y-pt1[c][0].y)*(pt1[c][2].x-pt1[c][0].x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
					}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x;
					Pot[c][1].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y;
					Pot[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
					Pot[c][3].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x;
					Pot[c][3].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][2].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][2].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][3].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][3].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		

					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			case 7:
				if(sz[c][0]==1)
				{ 
					if(abs(point.x-pt1[c][0].x)>abs(point.y-pt1[c][0].y))
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=point.x-pt1[c][0].x;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=point.x-pt1[c][0].x;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=point.x-pt1[c][0].x;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.x-pt1[c][0].x);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.x-pt1[c][0].x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.x-pt1[c][0].x);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.x-pt1[c][0].x)*(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.x-pt1[c][0].x)*(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)/(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x);
							}
						}
					}

					else
					{
						if(pt1[c][0].x>((CGraph*)m_ptrArray.GetAt(c))->Cen.x)
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=point.y-pt1[c][0].y;

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=point.y-pt1[c][0].y;
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=point.y-pt1[c][0].y;
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
						else
						{
							if(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x<((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x)
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-=-(point.y-pt1[c][0].y);

								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x+=-(point.y-pt1[c][0].y)*(pt1[c][2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
							else
							{
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y+=-(point.y-pt1[c][0].y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-=-(point.y-pt1[c][0].y);
		
								((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x+=-(point.y-pt1[c][0].y)*(pt1[c][1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/(pt1[c][1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
								((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-=-(point.y-pt1[c][0].y)*(pt1[c][2].x-pt1[c][0].x)/(pt1[c][2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y);
							}
						}
					}

					((CGraph*)m_ptrArray.GetAt(c))->m_clr2=color[c];
					if(((CGraph*)m_ptrArray.GetAt(c))->m_clr2==NULL)
						((CGraph*)m_ptrArray.GetAt(c))->IfFill=0;

					Pot[c][0]=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin;
					Pot[c][1].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x;
					Pot[c][1].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y;
					Pot[c][2]=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd;
					Pot[c][3].x=((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x;
					Pot[c][3].y=((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y;

					Pot[c][0].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][0].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][1].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][1].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][2].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][2].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		
					Pot[c][3].x=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))-(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
					Pot[c][3].y=(((CGraph*)m_ptrArray.GetAt(c))->m_ptOrigin.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(((CGraph*)m_ptrArray.GetAt(c))->Ang))+(((CGraph*)m_ptrArray.GetAt(c))->m_ptEnd.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(((CGraph*)m_ptrArray.GetAt(c))->Ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
		

					Invalidate();

					xy=TRUE;
					sz[c][0]=0;
				}
				break;
			}
			c--;
		}
	}

	if(m_nDrawType==12)
	{
		int c=a-1;
		bool xy=FALSE;
		CPoint px[4];
		while(c>=0 && xy==FALSE)
		{
			ang=float(asin((point.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)/sqrt((point.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*(point.x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)+(point.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*(point.y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y))));

			if(sz[c][0]==1)
			{	
				((CGraph*)m_ptrArray.GetAt(c))->IfSpin=1;
				((CGraph*)m_ptrArray.GetAt(c))->Ang+=ang;

				px[0]=Pot[c][0];
				px[1]=Pot[c][1];
				px[2]=Pot[c][2];
				px[3]=Pot[c][3];

				Pot[c][0].x=(px[0].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(ang))-(px[0].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				Pot[c][0].y=(px[0].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(ang))+(px[0].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;
				
				Pot[c][1].x=(px[1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(ang))-(px[1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				Pot[c][1].y=(px[1].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(ang))+(px[1].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;

				Pot[c][2].x=(px[2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(ang))-(px[2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				Pot[c][2].y=(px[2].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(ang))+(px[2].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;

				Pot[c][3].x=(px[3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(cos(ang))-(px[3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(sin(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.x;
				Pot[c][3].y=(px[3].x-((CGraph*)m_ptrArray.GetAt(c))->Cen.x)*float(sin(ang))+(px[3].y-((CGraph*)m_ptrArray.GetAt(c))->Cen.y)*float(cos(ang))+((CGraph*)m_ptrArray.GetAt(c))->Cen.y;

				Invalidate();

				xy=TRUE;
				sz[c][0]=0;
			}
	
			c--;
		}

	}

	CView::OnLButtonUp(nFlags, point);
}


