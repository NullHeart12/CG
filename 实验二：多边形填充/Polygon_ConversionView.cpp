// Polygon_ConversionView.cpp : implementation of the CPolygon_ConversionView class
//

#include "stdafx.h"
#include "Polygon_Conversion.h"

#include "Polygon_ConversionDoc.h"
#include "Polygon_ConversionView.h"
#include "SettingDialog.h"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView

IMPLEMENT_DYNCREATE(CPolygon_ConversionView, CView)

BEGIN_MESSAGE_MAP(CPolygon_ConversionView, CView)
	//{{AFX_MSG_MAP(CPolygon_ConversionView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_VIEW_INPUT_POLYGON, OnViewInputPolygon)
	ON_UPDATE_COMMAND_UI(ID_VIEW_INPUT_POLYGON, OnUpdateViewInputPolygon)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_SETTING, OnViewSetting)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView construction/destruction

CPolygon_ConversionView::CPolygon_ConversionView()
{
	m_bInputting_Polygon = FALSE;

	m_Vertex_Number = 0;   //������ĿΪ0��

	m_Fill_Color     = RGB(255, 0,0);
	m_bFillPolygon   = TRUE;
	m_iFillAlgorithm = 0;     


	m_pDC = NULL;
}

CPolygon_ConversionView::~CPolygon_ConversionView()
{
}

BOOL CPolygon_ConversionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView drawing

void CPolygon_ConversionView::OnDraw(CDC* pDC)
{
	CPolygon_ConversionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	m_pDC = pDC;
	// TODO: add draw code for native data here

	if ( this->m_bFillPolygon && this->m_Vertex_Number >= 3)
	{
		switch(this->m_iFillAlgorithm) {
		case 0: //x_scan_line
			X_Scan_Line_Conersion(m_Vertices, m_Vertex_Number);			
			break;
		case 1:
			Active_Edge_Table_Conersion(m_Vertices, m_Vertex_Number);			
			break;
		default:
			break;
		}
	}
	DrawPolygonOutline(pDC);  //���ƶ���ͱ߿�

	m_pDC = NULL;
	CView::OnDraw(pDC);	
}

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView printing

BOOL CPolygon_ConversionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPolygon_ConversionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPolygon_ConversionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView diagnostics

#ifdef _DEBUG
void CPolygon_ConversionView::AssertValid() const
{
	CView::AssertValid();
}

void CPolygon_ConversionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPolygon_ConversionDoc* CPolygon_ConversionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPolygon_ConversionDoc)));
	return (CPolygon_ConversionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPolygon_ConversionView message handlers

void CPolygon_ConversionView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( this->m_bInputting_Polygon)
	{
		m_Vertices[m_Vertex_Number][0] = point.x;
		m_Vertices[m_Vertex_Number][1] = point.y;
		m_Vertex_Number++;

		if ( m_Vertex_Number > 1)
		{
			CDC *pDC = this->GetDC();
			pDC->SetMapMode(R2_COPYPEN);
			pDC->MoveTo(m_Vertices[m_Vertex_Number-2][0],m_Vertices[m_Vertex_Number-2][1]);
			pDC->LineTo(m_Vertices[m_Vertex_Number-1][0],m_Vertices[m_Vertex_Number-1][1]);
			pDC->DeleteDC();
		}

		//For rubber drawing
		m_PrePoint = point;
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CPolygon_ConversionView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( this->m_bInputting_Polygon  && this->m_Vertex_Number > 0 )
	{
		CDC *pDC = this->GetDC();
		
		pDC->SetROP2(R2_NOT);
		
		
		pDC->MoveTo(m_Vertices[m_Vertex_Number-1][0],
			m_Vertices[m_Vertex_Number-1][1]);
		pDC->LineTo(m_PrePoint);
		
		pDC->MoveTo(m_Vertices[m_Vertex_Number-1][0],
			m_Vertices[m_Vertex_Number-1][1]);
		pDC->LineTo(point);
		
		m_PrePoint = point;
	}
	
	CView::OnMouseMove(nFlags, point);
}

void CPolygon_ConversionView::OnRButtonDown(UINT nFlags, CPoint point) 
{


	if ( this->m_bInputting_Polygon )
	{
		m_bInputting_Polygon = FALSE;


		if ( m_Vertex_Number > 1)
		{
			CDC *pDC = this->GetDC();
			//�������һ��rubber line;
			pDC->SetROP2(R2_NOT);
			pDC->MoveTo(m_Vertices[m_Vertex_Number-1][0],m_Vertices[m_Vertex_Number-1][1]);
			pDC->LineTo(m_PrePoint);

			//��ն����
			pDC->SetMapMode(R2_COPYPEN);
			pDC->MoveTo(m_Vertices[m_Vertex_Number-1][0],m_Vertices[m_Vertex_Number-1][1]);
			pDC->LineTo(m_Vertices[0][0],m_Vertices[0][1]);
			pDC->DeleteDC();

		
		}
	}
	CView::OnRButtonDown(nFlags, point);
}

void CPolygon_ConversionView::OnViewInputPolygon() 
{
	this->m_bInputting_Polygon = TRUE;	
}

void CPolygon_ConversionView::OnUpdateViewInputPolygon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bInputting_Polygon);
	pCmdUI->Enable(!m_bInputting_Polygon);	
}

void CPolygon_ConversionView::OnViewSetting() 
{
	CSettingDialog SettingDialog(m_Fill_Color,
		                         m_bFillPolygon,
								 m_iFillAlgorithm);
	if ( SettingDialog.DoModal() == IDOK )
	{
		this->m_bFillPolygon  = SettingDialog.m_bFill_Polygon;
		this->m_Fill_Color    = SettingDialog.m_FillColor;
		this->m_iFillAlgorithm = SettingDialog.m_iAlgorithm;

		this->Invalidate();
	}
}


/***************************************************************
���ƶ���α߿�
****************************************************************/
void CPolygon_ConversionView::DrawPolygonOutline(CDC *pDC)
{
	if ( this->m_Vertex_Number == 0) 
	{
		return;
	}
	pDC->SetMapMode(R2_COPYPEN);
	pDC->MoveTo(m_Vertices[0][0], m_Vertices[0][1]);

	//�����������״̬������Ҫ�������һ��͵�һ�㣬������Ҫ���ӣ�
	int LastPoint = this->m_bInputting_Polygon ?  (m_Vertex_Number-1): m_Vertex_Number;
	for ( int i = 1; i <= LastPoint; i++ )
	{
		pDC->LineTo(m_Vertices[i%m_Vertex_Number][0],m_Vertices[i%m_Vertex_Number][1]);
	}
	return;
}

void CPolygon_ConversionView::DrawPixel(int x, int y)
{

	if ( m_pDC != NULL)
	{
		CPen *pNewPen = new CPen;
		pNewPen->CreatePen(PS_SOLID, 1, this->m_Fill_Color);
		CPen *pOldPen = m_pDC->SelectObject(pNewPen);
		
		m_pDC->MoveTo(x-1, y);
		m_pDC->LineTo(x, y);

		m_pDC->SelectObject(pOldPen);
		pNewPen->DeleteObject();
		delete pNewPen;
	}
}

class Node
{
public:
	int xymin;
	int ymin;
	int ymax;
	double uwk;
	
	Node() {}
	Node(int x=0, int yi = 0, int y=0, double u=1) { xymin = x, ymin = yi, ymax = y, uwk = u; }
	~Node() {}

	bool operator==(const Node& other) const { return xymin == other.xymin && ymin == other.ymin && ymax == other.ymax && uwk == other.uwk; }

	bool operator<(const Node& other) const
	{
		if (xymin != other.xymin) return xymin < other.xymin;
		if (uwk != other.uwk) return uwk < other.uwk;
		return false;
	}
};

/*********************************************************************
���ܣ�X-ɨ����ת���㷨

����˵����
	 vertices[][2]---�����б�
	 VertexNum    ---������Ŀ
��ע��
     DrawPixel(int x, int y) --�������ص�(x, y)
**********************************************************************/
void  CPolygon_ConversionView::X_Scan_Line_Conersion(int Vertices[][2], int VertexNum)
{
	int top = INT_MIN, bottom = INT_MAX;
	for (int i = 0; i < VertexNum; i++)
	{
		int nowY = Vertices[i][1];
		if (nowY > top) top = nowY;
		if (nowY < bottom) bottom = nowY;
	}

	for (int y = bottom; y <= top; y++)
	{
		std::vector<int> intersections;
		for (int i = 0; i < VertexNum; i++)
		{
			int cury = Vertices[i][1], nexty = Vertices[(i + 1) % VertexNum][1];
			int curx = Vertices[i][0], nextx = Vertices[(i + 1) % VertexNum][0];
			int prex = Vertices[(i - 1) % VertexNum][0], prey = Vertices[(i - 1) % VertexNum][1];
			if ((cury - y) * (y - nexty) > 0)
			{
				int x = round(nextx - double((nexty - y) * (nextx - curx)) / (nexty - cury));
				intersections.emplace_back(x);
			}
			if (cury - y == 0)
			{
				if ((prey - cury) * (cury - nexty) < 0 || (cury == nexty)) continue;
				intersections.emplace_back(curx);
			}
		}
		sort(intersections.begin(), intersections.end());
		for (auto it = intersections.begin(); it != intersections.end() && it + 1 != intersections.end(); it += 2)
		{
			for (int i = *it; i <= *(it + 1); i++)
				DrawPixel(i, y);
		}
	}
}



/*********************************************************************
���ܣ���Ч�߱�ת���㷨
	  
����˵����
	 vertices[][2]---�����б�
	 VertexNum    ---������Ŀ
��ע��
     DrawPixel(int x, int y) --�������ص�(x, y)
**********************************************************************/
void  CPolygon_ConversionView::Active_Edge_Table_Conersion(int Vertices[][2], int VertexNum)
{
	//int top = INT_MIN, bottom = INT_MAX;
	//for (int i = 0; i < VertexNum; i++)
	//{
	//	int nowY = Vertices[i][1];
	//	if (nowY > top) top = nowY;
	//	if (nowY < bottom) bottom = nowY;
	//}
	//std::unordered_map<int, std::list<Node>> ET;
	//for (int i = 0; i < VertexNum; i++)
	//{
	//	int cury = Vertices[i][1], nexty = Vertices[(i + 1) % VertexNum][1];
	//	int curx = Vertices[i][0], nextx = Vertices[(i + 1) % VertexNum][0];
	//	double k_r = double(nextx - curx) / (nexty - cury);
	//	if (cury < nexty)
	//	{
	//		Node node(curx, cury, nexty, k_r);
	//		if (ET.find(cury) != ET.end()) ET[cury].emplace_back(node);
	//		else ET[cury] = { node };
	//	}
	//	if (nexty < cury)
	//	{
	//		Node node(nextx, nexty, cury, k_r);
	//		if (ET.find(nexty) != ET.end()) ET[nexty].emplace_back(node);
	//		else ET[nexty] = { node };
	//	}
	//}
	//std::list<Node> sub_ET = ET[bottom];
	//for (int y = bottom + 1; y <= top; y++)
	//{
	//	if (ET.find(y) != ET.end())
	//	{
	//		for (auto it = sub_ET.begin(); it != sub_ET.end();)
	//		{
	//			if (it->ymax <= y) it = sub_ET.erase(it);
	//			else it++;
	//		}
	//		for (auto item : ET[y]) sub_ET.emplace_back(item);
	//	}
	//	std::vector<int> intersections;
	//	for (auto item : sub_ET)
	//	{
	//		if (y<item.ymin || y>item.ymax) continue;
	//		int x = item.xymin + round(item.uwk * (y - item.ymin));
	//		intersections.emplace_back(x);
	//	}
	//	sort(intersections.begin(), intersections.end());
	//	for (auto it = intersections.begin(); it != intersections.end(); it += 2)
	//	{
	//		for (int i = *it; i <= *(it + 1); i++)
	//			DrawPixel(i, y);
	//	}
	//}
	//return;

	int top = INT_MIN, bottom = INT_MAX;
	for (int i = 0; i < VertexNum; i++)
	{
		int nowY = Vertices[i][1];
		if (nowY > top) top = nowY;
		if (nowY < bottom) bottom = nowY;
	}
	std::unordered_map<int, std::vector<Node>> ET;
	for (int i = 0; i < VertexNum; i++)
	{
		int cury = Vertices[i][1], nexty = Vertices[(i + 1) % VertexNum][1];
		int curx = Vertices[i][0], nextx = Vertices[(i + 1) % VertexNum][0];
		double k_r = double(nextx - curx) / (nexty - cury);
		if (cury < nexty)
		{
			Node node(curx, cury, nexty, k_r);
			if (ET.find(cury) != ET.end()) ET[cury].emplace_back(node);
			else ET[cury] = { node };
		}
		if (nexty < cury)
		{
			Node node(nextx, nexty, cury, k_r);
			if (ET.find(nexty) != ET.end()) ET[nexty].emplace_back(node);
			else ET[nexty] = { node };
		}
	}
	std::vector<Node> sub_ET = ET[bottom];
	for (int y = bottom + 1; y <= top; y++)
	{
		if (ET.find(y) != ET.end())
		{
			for (auto it = sub_ET.begin(); it != sub_ET.end();)
			{
				if (it->ymax <= y) it = sub_ET.erase(it);
				else it++;
			}
			for (auto item : ET[y]) sub_ET.emplace_back(item);
		}
		std::vector<int> intersections;
		for (auto item : sub_ET)
		{
			if (y<item.ymin || y>item.ymax) continue;
			int x = item.xymin + round(item.uwk * (y - item.ymin));
			intersections.emplace_back(x);
		}
		sort(intersections.begin(), intersections.end());
		for (auto it = intersections.begin(); it != intersections.end(); it += 2)
		{
			for (int i = *it; i <= *(it + 1); i++)
				DrawPixel(i, y);
		}
	}
	return;
}