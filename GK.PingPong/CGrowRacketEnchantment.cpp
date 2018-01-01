#include "stdafx.h"
#include "CRacketEnchantment.h"
#include "gl_helper.h"
#include "CGameController.h"
#include "collision_helper.h"


CRacketEnchantment::CRacketEnchantment(const Position2D position, const int width, const int height, int enchantValue) : CEnchantment(position)
{
	this->width = width;
	this->height = height;
	this->enchantValue = enchantValue;
}
CRacketEnchantment::~CRacketEnchantment()
{
}

void CRacketEnchantment::DrawMe()
{
	if(enchantValue < 0)
		gl_helper::SetColor(1.0, 0, 0);
	else
		gl_helper::SetColor(0, 1.0, 0);

	gl_helper::DrawRect(pos.x, pos.y, width, height);
}

bool CRacketEnchantment::IsCollision(CBall* ball)
{
	const bool isCollision = collision_helper::is_collision(this->pos, width, height, ball->pos, ball->radius);
	return isCollision;
}

void CRacketEnchantment::DoOnCollision(CGameController* game)
{
	if(game->ball->RacketLastTouched != nullptr)
	{
		const int heightAfter = (*game->ball->RacketLastTouched)->height + enchantValue;
		if (heightAfter > 300 || heightAfter < 50)
			return;

		(*game->ball->RacketLastTouched)->height += enchantValue;
	}
}

