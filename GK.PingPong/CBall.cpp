#include "stdafx.h"
#include "CBall.h"
#include "gl_helper.h"


CBall::CBall(const Position2D pos, const float radius) : CObject2D(pos)
{
	this->velocityX = 1;
	this->velocityY = 0;

	this->radius = radius;
}

CBall::~CBall()
{
}

void CBall::DrawMe()
{
	gl_helper::DrawCircle(this->pos.x, this->pos.y, this->radius);
}
