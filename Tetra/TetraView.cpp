
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
			bmp.LoadBitmap(310 + pDoc->game.m_board.GetArrValue(i, j));

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
