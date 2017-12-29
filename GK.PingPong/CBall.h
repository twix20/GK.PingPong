#pragma once
#include "Position2D.h"
#include "CObject2D.h"
#include "CRacket.h"

class CBall : public CObject2D
{
public:
	float radius;
	float velocityX, velocityY;

	CBall(Position2D position, float radius) ;
	~CBall();

	void DrawMe() override;
};

