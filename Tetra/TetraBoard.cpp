#include "stdafx.h"
#include "TetraBoard.h"
#include <vector>
#include <algorithm>


TetraBoard::TetraBoard():m_nColumns(6),m_nRows(5),m_nWidth(165),m_nHeight(125)
{}

TetraBoard::~TetraBoard()
{
	DeleteBoard();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TetraBoard::SetupBoard()
{
	if (m_arrBoard.empty())
		CreateBoard();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TetraBoard::CreateBoard()
{
	m_arrBoard.resize(m_nColumns);
	if (!m_arrBoard.empty())
		DeleteBoard();
	std::vector<int> filler(m_nRows);
	std::vector<int> filler2(m_nRows);
	std::vector<int> filler3(m_nRows);
	
	fill(filler.begin(), filler.end(), 0);
	generate(filler2.begin(), filler2.end(), [n = 1]()mutable{ return n++; });
	generate(filler3.begin(), filler3.end(), [n = 6]()mutable{ return n++; });
	m_arrBoard.push_back(filler2);
	for (int i = 0; i < m_nColumns-2; ++i)
		m_arrBoard.push_back(filler);
	m_arrBoard.push_back(filler3);
	filler.clear();
	filler2.clear();
	filler3.clear();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RECT TetraBoard::GetBoardRect(int x,int y)
{
	RECT cord;
	/*if (!m_arrBoard[x][y])
		return cord;*/
	try 
	{
		cord.left = x * m_nWidth;
		cord.right = x * m_nWidth + m_nWidth;
		cord.top = y * m_nHeight;
		cord.bottom = y * m_nHeight + m_nHeight;
	}
	catch(...){}
	return cord;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TetraBoard::DeleteBoard()
{
	if (!m_arrBoard.empty())
	{
		m_arrBoard.clear();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TetraBoard::IsEmpty()
{
	return m_arrBoard.empty();
}

int TetraBoard::GetArrValue(int x, int y)
{
	return m_arrBoard[x][y];
}
