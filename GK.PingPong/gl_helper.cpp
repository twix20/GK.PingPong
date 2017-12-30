#include "stdafx.h"

#include <Windows.h>

#include "gl_helper.h"
//#include "GL/glew.h"
#include <GL/glu.h>

#define _USE_MATH_DEFINES
#include <cmath>


void gl_helper::DebugPoint(float x, float y) {

	float SavedColor[4];
	glGetFloatv(GL_CURRENT_COLOR, SavedColor);


	glColor4f(1.0f, 0, 0, 1.0f);

	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

	glColor4f(SavedColor[0], SavedColor[1], SavedColor[2], SavedColor[3]);

}


void gl_helper::SetColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}

void gl_helper::DrawRect(const int x, const int y, const int width, const int height)
{
	glBegin(GL_QUADS);

	//Buttom Left
	glVertex2f(x, y);
	//Buttom Right
	glVertex2f(x + width, y);
	//Top Right
	glVertex2f(x + width, y + height);

	glVertex2f(x, y + height);

	glEnd();
}

void gl_helper::DrawCircle(const int x, const int y, const float radius)
{
	const float twoPi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // origin
	const float delta = twoPi / CIRCLE_SEGMENTS;
	for (unsigned int i = 0; i <= CIRCLE_SEGMENTS; i++)
	{
		glVertex2f(x + (radius * cos(i *  delta)), y + (radius * sin(i * delta)));
	}
	glEnd();
}


void gl_helper::DrawNumber(int x, int y, int n)
{

	/*
	//Top
	DrawRect(x + 5 , y , 20 , 5  );
	//Top Left
	DrawRect(x , y + 5 , 5 , 20  );
	//Top Right
	DrawRect(x + 25 , y + 5 , 5 , 20 );
	//Center
	DrawRect(x + 5 , y + 25 , 20 , 5  );
	//Buttom Left
	DrawRect(x , y + 30 , 5 , 20  );
	//Buttom Right
	DrawRect(x + 25 , y + 30 , 5 , 20 );
	//Buttom
	DrawRect(x + 5 , y + 50 , 20 , 5  );
	*/


	switch (n) {

	case 0:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;

	case 1:
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		break;
	case 2:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 3:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 4:
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		break;
	case 5:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 6:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 7:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		break;
	case 8:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x, y + 30, 5, 20);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;
	case 9:
		DrawRect(x + 5, y, 20, 5);
		DrawRect(x, y + 5, 5, 20);
		DrawRect(x + 25, y + 5, 5, 20);
		DrawRect(x + 5, y + 25, 20, 5);
		DrawRect(x + 25, y + 30, 5, 20);
		DrawRect(x + 5, y + 50, 20, 5);
		break;

	}



}
