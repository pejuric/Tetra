#pragma once
class TetraBoard
{
public:
	TetraBoard();
	~TetraBoard();
	void SetupBoard();
	int ReturnOccupied();
	void CreateBoard();
	void DeleteBoard();
	int IsEmpty(int row, int col);
	int GetWidth() { return m_nWidth; }
	int GetHeight() { return m_nHeight; }
	int GetColumns() { return m_nColumns; }
	int GetRows() { return m_nRows; }
private:
	int** m_arrBoard;
	int m_nWidth;
	int m_nHeight;
	int m_nColumns;
	int m_nRows;
};

