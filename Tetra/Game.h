#pragma once



class Game
{
private:
	int selected_Card;
	int gameState;
	int placedCards;
	int won;
	int chance;
public:
	bool gameStarted;
	bool gameOver;
	TetraBoard m_board;
	Game();
	~Game();
	void NewGame();
	void RedWin();
	void BlueWin();
	bool GameTick(CPoint cord);
	bool IsFieldZero(int x, int y);
	bool SelectCard(CPoint cord);
	bool PlaceCard(CPoint cord);
	bool CheckForTheEnemy(int x1, int y1, int x2, int y2);
	bool RollForVictory(int us, int them);

};
