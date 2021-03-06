#include "stdafx.h"

#include <Windows.h>

//#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CBall.h"
#include "CRacket.h"
#include "CScoreBoard.h"
#include "CRacketEnchantment.h"
#include "gl_helper.h"
#include "collision_helper.h"

#include "CGameController.h"


class CEnchantmentGenerator
{
public:
	CEnchantmentGenerator(CGameController* c);
	void TryToGenerate();
};

CGameController::CGameController()
{
	racketLeft = new CRacket({0, GAME_HEIGHT / 2 - 50}, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT, RACKET_INIT_SPEED);
	racketRight = new CRacket({GAME_WIDTH - 10, GAME_HEIGHT / 2 - 50}, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT,
	                          RACKET_INIT_SPEED);

	ball = new CBall({GAME_WIDTH / 2 - 5, GAME_HEIGHT / 2 - 5}, BALL_INIT_RADIUS);
	scoreBoard = new CScoreBoard({GAME_WIDTH / 2, 10});

	time = 0;
	enchantment_generator = new CEnchantmentGenerator(this);
}

CGameController::~CGameController()
{
	delete racketLeft, racketRight;
	delete ball;
	delete scoreBoard;
}

void CGameController::MoveBall()
{
	if(ball->velocityY > MAX_BALL_SPEED)
		ball->velocityY = MAX_BALL_SPEED;
	else if(ball->velocityY < -MAX_BALL_SPEED)
		ball->velocityY = -MAX_BALL_SPEED;


	ball->pos.x += ball->velocityX;
	StoredVelocity += ball->velocityY;


	ball->pos.y += StoredVelocity >= 1.0f ? 1 : -1;
	StoredVelocity += StoredVelocity >= 1.0f ? -1 : 1;
}

void CGameController::DrawAll() const
{
	gl_helper::SetColor(255, 255, 255);
	//Left Racket
	racketLeft->DrawMe();
	//Right Racket
	racketRight->DrawMe();
	//Ball
	ball->DrawMe();
	//Score Board
	scoreBoard->DrawMe();

	for (auto it = enchantments.begin(); it != enchantments.end(); ++it)
	{
		(*it)->DrawMe();
	}
}

void CGameController::Start(const KeysCallback keysCb)
{
	glfwInit();

	//Hints Before Window Creation
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(GAME_WIDTH, GAME_HEIGHT, "PingPong - Piotr Markiewicz 226020", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keysCb);

	time = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {

		//2D Mode		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, GAME_WIDTH, GAME_HEIGHT, 0, 0, 1);
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glClearColor(0.0f, 0.0f, 0.0f, 0);
		glClear(GL_COLOR_BUFFER_BIT);

		//Generate enchantments
		enchantment_generator->TryToGenerate();

		//Move ball
		MoveBall();

		//Collision Detection
		Collisions();

		//Draw objects on screen
		DrawAll();

		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
}

void CGameController::ResetGame()
{
	glfwSetTime(0.0);
	time = 0.0;

	//ResetGame ball
	ball->pos.x = GAME_WIDTH / 2 - ball->radius / 2;
	ball->velocityX = 1;
	ball->velocityY = 0;

	StoredVelocity = 0;

	//ResetGame Rackets
	racketRight->racketSpeed = RACKET_INIT_SPEED;
	racketRight->height = RACKET_INIT_HEIGHT;
	racketRight->width = RACKET_INIT_WIDTH;

	racketLeft->racketSpeed = RACKET_INIT_SPEED;
	racketLeft->height = RACKET_INIT_HEIGHT;
	racketLeft->width = RACKET_INIT_WIDTH;

	//Delete enchantments
	for (int i = 0; i< enchantments.size(); i++)
		delete (enchantments[i]);
	enchantments.clear();

	if (scoreBoard->ShouldGameEnd()) {
		scoreBoard->Reset();
	}
}

void CGameController::Collisions() {

	//TODO: To do racket?
	if (ball->pos.x > GAME_WIDTH - racketRight->width * 2) { //ball at Right Edge

		if (collision_helper::Between(ball->pos.y, racketRight->pos.y + racketRight->height, racketRight->pos.y)) {

			ball->RacketLastTouched = &racketRight;
			ball->velocityX = -ball->velocityX;

			if (collision_helper::Between(ball->pos.y, racketRight->pos.y, racketRight->pos.y + racketRight->height * 0.3)) {

				ball->velocityY -= 0.3;

			}
			else if (collision_helper::Between(ball->pos.y, racketRight->pos.y + racketRight->height - racketRight->height * 0.3, racketRight->pos.y + racketRight->height)) {

				ball->velocityY += 0.3;
			}
		}
		else {
			scoreBoard->LeftScore++;
			ResetGame();
		}
	}
	else if (ball->pos.x - racketLeft->width < racketLeft->width) { //ball at Left Edge

		if (collision_helper::Between(ball->pos.y, racketLeft->pos.y + racketLeft->height, racketLeft->pos.y)) {

			ball->RacketLastTouched = &racketLeft;
			ball->velocityX = -ball->velocityX;

			if (collision_helper::Between(ball->pos.y, racketLeft->pos.y, racketLeft->pos.y + racketLeft->height * 0.3)) {

				ball->velocityY -= 0.3;

			}
			else if (collision_helper::Between(ball->pos.y, racketLeft->pos.y + racketLeft->height - racketLeft->height * 0.3, racketLeft->pos.y + racketLeft->height)) {

				ball->velocityY += 0.3;
			}

		}
		else {
			scoreBoard->RightScore++;
			ResetGame();
		}
	}

	if (static_cast<int>(ball->pos.y - ball->radius) < 0) { //ball at Top Edge

		ball->pos.y = ball->radius + 5;
		ball->velocityY = -ball->velocityY;

		StoredVelocity += StoredVelocity >= 1.0f ? -1 : 1;
	}
	if (ball->pos.y > static_cast<int>(GAME_HEIGHT - ball->radius)) { //ball at Bottom Edge

		ball->pos.y = GAME_HEIGHT - ball->radius - 5;
		ball->velocityY = -ball->velocityY;

		StoredVelocity += StoredVelocity >= 1.0f ? -1 : 1;
	}

	//Enchantments collision
	auto it = enchantments.begin();
	while (it != enchantments.end())
	{
		if ((*it)->IsCollision(ball))
		{
			(*it)->DoOnCollision(this);
			it = enchantments.erase(it);
		}
		else
		{
			++it;
		}
	}
}