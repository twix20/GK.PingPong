// GK.PingPong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

//#include <GL/glew.h>
#include <GL/glu.h>
#include "CGameController.h"


using namespace std;

CGameController game;

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Left Control UP
	if (key == GLFW_KEY_UP) {
		game.racketRight->pos.y -= game.racketRight->racketSpeed;
	}
	//Left Control Down
	if (key == GLFW_KEY_DOWN) {
		game.racketRight->pos.y += game.racketRight->racketSpeed;
	}
	//Right Control UP
	if (key == GLFW_KEY_W) {
		game.racketLeft->pos.y -= game.racketLeft->racketSpeed;
	}
	//Right Control Down
	if (key == GLFW_KEY_S) {
		game.racketLeft->pos.y += game.racketLeft->racketSpeed;
	}

}

int main()
{
	game.Start(&KeyCallBack);
}

