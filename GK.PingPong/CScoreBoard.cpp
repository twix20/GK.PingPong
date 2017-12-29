#include "stdafx.h"
#include "CScoreBoard.h"
#include "gl_helper.h"


CScoreBoard::CScoreBoard(const Position2D position) : CObject2D(position)
{
}


CScoreBoard::~CScoreBoard()
{
}

bool CScoreBoard::ShouldGameEnd() const
{
	return LeftScore > 9 || RightScore > 9;
}

void CScoreBoard::Reset()
{
	LeftScore = RightScore = 0;
}

void CScoreBoard::DrawMe()
{
	//Left Score
	gl_helper::DrawNumber(pos.x - 40, pos.y, LeftScore);

	//Right Score
	gl_helper::DrawNumber(pos.x + 10, pos.y, RightScore);

	//Colon
	gl_helper::DrawRect(pos.x - 2, pos.y + 10, 5, 5);
	gl_helper::DrawRect(pos.x - 2, pos.y + 35, 5, 5);
}
