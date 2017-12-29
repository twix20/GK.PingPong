#pragma once

struct Position2D
{
	int x;
	int y;

	Position2D()
	{
		this->x = 0;
		this->y = 0;
	}

	Position2D(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	}
};