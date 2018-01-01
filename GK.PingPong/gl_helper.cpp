#include "stdafx.h"

#include <Windows.h>

#include "gl_helper.h"
//#include "GL/glew.h"
//#include <GL/glu.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>

GLbyte *LoadTGAImage(const char *FileName, int *ImWidth, int *ImHeight, int *ImComponents, unsigned int *ImFormat)
{

	/*************************************************************************************/

	// Struktura dla nag³ówka pliku  TGA


#pragma pack(1)            
	typedef struct
	{
		GLbyte    idlength;
		GLbyte    colormaptype;
		GLbyte    datatypecode;
		unsigned short    colormapstart;
		unsigned short    colormaplength;
		unsigned char     colormapdepth;
		unsigned short    x_orgin;
		unsigned short    y_orgin;
		unsigned short    width;
		unsigned short    height;
		GLbyte    bitsperpixel;
		GLbyte    descriptor;
	}TGAHEADER;
#pragma pack(8)

	FILE *pFile;
	TGAHEADER tgaHeader;
	unsigned long lImageSize;
	short sDepth;
	GLbyte    *pbitsperpixel = NULL;


	/*************************************************************************************/

	// Wartoœci domyœlne zwracane w przypadku b³êdu 

	*ImWidth = 0;
	*ImHeight = 0;
	*ImFormat = GL_BGR_EXT;
	*ImComponents = GL_RGB8;

	//pFile = fopen(FileName, "rb");
	fopen_s(&pFile, FileName, "rb");
	if (pFile == NULL)
		return NULL;

	/*************************************************************************************/
	// Przeczytanie nag³ówka pliku 


	fread(&tgaHeader, sizeof(TGAHEADER), 1, pFile);


	/*************************************************************************************/

	// Odczytanie szerokoœci, wysokoœci i g³êbi obrazu 

	*ImWidth = tgaHeader.width;
	*ImHeight = tgaHeader.height;
	sDepth = tgaHeader.bitsperpixel / 8;


	/*************************************************************************************/
	// Sprawdzenie, czy g³êbia spe³nia za³o¿one warunki (8, 24, lub 32 bity) 

	if (tgaHeader.bitsperpixel != 8 && tgaHeader.bitsperpixel != 24 && tgaHeader.bitsperpixel != 32)
		return NULL;

	/*************************************************************************************/

	// Obliczenie rozmiaru bufora w pamiêci


	lImageSize = tgaHeader.width * tgaHeader.height * sDepth;


	/*************************************************************************************/

	// Alokacja pamiêci dla danych obrazu


	pbitsperpixel = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));

	if (pbitsperpixel == NULL)
		return NULL;

	if (fread(pbitsperpixel, lImageSize, 1, pFile) != 1)
	{
		free(pbitsperpixel);
		return NULL;
	}


	/*************************************************************************************/

	// Ustawienie formatu OpenGL


	switch (sDepth)

	{

	case 3:

		*ImFormat = GL_BGR_EXT;

		*ImComponents = GL_RGB8;

		break;

	case 4:

		*ImFormat = GL_BGRA_EXT;

		*ImComponents = GL_RGBA8;

		break;

	case 1:

		*ImFormat = GL_LUMINANCE;

		*ImComponents = GL_LUMINANCE8;

		break;

	};



	fclose(pFile);



	return pbitsperpixel;

}

/*************************************************************************************/


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

void gl_helper::DrawCircleTexture(const int x, const int y, const float radius, const char* textureFile)
{
	int ImWidth, ImHeight, ImComponents;
	unsigned int ImFormat;

	auto pBytes = LoadTGAImage(textureFile, &ImWidth, &ImHeight, &ImComponents, &ImFormat);
	glTexImage2D(GL_TEXTURE_2D, 0, ImComponents, ImWidth, ImHeight, 0, ImFormat, GL_UNSIGNED_BYTE, pBytes);

	free(pBytes);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	const float twoPi = 2.0f * M_PI;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // origin
	const float delta = twoPi / CIRCLE_SEGMENTS;
	for (unsigned int i = 0; i <= CIRCLE_SEGMENTS; i++)
	{
		auto xx = x + (radius * cos(i *  delta));
		auto yy = y + (radius * sin(i * delta));
		glTexCoord2f(xx, yy);
		glVertex2f(xx, yy);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);

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
