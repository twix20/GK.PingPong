#pragma once
#include "CGameController.h"

class CEnchantmentGenerator
{
public:
	CGameController* game;

	CEnchantmentGenerator(CGameController* game);
	~CEnchantmentGenerator();

	void TryToGenerate();
};

