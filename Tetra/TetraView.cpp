
// TetraView.cpp : implementation of the CTetraView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Tetra.h"
#endif

#include "TetraDoc.h"
#include "TetraView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetraView

IMPLEMENT_DYNCREATE(CTetraView, CView)

BEGIN_MESSAGE_MAP(CTetraView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CTetraView construction/destruction

CTetraView::CTetraView()
{
	// TODO: add construction code here

}

CTetraView::~CTetraView()
{
}

BOOL CTetraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTetraView drawing

void CTetraView::OnDraw(CDC* pDC)
{
	CTetraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/////////////////////////////////////////////////////////////
	PaintCards(pDC);
	/////////////////////////////////////////////////////////////
}


// CTetraView diagnostics

#ifdef _DEBUG
void CTetraView::AssertValid() const
{
	CView::AssertValid();
}

void CTetraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetraDoc* CTetraView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetraDoc)));
	return (CTetraDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetraView message handlers


void CTetraView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
/////////////////////////////////////////////////
	ResizeWindow();
//////////////////////////////////////////////////
}

void CTetraView::ResizeWindow()
{
	//  First get a pointer to the document
	CTetraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void CTetraView::PaintCards(CDC* cDC)
{
	CTetraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CBitmap bmp;
	CRect rec;
	for(int i=0;i<pDoc->game.m_board.GetColumns();++i)
		for (int j = 0; j < pDoc->game.m_board.GetRows(); ++j)
		{
			switch (pDoc->game.m_board.GetArrValue(i, j))
			{	
				case 0:bmp.LoadBitmapW(IDB_BITMAP00); break;
				case 1:bmp.LoadBitmapW(IDB_BITMAP1);  break;
				case 2:bmp.LoadBitmapW(IDB_BITMAP2);  break;
				case 3:bmp.LoadBitmapW(IDB_BITMAP3);  break;
				case 4:bmp.LoadBitmapW(IDB_BITMAP4);  break;
				case 5:bmp.LoadBitmapW(IDB_BITMAP5);  break;
				case 6:bmp.LoadBitmapW(IDB_BITMAP6);  break;
				case 7:bmp.LoadBitmapW(IDB_BITMAP7);  break;
				case 8:bmp.LoadBitmapW(IDB_BITMAP8);  break;
				case 9:bmp.LoadBitmapW(IDB_BITMAP9);  break;
				case 10:bmp.LoadBitmapW(IDB_BITMAP10);break;
				case 11:bmp.LoadBitmapW(IDB_BITMAP12);break;
				case 12:bmp.LoadBitmapW(IDB_BITMAP13);break;
				case 13:bmp.LoadBitmapW(IDB_BITMAP14);break;
				case 14:bmp.LoadBitmapW(IDB_BITMAP15);break;
				case 15:bmp.LoadBitmapW(IDB_BITMAP16);break;
				case 16:bmp.LoadBitmapW(IDB_BITMAP17);break;
				case 17:bmp.LoadBitmapW(IDB_BITMAP18);break;
				case 18:bmp.LoadBitmapW(IDB_BITMAP19);break;
				case 19:bmp.LoadBitmapW(IDB_BITMAP20);break;
				case 20:bmp.LoadBitmapW(IDB_BITMAP21);break;
				case 21:bmp.LoadBitmapW(IDB_BITMAP22); break;
				case 22:bmp.LoadBitmapW(IDB_BITMAP23); break;
				case 25:bmp.LoadBitmapW(IDB_BITMAP25); break;
				case 26:bmp.LoadBitmapW(IDB_BITMAP26); break;
				case 27:bmp.LoadBitmapW(IDB_BITMAP27); break;
				case 28:bmp.LoadBitmapW(IDB_BITMAP28); break;
			}

			CBrush brush(&bmp);
			rec = pDoc->game.m_board.GetBoardRect(i, j);
			cDC->SetBrushOrg(rec.left, rec.top);
			cDC->FillRect(rec, &brush);
			bmp.DeleteObject();
		}	
}
/////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////


void CTetraView::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool turn;
	CTetraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CRect myRect;
	if (!pDoc)
		return;
	turn = pDoc->game.GameTick(point);
	if (turn) 
	{
		myRect = pDoc->game.m_board.GetBoardWideRectFromPoint(point);
		InvalidateRect(CRect(myRect.left, myRect.top, myRect.right, myRect.bottom));
	}
	if (pDoc->game.gameOver)
		InvalidateRect(CRect(0, 0, (pDoc->game.m_board.GetColumns()*pDoc->game.m_board.GetWidth()), (pDoc->game.m_board.GetRows()*pDoc->game.m_board.GetHeight())));
	
	CView::OnLButtonDown(nFlags, point);
}
