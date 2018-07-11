
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

void CTetraView::OnDraw(CDC* /*pDC*/)
{
	CTetraDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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
