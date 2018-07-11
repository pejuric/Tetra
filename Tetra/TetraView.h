
// TetraView.h : interface of the CTetraView class
//

#pragma once


class CTetraView : public CView
{
protected: // create from serialization only
	CTetraView();
	DECLARE_DYNCREATE(CTetraView)

// Attributes
public:
	CTetraDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CTetraView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TetraView.cpp
inline CTetraDoc* CTetraView::GetDocument() const
   { return reinterpret_cast<CTetraDoc*>(m_pDocument); }
#endif

