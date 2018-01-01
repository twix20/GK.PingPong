#pragma once
#include "CEnchantment.h"

class CRacketEnchantment : public CEnchantment
{
public:
	int width, height;
	int enchantValue;

	CRacketEnchantment(Position2D position2, int width, int height, int enchantValue);
	~CRacketEnchantment();

	void DrawMe() override;
	bool IsCollision(CBall* ball) override;
	void DoOnCollision(CGameController* game) override;
};

