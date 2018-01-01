#include "stdafx.h"
#include "CEnchantmentGenerator.h"
#include "CRacketEnchantment.h"


CEnchantmentGenerator::CEnchantmentGenerator(CGameController* game)
{
	this->game = game;
}

CEnchantmentGenerator::~CEnchantmentGenerator()
{
}

int randNum(int min, int max)
{
	return rand() % max + min;
}

bool ShouldGenerate()
{
	return randNum(0, 1000) < 2;
}


void CEnchantmentGenerator::TryToGenerate()
{
	Position2D leftBottom = { 20, 20 };
	Position2D rightTop = { GAME_WIDTH - 20, GAME_HEIGHT - 20 };

	if(ShouldGenerate())
	{
		Position2D p = { randNum(leftBottom.x, rightTop.x), randNum(leftBottom.y, rightTop.y) };
		CRacketEnchantment* e = new CRacketEnchantment(p, 20, 20, randNum(-10, 20));

		std::cout << e->enchantValue << std::endl;
		//Max 5 enchantments at once
		if(game->enchantments.size() >= 5)
		{
			delete game->enchantments[0];
			game->enchantments.erase(game->enchantments.begin());
		}

		game->enchantments.push_back(e);
	}
}


