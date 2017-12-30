#include "stdafx.h"
#include "CGameController.h"

#include <Windows.h>

//#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CBall.h"
#include "CRacket.h"
#include "CScoreBoard.h"


CGameController::CGameController()
{
	racketLeft = new CRacket({ 0, gameHeight / 2 - 50 }, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT, RACKET_INIT_SPEED);
	racketRight = new CRacket({ gameWidth - 10, gameHeight / 2 - 50 }, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT, RACKET_INIT_SPEED);

	ball = new CBall({ gameWidth / 2 - 5, gameHeight / 2 - 5 }, 10.0f);
	scoreBoard = new CScoreBoard({ gameWidth / 2, 10 });
}


CGameController::~CGameController()
{
	delete racketLeft, racketRight;
	delete ball;
	delete scoreBoard;
}

void CGameController::Start(KeyCallback keyCb)
{
	glfwInit();

	//Hints Before Window Creation
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(gameWidth, gameHeight, "PingPong", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCb);

	time = glfwGetTime()*TimeSpeed;

	while (!glfwWindowShouldClose(window)) {

		//2D Mode		
		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		glOrtho(0, gameWidth, gameHeight, 0, 0, 1);

		glDisable(GL_DEPTH_TEST);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glClearColor(0.0f, 0.0f, 0.0f, 0);

		glClear(GL_COLOR_BUFFER_BIT);

		//Collision Detection
		Collisions();

		//Left Racket
		this->racketLeft->DrawMe();
		//Right Racket
		this->racketRight->DrawMe();
		//ball
		this->ball->DrawMe();
		//Score
		this->scoreBoard->DrawMe();

		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();


}

void CGameController::Reset()
{
	glfwSetTime(0.0);
	time = 0.0;

	//Reset ball
	this->ball->pos.x = gameWidth / 2 - ball->radius / 2;
	this->ball->velocityX = 1;
	this->ball->velocityY = 0;

	StoredVelocity = 0;

	//Reset Rackets
	this->racketRight->racketSpeed = RACKET_INIT_SPEED;
	this->racketRight->height = RACKET_INIT_HEIGHT;
	this->racketRight->width = RACKET_INIT_WIDTH;

	this->racketLeft->racketSpeed = RACKET_INIT_SPEED;
	this->racketLeft->height = RACKET_INIT_HEIGHT;
	this->racketLeft->width = RACKET_INIT_WIDTH;

	if (this->scoreBoard->ShouldGameEnd()) {
		this->scoreBoard->Reset();
	}
}

void CGameController::Collisions() {

	if (glfwGetTime() - time > 1.0) {

		time = glfwGetTime()*TimeSpeed;

		this->ball->pos.x += this->ball->velocityX;

		StoredVelocity += this->ball->velocityY;

		if (StoredVelocity > 1.0f) {
			this->ball->pos.y += 1;
			StoredVelocity -= 1;
		}
		else if (StoredVelocity < -1.0f) {
			this->ball->pos.y -= 1;
			StoredVelocity += 1;

		}
	}


	if (this->ball->pos.x > gameWidth - this->racketRight->width * 2) { //ball at Right Edge

		if (Between(this->ball->pos.y, this->racketRight->pos.y + this->racketRight->height, this->racketRight->pos.y)) {

			this->ball->RacketLastTouched = &racketRight;
			this->ball->velocityX = -ball->velocityX;

			if (Between(this->ball->pos.y, this->racketRight->pos.y, this->racketRight->pos.y + this->racketRight->height * 0.3)) {

				this->ball->velocityY -= 0.3;

			}
			else if (Between(this->ball->pos.y, this->racketRight->pos.y + this->racketRight->height - this->racketRight->height * 0.3, this->racketRight->pos.y + this->racketRight->height)) {

				this->ball->velocityY += 0.3;
			}
		}
		else {

			this->scoreBoard->LeftScore++;
			Reset();
		}
	}
	else if (this->ball->pos.x - this->racketLeft->width < this->racketLeft->width) { //ball at Left Edge

		if (Between(this->ball->pos.y, this->racketLeft->pos.y + this->racketLeft->height, this->racketLeft->pos.y)) {

			this->ball->RacketLastTouched = &racketLeft;
			this->ball->velocityX = -this->ball->velocityX;

			if (Between(ball->pos.y, racketLeft->pos.y, racketLeft->pos.y + racketLeft->height * 0.3)) {

				this->ball->velocityY -= 0.3;

			}
			else if (Between(this->ball->pos.y, this->racketLeft->pos.y + this->racketLeft->height - this->racketLeft->height * 0.3, this->racketLeft->pos.y + this->racketLeft->height)) {

				this->ball->velocityY += 0.3;
			}

		}
		else {

			this->scoreBoard->RightScore++;
			Reset();
		}
	}
	else if (ball->pos.y - ball->radius < 0) { //ball at Top Edge

		this->ball->pos.y = this->ball->radius;
		this->ball->velocityY = -this->ball->velocityY;

	}
	else if (this->ball->pos.y > gameHeight - this->ball->radius) { //ball at Bottom Edge

		this->ball->pos.y = gameHeight - this->ball->radius;
		this->ball->velocityY = -this->ball->velocityY;
	}

}

bool CGameController::Between(const int target, int a, int b) {

	const int max = max(a, b);
	const int min = min(a, b);

	return target < max && target > min;
}
