
// TetraDoc.h : interface of the CTetraDoc class
//


#pragma once

#include "TetraBoard.h"


class CTetraDoc : public CDocument
{
protected: // create from serialization only
	CTetraDoc();
	DECLARE_DYNCREATE(CTetraDoc)

// Attributes
public:

// Operations
public:
	/*  Functions for accessing the game board */

	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CTetraDoc();
////////////////////////////////////////////////////////////////
	static CTetraDoc * GetDoc();
	TetraBoard m_board;
////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
