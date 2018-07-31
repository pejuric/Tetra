#include "stdafx.h"
#include "Tetra.h"
#include "TetraDoc.h"
#include "TetraView.h"
#include "TetraBoard.h"
#include "Game.h"
#include "time.h"

#define down (x, y, x, y + 1)
#define up (x, y, x, y - 1)
#define left (x, y, x - 1, y)
#define right (x, y, x + 1, y)

Game::Game()
{
	gameStarted = false;
	gameState = 0;
	m_board.SetupBoard();
	gameOver = false;
	placedCards = 0;
	won = 0;
}
Game::~Game(){}
/////////////////////////////////////////////////////////////////////////////////////////////
void Game::NewGame()
{
	gameStarted = false;
	gameState = 0;
	m_board.SetupBoard();
	gameOver = false;
	placedCards = 0;
	won = 0;
	m_board.SetArrValue(1, 0, 27);
	m_board.SetArrValue(2, 2, 27);
	m_board.SetArrValue(3, 2, 27);
	m_board.SetArrValue(1, m_board.GetRows() - 1, 27);
	m_board.SetArrValue(m_board.GetColumns()-2, 0, 27);
	m_board.SetArrValue(m_board.GetColumns() - 2, m_board.GetRows() - 1, 27);
}
void Game::RedWin()
{
		m_board.SetArrValue(m_board.GetColumns()-1, 0, 26);
}
void Game::BlueWin()
{
		m_board.SetArrValue(0, 0, 25);
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::GameTick(CPoint cord)
{
	if (gameOver)
	{
		if (won < 0)
			RedWin();
		if (won > 0)
			BlueWin();
		return false;
	}
	switch(gameState)
	{
	case 0: if (SelectCard(cord)) { gameState = 1; return true; }break;
	case 1: if (PlaceCard(cord)) { gameState = 2; return true; }break;
	case 2: if (SelectCard(cord)) { gameState = 3; return true; }break;
	case 3: if (PlaceCard(cord)) {
		gameState = 0;
		if (gameOver)
		{
			if (won < 0)
				RedWin();
			if (won > 0)
				BlueWin();
			}return true; }break;
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::IsFieldZero(int x, int y)
{
	return m_board.GetArrValue(x,y) == 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::SelectCard(CPoint cord)
{
	gameStarted = true;
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
	if(IsFieldZero(x,y)||m_board.GetArrValue(x,y)>10)
		return false;

	selected_Card = m_board.GetArrValue(x, y);
	m_board.SetArrValue(x, y, selected_Card+10);
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////

bool Game::CheckForTheEnemy(int x1, int y1, int x2, int y2)
{
	
	if(x2<=0||x2>=(m_board.GetColumns()-1)|| y2 < 0 || y2 > (m_board.GetRows()-1))
		return true;
	if (m_board.GetArrValue(x2, y2) == 0 || m_board.GetArrValue(x2, y2) == 27)
		return true;
	int myVal;
	myVal = m_board.GetArrValue(x1, y1);
	int hisVal = m_board.GetArrValue(x2, y2);
	if (hisVal == 21) hisVal = 1;
	if (hisVal == 22) hisVal = 6;

	if (myVal > 5 && hisVal > 5)return true;
	if (myVal < 6 && hisVal < 6)return true;
	if (RollForVictory(myVal, hisVal)) 
	{
		if (myVal < 6) {
			m_board.SetArrValue(x2, y2, 21);
			++won;
		}
		else {
			m_board.SetArrValue(x2, y2, 22);
			--won;
		}
			return true;	
	}
	else 
	{
		if (myVal < 6) {
			m_board.SetArrValue(x1, y1, 22);
			--won;
		}
		else {
			m_board.SetArrValue(x1, y1, 21);
			++won;
		}return false;
	}

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////
bool Game::RollForVictory(int myVal, int hisVal)
{
	int us2, them2;
	if (myVal < 6)
	{
		us2 = myVal + 5;
		them2 = hisVal;
	}
	else
	{
		them2 = hisVal + 5;
		us2 = myVal;
	}
		srand(time(NULL));
	while (1)
	{
		us2 += rand() % 8;
		them2 += rand() % 8;
		if (us2 > them2)
			return true;
		if (us2 < them2)
			return false;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////
bool Game::PlaceCard(CPoint cord)
{
	int x, y; x = cord.x / m_board.GetWidth(); y = cord.y / m_board.GetHeight();
	if (gameState != 1 && gameState != 3)
		return false;
	if (x==0 || x==m_board.GetColumns()-1 || gameOver || !IsFieldZero(x,y))
		return false;
	m_board.SetArrValue(x, y, selected_Card);

	switch(selected_Card)
	{
	case 1:CheckForTheEnemy down; break;
		case 2:
		{
			if (CheckForTheEnemy up)
				CheckForTheEnemy down;
		}break;

		case 3:
		{
			if (CheckForTheEnemy up)
				if (CheckForTheEnemy down)
					CheckForTheEnemy right;
		}break;

		case 4: 
		{
			if (CheckForTheEnemy up)
				if (CheckForTheEnemy down)
					if (CheckForTheEnemy left)
						CheckForTheEnemy right;

		} break;

		case 5: 
		{
			if (CheckForTheEnemy(x, y, x + 1, y - 1))
				if (CheckForTheEnemy(x, y, x + 1, y + 1))
					if (CheckForTheEnemy up)
						if (CheckForTheEnemy down)
							if (CheckForTheEnemy left)
								CheckForTheEnemy right;
		} break;
		case 6: CheckForTheEnemy up; break;
		case 7: 
		{
			if (CheckForTheEnemy up)
				CheckForTheEnemy down;
		} break;

		case 8: 
		{
			if (CheckForTheEnemy up)
				if (CheckForTheEnemy down)
					CheckForTheEnemy left;
		} break;

		case 9: 
		{
			if (CheckForTheEnemy up)
				if (CheckForTheEnemy down)
					if (CheckForTheEnemy left)
						CheckForTheEnemy right;
		} break;

		case 10: 
		{
			if (CheckForTheEnemy(x, y, x - 1, y - 1))
				if (CheckForTheEnemy(x, y, x - 1, y + 1))
					if (CheckForTheEnemy up)
						if (CheckForTheEnemy down)
							if (CheckForTheEnemy left)
								CheckForTheEnemy right;
		} break;
	
	}
	++placedCards;
	if (placedCards == 10)
		gameOver = true;
	return true;
}
