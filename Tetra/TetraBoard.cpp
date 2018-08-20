#include "stdafx.h"
#include "TetraBoard.h"
#include <vector>
#include <algorithm>


TetraBoard::TetraBoard()//:m_nColumns(6),m_nRows(5),m_nWidth(165),m_nHeight(125)
{
	const TCHAR* filename = _T(".\\Config.ini");
	TCHAR* section = _T("board");
	m_nColumns = GetPrivateProfileInt(section, _T("columns"), 6, filename);
	m_nRows= GetPrivateProfileInt(section, _T("rows"), 5, filename);
	m_nWidth= GetPrivateProfileInt(section, _T("width"), 165, filename);
	m_nHeight= GetPrivateProfileInt(section, _T("height"), 125, filename);
}

TetraBoard::~TetraBoard()
{
	DeleteBoard();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TetraBoard::SetupBoard()
{
	m_arrBoard.clear();
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

RECT TetraBoard::GetBoardWideRectFromPoint(CPoint clickCord)
{
	RECT cord;
	int x, y;
	x = clickCord.x / GetWidth(); y = clickCord.y / GetHeight();
	try
	{
		cord.left = x * m_nWidth - m_nWidth;
		cord.right = x * m_nWidth + m_nWidth + m_nWidth;
		cord.top = y * m_nHeight - m_nHeight;
		if (cord.top < 0)
			cord.top = 0;
		cord.bottom = y * m_nHeight + m_nHeight + m_nHeight;
		if (cord.bottom > (m_nRows - 1)*m_nHeight)
			cord.bottom = y * m_nHeight + m_nHeight;
	}
	catch (...) {}
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
///////////////////////////////////////////////////////////////////////////////
int TetraBoard::GetArrValue(int x, int y)
{
	return m_arrBoard[x][y];
}
///////////////////////////////////////////////////////////////////////////////
void TetraBoard::SetArrValue(int x, int y, int value)
{
	m_arrBoard[x][y] = value;
}
