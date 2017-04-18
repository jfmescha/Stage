#include "LIT.h"

LITBox::LITBox(int sw, int sh)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	LITWindow = SDL_CreateWindow("Stage//", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	LITContext = SDL_GL_CreateContext(LITWindow);
	SDL_GL_SetSwapInterval(1);
	InitOpenGL();
}

LITBox::~LITBox()
{

}

void LITBox::InitOpenGL()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.f, 0.f, 0.f, 1.f);
}

void LITBox::UpdateBox()
{
}
