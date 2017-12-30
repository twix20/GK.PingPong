#pragma once
#include "CObject2D.h"

class CRacket : public CObject2D
{
public:
	int width, height;
	int racketSpeed;

	CRacket(Position2D position, int width, int height, int racketSpeed);
	~CRacket();
	void DrawMe() override;
};

