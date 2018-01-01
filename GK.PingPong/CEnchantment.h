#pragma once
#include "CGameController.h"

class CEnchantment : public CObject2D
{
public:
	CEnchantment(Position2D position);
	~CEnchantment();

	virtual void DrawMe() = 0;
	virtual bool IsCollision(CBall* ball) = 0;
	virtual void DoOnCollision(CGameController* game) = 0;
};

