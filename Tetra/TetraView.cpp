
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
	PaintCards(pDC);

	// TODO: add draw code for native data here
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

	// TODO: Add your specialized code here and/or call the base class
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

	for(int i=0;i<pDoc->m_board.GetColumns();++i)
		for (int j = 0; j < pDoc->m_board.GetRows(); ++j)
		{
			switch (pDoc->m_board.GetArrValue(i, j))
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
			}

			CBrush brush(&bmp);
			rec = pDoc->m_board.GetBoardRect(i, j);
			cDC->SetBrushOrg(rec.left, rec.top);
			cDC->FillRect(rec, &brush);
			bmp.DeleteObject();
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	
}

