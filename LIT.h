#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>
#include <stdio.h>
#include <string>

//Main Hardware OpenGL RenderEngine
class LITBox
{
private:
	SDL_Window * LITWindow;
	SDL_GLContext LITContext;

public:
	LITBox(int, int);
	~LITBox();

	void InitOpenGL();
	void UpdateBox();

};


//Graphics Object that uses LIT haredware OpenGL RenderEngine
class GO
{
private:

public:

};