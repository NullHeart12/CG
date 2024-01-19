// Experiment_Frame_OneView.cpp : implementation of the CExperiment_Frame_OneView class
//

#include "stdafx.h"
#include "Experiment_Frame_One.h"

#include "Experiment_Frame_OneDoc.h"
#include "Experiment_Frame_OneView.h"
#include "SettingDlg.h"
#include "InputDialog.h"
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

#define cmptimes 500

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView

IMPLEMENT_DYNCREATE(CExperiment_Frame_OneView, CView)

BEGIN_MESSAGE_MAP(CExperiment_Frame_OneView, CView)
	//{{AFX_MSG_MAP(CExperiment_Frame_OneView)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(IDM_INPUT, OnInput)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView construction/destruction

CExperiment_Frame_OneView::CExperiment_Frame_OneView()
{
	// TODO: add construction code here
	m_bGridOn     = true;
	m_iMarginSize = 20;
	m_iPointSize  = 20;
	m_iActive_Algorithm = 0;

	m_PointColor  = RGB(255, 0, 0); 

	X0 = Y0 = 0;  
	X1 = Y1 = 10;

}

CExperiment_Frame_OneView::~CExperiment_Frame_OneView()
{
}

BOOL CExperiment_Frame_OneView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView drawing

void CExperiment_Frame_OneView::OnDraw(CDC* pDC)
{
	CExperiment_Frame_OneDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if( this->m_bGridOn )
	{
		this->DrawGrid(pDC);
	}
	auto start = chrono::steady_clock::now();
	switch( this->m_iActive_Algorithm) {
	case 0: //DDA
		for(int i=0;i<cmptimes;i++)
			DDA(X0,Y0,X1,Y1);
		break;
	case 1: //Mid_Bresenham
		for(int i=0;i<cmptimes;i++)
			Mid_Bresenham(X0,Y0,X1,Y1);
		break;
	default:
		break;
	}
	auto end = chrono::steady_clock::now();
	chrono::duration<double> diff = end - start;
	TRACE("duration:%lfs\n", diff.count());
	CView::OnDraw(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView printing

BOOL CExperiment_Frame_OneView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExperiment_Frame_OneView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExperiment_Frame_OneView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView diagnostics

#ifdef _DEBUG
void CExperiment_Frame_OneView::AssertValid() const
{
	CView::AssertValid();
}

void CExperiment_Frame_OneView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExperiment_Frame_OneDoc* CExperiment_Frame_OneView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExperiment_Frame_OneDoc)));
	return (CExperiment_Frame_OneDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExperiment_Frame_OneView message handlers

void CExperiment_Frame_OneView::DrawGrid(CDC *pDC)
{
	CRect ClientRect;
	GetClientRect( &ClientRect );

	CPen  *pNewPen = new CPen;
	pNewPen->CreatePen(PS_DOT, 1, RGB(256,0,0));
	CPen *pOldPen = pDC->SelectObject(pNewPen);

	int x0 = ClientRect.left   + m_iMarginSize; 
	int x1 = x0 + (ClientRect.right -ClientRect.left - 2*m_iMarginSize)/m_iPointSize * m_iPointSize;
	int y0 = ClientRect.bottom - m_iMarginSize;
	int y1 = y0 - (ClientRect.bottom - ClientRect.top - 2*m_iMarginSize)/m_iPointSize * m_iPointSize;
	int x,  y;
	//Draw horizontal lines
	for ( y = y0; y >= y1; y -= m_iPointSize)
	{
		pDC->MoveTo(x0, y);
		pDC->LineTo(x1, y);
	}

	//Draw vertical lines
	for ( x = x0; x <= x1; x += m_iPointSize)
	{
		pDC->MoveTo(x, y0);
		pDC->LineTo(x, y1);
	}


	pDC->SelectObject(pOldPen);
	pNewPen->DeleteObject();
	return;
}

void CExperiment_Frame_OneView::DrawPixel(int X, int Y)
{
	CDC *pDC= GetDC();
	CBrush *pNewBrush = new CBrush;
	pNewBrush->CreateSolidBrush(m_PointColor);
	CBrush *pOldBrush = pDC->SelectObject(pNewBrush);

	CPen *pNewPen = new CPen;
	pNewPen->CreatePen(PS_NULL, 1, RGB(255,0,0));
	CPen *pOldPen = pDC->SelectObject(pNewPen);

	CRect ClientRect;
	GetClientRect( &ClientRect );

	int x0 = ClientRect.left   + m_iMarginSize; 
	int y0 = ClientRect.bottom - m_iMarginSize;

	CRect Point;
	Point.left   = x0 + X*m_iPointSize;
	Point.right  = Point.left + m_iPointSize;
	
	Point.bottom = y0 - Y*m_iPointSize;
	Point.top    = Point.bottom - m_iPointSize;

	pDC->Rectangle(&Point);
	
	pDC->SelectObject(pOldBrush);
	pNewBrush->DeleteObject();

	pDC->SelectObject(pOldPen);
	pOldPen->DeleteObject();

}

void CExperiment_Frame_OneView::OnSetting() 
{
	CSettingDlg SettingDialog(m_iPointSize,
		                      m_PointColor,
							  m_iActive_Algorithm,
							  m_bGridOn
							  );
	if ( SettingDialog.DoModal() == IDOK )
	{
		this->m_bGridOn           = SettingDialog.m_bGridOn;
		this->m_PointColor        = SettingDialog.m_Point_Color;
		this->m_iPointSize        = SettingDialog.m_Point_Size;
		this->m_iActive_Algorithm = SettingDialog.m_iActive_Algorithm;
		this->Invalidate();		
	}
}

void CExperiment_Frame_OneView::OnInput() 
{
	CInputDialog InputDialog(X0, Y0, X1, Y1);

	if ( InputDialog.DoModal() == IDOK)
	{
		X0 = InputDialog.m_X0;
		X1 = InputDialog.m_X1;
		Y0 = InputDialog.m_Y0;
		Y1 = InputDialog.m_Y1;
		Invalidate();
	}	
}

//-------------------------算法实现------------------------------//
//绘制像素的函数DrawPixel(x, y);
void CExperiment_Frame_OneView::DDA(int X0, int Y0, int X1, int Y1)
{
	//----------请实现DDA算法------------//
	for (int i = 0; i < cmptimes; i++)
	{
		double x = X0, y = Y0;
		int dx = X1 - X0, dy = Y1 - Y0;
		int steps = max(abs(dx), abs(dy));
		double xIncre = double(dx) / double(steps), yIncre = double(dy) / double(steps);
		for (int i = 0; i <= steps; i++)
		{
			//DrawPixel(round(x), round(y));
			x += xIncre;
			y += yIncre;
		}
	}
}

void CExperiment_Frame_OneView::Mid_Bresenham(int X0, int Y0, int X1, int Y1)
{
	//-------请实现Mid_Bresenham算法-------//
	int dx = X1 - X0, dy = Y1 - Y0;
	int stepx = dx / abs(dx), stepy = dy / abs(dy);
	dx = stepx * dx, dy = stepy * dy;
	int x = X0, y = Y0;
	if (abs(dx) > abs(dy))
	{
		int Di = stepx * dx - 2 * stepy * dy;
		while (x != X1)
		{
			//DrawPixel(x, y);
			x += stepx;
			if (Di >= 0) Di = Di - 2 * stepy * dy;
			else
			{
				Di = Di - 2 * stepy * dy + 2 * stepx * dx;
				y += stepy;
			}
		}
		//DrawPixel(X1, Y1);
	}
	else
	{
		int Di = stepy * dy - 2 * stepx * dx;
		while (y != Y1)
		{
			//DrawPixel(x, y);
			y += stepy;
			if (Di >= 0) Di = Di - 2 * stepx * dx;
			else
			{
				Di =  Di - 2 * stepx * dx + 2 * stepy * dy;
				x += stepx;
			}
		}
		//DrawPixel(X1, Y1);
	}
}


