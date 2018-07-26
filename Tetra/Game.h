#pragma once



class Game
{
private:
	int selected_Card;
	int gameState;
	bool gameOver;
//	CTetraDoc* pDoc;
public:
	TetraBoard m_board;
	Game();
	~Game();
	void NewGame();
	bool GameTick(CPoint cord);
	bool IsFieldZero(int x, int y);
	bool SelectCard(CPoint cord);
	bool PlaceCard(CPoint cord);
};
