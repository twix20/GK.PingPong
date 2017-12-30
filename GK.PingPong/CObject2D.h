#pragma once
#include "Position2D.h"

class CObject2D
{
public:
	Position2D pos;

	CObject2D(Position2D position);
	virtual ~CObject2D();

	virtual void DrawMe() = 0;
};

