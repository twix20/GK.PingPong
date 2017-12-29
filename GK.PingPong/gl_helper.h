#pragma once
//#ifndef GL_HELPER_H
//#define GL_HELPER_H

#define CIRCLE_SEGMENTS 40

class gl_helper
{
public:

	static void DrawRect(int x, int y, int width, int height);
	static void DrawCircle(int x, int y, float radius);
	static void DrawNumber(int x, int y, int n);
	static void DebugPoint(float x, float y);

};

//#endif // GL_HELPER_H
