#pragma once
#include "CObject2D.h"

class CRacket : public CObject2D
{
public:
	int width, height;

	CRacket(Position2D position, int width, int height);
	~CRacket();
	void DrawMe() override;
};

