#include "stdafx.h"
#include "TetraBoard.h"


TetraBoard::TetraBoard():m_nColumns(5),m_nRows(5),m_nHeight(35),m_nWidth(35)
{}


TetraBoard::~TetraBoard()
{
	DeleteBoard();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::SetupBoard()
{
	if (m_arrBoard == NULL)
		CreateBoard();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::CreateBoard()
{
	if (m_arrBoard != NULL)
		DeleteBoard();
	m_arrBoard = new int*[m_nRows];
	for (int row = 0; row < m_nRows; row++)
	{
		m_arrBoard[row] = new int[m_nColumns];
		for (int col = 0; col < m_nColumns; col++)
			m_arrBoard[row][col] = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void TetraBoard::DeleteBoard()
{
	if (m_arrBoard != NULL)
	{
		for (int row = 0; row < m_nRows; row++)
		{
			if (m_arrBoard[row] != NULL)
			{
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int TetraBoard::IsEmpty(int row, int col)
{
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return 0;
	if (m_arrBoard[row][col] == 0)
		return 1;
	return 0;
}