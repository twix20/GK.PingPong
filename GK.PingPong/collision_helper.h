#pragma once
#include "Position2D.h"

class collision_helper
{
public:
	collision_helper();
	~collision_helper();

	static bool is_collision(Position2D rectLeftBottom, int rectWidth, int rectHeigh, Position2D circlePos, int circleRadius);

	static bool Between(const int target, int a, int b);
};

