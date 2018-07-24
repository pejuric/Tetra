#include "stdafx.h"
#include "Tetra.h"
#include "TetraDoc.h"
#include "TetraView.h"
#include "TetraBoard.h"
#include "Game.h"

Game::Game()
{
	Game::pDoc = CTetraDoc::GetDoc();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	Game::m_board = pDoc->m_board;
}


bool Game::isFieldFree(int x, int y)
{
	return m_board.GetArrValue(x,y) == 0;
}
