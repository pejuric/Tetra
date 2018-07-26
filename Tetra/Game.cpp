#include "stdafx.h"
#include "Tetra.h"
#include "TetraDoc.h"
#include "TetraView.h"
#include "TetraBoard.h"
#include "Game.h"

Game::Game()
{
	gameState = 0;
	m_board.SetupBoard();
}
Game::~Game(){}
/////////////////////////////////////////////////////////////////////////////////////////////
void Game::NewGame()
{
	gameState = 0;
	m_board.SetupBoard();
	gameOver = false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::GameTick(CPoint cord)
{
	if (gameOver)
		return false;
	switch(gameState)
	{
	case 0: if (SelectCard(cord)) gameState = 1; return true;
	case 1: if (PlaceCard(cord)) gameState = 2; return true;
	case 2: if (SelectCard(cord)) gameState = 3; return true;
	case 3: if (PlaceCard(cord)) gameState = 0; return true;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::IsFieldZero(int x, int y)
{
	return m_board.GetArrValue(x,y) == 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::SelectCard(CPoint cord)
{
	int x, y;
	x = cord.x / m_board.GetWidth(); y = cord.y / m_board.GetHeight();

	if (gameState != 0 && gameState != 2)
		return false;
	if (gameState == 0)
		if (x != 0)
			return false;
	if (gameState == 2)
		if (x != m_board.GetColumns()-1)
			return false;
	if(IsFieldZero(x,y))
		return false;

	selected_Card = m_board.GetArrValue(x, y);
	m_board.SetArrValue(x, y, 0);
	//	InvalidateRect(); TODO
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::PlaceCard(CPoint cord)
{
	int x, y; x = cord.x / m_board.GetWidth(); y = cord.y / m_board.GetHeight();
	if (gameState != 1 && gameState != 3)
		return false;
	if (x==0 || x==m_board.GetColumns()-1 || gameOver || !IsFieldZero(x,y))
		return false;
	m_board.SetArrValue(x, y, selected_Card);
//	InvalidateRect(); TODO
	return true;
}

