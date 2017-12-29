#include "stdafx.h"
#include "CRacket.h"
#include "gl_helper.h"


CRacket::CRacket(const Position2D position, const int width, const int height) : CObject2D(position)
{
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
