#include "stdafx.h"

#include "collision_helper.h"
#include <cmath>


collision_helper::collision_helper()
{
}


collision_helper::~collision_helper()
{
}

bool collision_helper::is_collision(Position2D rectLeftBottom, int rectWidth, int rectHeigh,
	Position2D circlePos, int circleRadius)
{
	Position2D circleDistance;

	circleDistance.x = abs(circlePos.x - (rectLeftBottom.x + rectWidth / 2));
	circleDistance.y = abs(circlePos.y - rectLeftBottom.y);

	if (circleDistance.x > (rectWidth / 2 + circleRadius)) { return false; }
	if (circleDistance.y > (rectHeigh / 2 + circleRadius)) { return false; }

	if (circleDistance.x <= (rectWidth / 2)) { return true; }
	if (circleDistance.y <= (rectHeigh / 2)) { return true; }

	return false;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int min(int a, int b)
{
	return a > b ? b : a;
}
bool collision_helper::Between(const int target, int a, int b) {

	const int ma = max(a, b);
	const int mi = min(a, b);

	return target < ma && target > mi;
}


