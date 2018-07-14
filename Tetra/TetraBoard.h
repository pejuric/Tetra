#pragma once
#include <vector>
class TetraBoard
{
public:
	TetraBoard();
	~TetraBoard();
	void SetupBoard();
	RECT GetBoardRect(int x, int y);
	void CreateBoard();
	void DeleteBoard();
	int IsEmpty();
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetColumns() { return m_nColumns; }
	int GetRows() { return m_nRows; }
private:
	std::vector<std::vector<int>> m_arrBoard;
	int m_nWidth;
	int m_nHeight;
	int m_nColumns;
	int m_nRows;
};

