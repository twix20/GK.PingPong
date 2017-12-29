// GK.PingPong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#include <cmath>

//#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "gl_helper.h"
#include "CBall.h"
#include "CRacket.h"

#define RACKET_INIT_WIDTH 10
#define RACKET_INIT_HEIGHT 100
#define RACKET_INIT_SPEED 5

using namespace std;

const int gameWidth = 450, gameHeight = 450;

CBall Ball({0,0}, 10.0f);
CRacket RacketLeft({ 0, 0 }, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT);
CRacket RacketRight({ gameWidth - 10, 0 }, RACKET_INIT_WIDTH, RACKET_INIT_HEIGHT);

double time;

float StoredVelocity = 0.0f;

//Ball Speed
double TimeSpeed = 0.2;

int LeftScore = 0;
int RightScore = 0;

void Reset();
void Collisions();
bool Between(int target, int min, int max);

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {

	//Left Control UP
	if (key == GLFW_KEY_UP) {
		RacketRight.pos.y -= RACKET_INIT_SPEED;
	}
	//Left Control Down
	if (key == GLFW_KEY_DOWN) {
		RacketRight.pos.y += RACKET_INIT_SPEED;
	}
	//Right Control UP
	if (key == GLFW_KEY_W) {
		RacketLeft.pos.y -= RACKET_INIT_SPEED;
	}
	//Right Control Down
	if (key == GLFW_KEY_S) {
		RacketLeft.pos.y += RACKET_INIT_SPEED;
	}

}


int main()
{

	GLFWwindow* window;

	glfwInit();

	//Hints Before Window Creation
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(gameWidth, gameHeight, "Pong", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, KeyCallBack);


	//Ball Starting pos
	Ball.pos.x = gameWidth / 2 - 5;
	Ball.pos.y = gameHeight / 2 - 5;

	//Racket Starting Y Position2D
	RacketLeft.pos.y = gameHeight / 2 - 50;
	RacketRight.pos.y = gameHeight / 2 - 50;

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
		//gl_helper::DrawRect(0, RacketLeft.pos.y, RacketWidth, RacketHeight);
		RacketLeft.DrawMe();
		//Right Racket
		//gl_helper::DrawRect(gameWidth - 10, RightY, RacketWidth, RacketHeight);
		RacketRight.DrawMe();
		//Ball
		Ball.DrawMe();

		//Left Score
		gl_helper::DrawNumber(gameWidth / 2 - 40, 10, LeftScore);
		//Right Score
		gl_helper::DrawNumber(gameWidth / 2 + 10, 10, RightScore);
		//Colon
		gl_helper::DrawRect(gameWidth / 2 - 2, 25, 5, 5);
		gl_helper::DrawRect(gameWidth / 2 - 2, 45, 5, 5);

		glfwSwapBuffers(window);
		glfwSwapInterval(1);
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void Collisions() {

	if (glfwGetTime() - time > 1.0) {

		time = glfwGetTime()*TimeSpeed;

		Ball.pos.x += Ball.velocityX;

		StoredVelocity += Ball.velocityY;

		if (StoredVelocity > 1.0f) {
			Ball.pos.y += 1;
			StoredVelocity -= 1;
		}
		else if (StoredVelocity < -1.0f) {
			Ball.pos.y -= 1;
			StoredVelocity += 1;

		}
	}


	if (Ball.pos.x > gameWidth - RacketRight.width * 2) { //Ball at Right Edge

		if (Between(Ball.pos.y, RacketRight.pos.y + RacketRight.height, RacketRight.pos.y)) {

			Ball.velocityX = -Ball.velocityX;

			if (Between(Ball.pos.y, RacketRight.pos.y, RacketRight.pos.y + RacketRight.height * 0.3)) {

				Ball.velocityY -= 0.3;

			}
			else if (Between(Ball.pos.y, RacketRight.pos.y + RacketRight.height - RacketRight.height * 0.3, RacketRight.pos.y + RacketRight.height)) {

				Ball.velocityY += 0.3;
			}
		}
		else {

			LeftScore++;
			Reset();
		}
	}
	else if (Ball.pos.x < RacketLeft.width) { //Ball at Left Edge

		if (Between(Ball.pos.y, RacketLeft.pos.y + RacketLeft.height, RacketLeft.pos.y)) {

			Ball.velocityX = -Ball.velocityX;

			if (Between(Ball.pos.y, RacketLeft.pos.y, RacketLeft.pos.y + RacketLeft.height * 0.3)) {

				Ball.velocityY -= 0.3;

			}
			else if (Between(Ball.pos.y, RacketLeft.pos.y + RacketLeft.height - RacketLeft.height * 0.3, RacketLeft.pos.y + RacketLeft.height)) {

				Ball.velocityY += 0.3;
			}

		}
		else {

			RightScore++;
			Reset();
		}

		//Ball at Top Edge
	}
	else if (Ball.pos.y < 0) {

		Ball.pos.y = 0;
		Ball.velocityY = -Ball.velocityY;

		//Ball at Buttom Edge
	}
	else if (Ball.pos.y > gameHeight - Ball.radius) {

		Ball.pos.y = gameHeight - Ball.radius;
		Ball.velocityY = -Ball.velocityY;
	}

}


bool Between(int target, int a, int b) {

	const int max = max(a, b);
	const int min = min(a, b);

	if (target < max && target > min)
		return true;

	return false;

}

void Reset() {

	Ball.pos.x = gameWidth / 2 - Ball.radius / 2;
	glfwSetTime(0.0);
	time = 0.0;
	Ball.velocityX = 1;
	Ball.velocityY = 0;
	StoredVelocity = 0;

	if (LeftScore > 9 || RightScore > 9) {

		LeftScore = 0;
		RightScore = 0;
	}
}


