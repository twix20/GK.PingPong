#include "stdafx.h"
#include "CGrowRacketEnchantment.h"
#include "gl_helper.h"
#include "CGameController.h"


CGrowRacketEnchantment::CGrowRacketEnchantment(const Position2D position, const int width, const int height) : CEnchantment(position)
{
	this->width = width;
	this->height = height;
}

void CGrowRacketEnchantment::DrawMe()
{
	gl_helper::SetColor(1.0, 0, 0);
	gl_helper::DrawRect(pos.x, pos.y, 4, 4);
}

bool CGrowRacketEnchantment::IsCollision(CBall* ball)
{
	return false;
}

void CGrowRacketEnchantment::DoOnCollision(CGameController* game)
{
	//if(game->ball->RacketLastTouched != nullptr)
	//{
	//	//game->ball->RacketLastTouched->height += 30;
	//}
}

CGrowRacketEnchantment::~CGrowRacketEnchantment()
{
}
