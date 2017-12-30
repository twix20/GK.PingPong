#include "stdafx.h"
#include "CRacket.h"
#include "gl_helper.h"


CRacket::CRacket(const Position2D position, const int width, const int height, const int racketSpeed) : CObject2D(position)
{
	this->racketSpeed = racketSpeed;
	this->width = width;
	this->height = height;
}


CRacket::~CRacket()
{
}

void CRacket::DrawMe()
{
	gl_helper::DrawRect(pos.x, pos.y, width, height);
}
