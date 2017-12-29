#pragma once
#include "CObject2D.h"

class CScoreBoard : CObject2D
{
public:
	int LeftScore = 0;
	int RightScore = 0;


	CScoreBoard(Position2D position);
	~CScoreBoard();

	bool ShouldGameEnd() const;
	void Reset();

	void DrawMe() override;
};

