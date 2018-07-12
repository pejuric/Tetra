#include "stdafx.h"
#include "TetraBoard.h"
#include <vector>


TetraBoard::TetraBoard():m_nColumns(5),m_nRows(5),m_nHeight(100),m_nWidth(100)
{}


TetraBoard::~TetraBoard()
{
	DeleteBoard();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::SetupBoard()
{
	if (m_arrBoard.empty())
		CreateBoard();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::CreateBoard()
{
	m_arrBoard.resize(m_nColumns);
	if (!m_arrBoard.empty())
		DeleteBoard();
	std::vector<int> filler(m_nRows);
	fill(filler.begin(), filler.end(), 0);
	for (int i = 0; i < m_nColumns; ++i)
		m_arrBoard.push_back(filler);
	filler.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::DeleteBoard()
{
	if (!m_arrBoard.empty())
	{
		m_arrBoard.clear();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TetraBoard::IsEmpty()
{
	return m_arrBoard.empty();
}