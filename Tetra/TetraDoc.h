
// TetraDoc.h : interface of the CTetraDoc class
//


#pragma once

#include "TetraBoard.h"
#include "Game.h"

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
/////////////////////////////////////////////////////////////////////////////////////
	int GetWidth(void) { return game.m_board.GetWidth(); }
	int GetHeight(void) { return game.m_board.GetHeight(); }
	int GetColumns(void) { return game.m_board.GetColumns(); }
	int GetRows(void) { return game.m_board.GetRows(); }
	void DeleteBoard(void) { game.m_board.DeleteBoard(); }
////////////////////////////////////////////////////////////////////////////////////
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
	Game game;
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
