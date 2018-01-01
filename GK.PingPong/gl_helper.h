#pragma once
//#ifndef GL_HELPER_H
//#define GL_HELPER_H

#define CIRCLE_SEGMENTS 40

class gl_helper
{
public:

	static void SetColor(float r, float g, float b);

	static void DrawRect(int x, int y, int width, int height);
	static void DrawCircle(int x, int y, float radius);
	static void DrawCircleTexture(const int x, const int y, const float radius, const char * textureFile);
	static void DrawNumber(int x, int y, int n);
	static void DebugPoint(float x, float y);

};

//#endif // GL_HELPER_H
