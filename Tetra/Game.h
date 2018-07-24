#pragma once



class Game
{
private:
	int selected_Card;
	int playerOnTurn;
	TetraBoard m_board;
	CTetraDoc* pDoc;
public:
	Game();
	~Game();
	bool isFieldFree(int x, int y);
	bool selectCard();
	bool placeCard();
};