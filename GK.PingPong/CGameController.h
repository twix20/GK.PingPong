#pragma once
#include <GLFW/glfw3.h>

#include <Windows.h>

#include <iostream>
#include "CBall.h"
#include "CRacket.h"
#include "CScoreBoard.h"

#define RACKET_INIT_WIDTH 10
#define RACKET_INIT_HEIGHT 100
#define RACKET_INIT_SPEED 7

const int gameWidth = 450, gameHeight = 450;

typedef void(*KeyCallback)(GLFWwindow*, int, int, int, int);


class CGameController
{
public:

	CRacket* racketLeft;
	CRacket* racketRight;

	CBall* ball;
	CScoreBoard* scoreBoard;

	double time;

	float StoredVelocity = 0.0f;

	//ball Speed
	double TimeSpeed = 0.2;

	CGameController();
	~CGameController();

	void Start(KeyCallback keyCb);

	void Reset();
	void Collisions();
	static bool Between(int target, int min, int max);
};

