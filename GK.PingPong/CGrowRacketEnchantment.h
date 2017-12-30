#pragma once
#include "CEnchantment.h"

class CGrowRacketEnchantment : public CEnchantment
{
public:
	int width, height;

	CGrowRacketEnchantment(Position2D position2, int width, int height);
	~CGrowRacketEnchantment();

	void DrawMe() override;
	bool IsCollision(CBall* ball) override;
	void DoOnCollision(CGameController* game) override;
};

