#pragma once

#include <vector>
#include <GLFW/glfw3.h>

#include <Windows.h>
#include <iostream>

#include "CBall.h"
#include "CRacket.h"
#include "CScoreBoard.h"
//#include "CEnchantmentGenerator.h"

//#include "CEnchantment.h"

#define RACKET_INIT_WIDTH 10
#define RACKET_INIT_HEIGHT 100
#define RACKET_INIT_SPEED 7

#define GAME_WIDTH 450
#define GAME_HEIGHT 450

typedef void(*KeysCallback)(GLFWwindow*, int, int, int, int);

class CEnchantment;
class CEnchantmentGenerator;
class CGameController
{
public:

	CRacket* racketLeft;
	CRacket* racketRight;

	CBall* ball;
	CScoreBoard* scoreBoard;

	std::vector<CEnchantment*> enchantments;
	CEnchantmentGenerator* enchantment_generator;

	double time;

	float StoredVelocity = 0.0f;

	//ball Speed
	double TimeSpeed = 0.2;

	CGameController();
	~CGameController();

	void DrawAll() const;

	void Start(KeysCallback keysCb);
	void Reset();

	void Collisions();
	static bool Between(int target, int min, int max);
};

