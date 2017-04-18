#include "LITSoft.h"
#include <iostream>

LIT::LIT()
{
}

LIT::~LIT()
{
}

void LIT::InitSoftware(int sw, int sh)
{
	//Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	SoftWindow = SDL_CreateWindow("Stage// Project Dungeons", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sw, sh, SDL_WINDOW_SHOWN);
	SoftScreenSurface = SDL_GetWindowSurface(SoftWindow);
	SoftRenderer = SDL_CreateRenderer(SoftWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	DefaultFont = TTF_OpenFont("Font/arial.ttf", 11);
	if(DefaultFont == NULL)
		std::cout << "Font fail" << std::endl;

	Camera.x = 0;
	Camera.y = 0;
	Camera.w = sw;
	Camera.h = sh;
}

void LIT::RenderSoftware()
{
	SDL_SetRenderTarget(SoftRenderer, NULL);
	SDL_RenderPresent(SoftRenderer);
}

void LIT::RenderUpdateSoft()
{
	//SDL_UpdateWindowSurface(SoftWindow);
	SDL_RenderClear(SoftRenderer);
	SDL_SetRenderDrawColor(SoftRenderer, 0, 0, 0, 0);
}

void LIT::CloseSoftware()
{
	SDL_DestroyWindow(SoftWindow);
	SoftWindow = NULL;

	SDL_Quit();
}

void LIT::DrawSoftBox(float xpos, float ypos, float width, float height, int r, int g, int b)
{
	fillRect.x = xpos;
	fillRect.y = ypos;
	fillRect.w = width;
	fillRect.h = height;
	// = { xpos, ypos, width, height };
	SDL_SetRenderDrawColor(SoftRenderer,r,g,b,255);
	SDL_RenderFillRect(SoftRenderer, &fillRect);
}

void LIT::DrawSoftRect(float xpos, float ypos, float width, float height, int r, int g, int b)
{
	SDL_Rect fillRect = { xpos, ypos, width, height };
	SDL_SetRenderDrawColor(SoftRenderer, r, g, b, 255);
	SDL_RenderDrawRect(SoftRenderer, &fillRect);
}

void LIT::DrawSoftText(float x, float y, int r, int g, int b, std::string text)
{
	//SDL_SetRenderDrawColor(SoftRenderer, r, g, b, 255);
	SDL_Color tcolor = { r,g,b };
	TextBox = TTF_RenderText_Solid(DefaultFont, text.c_str(), tcolor);
	SDL_Rect renderQuad = { x, y, TextBox->w, TextBox->h };
	TextTexture = SDL_CreateTextureFromSurface(SoftRenderer, TextBox);
	SDL_RenderCopyEx(SoftRenderer, TextTexture, NULL,&renderQuad,NULL,NULL, SDL_FLIP_NONE);
	SDL_DestroyTexture(TextTexture);
	TextTexture = NULL;
	SDL_FreeSurface(TextBox);
}

SDL_Rect LIT::PushCamera()
{
	return Camera;
}

void LIT::PanCamera(int xc, int yc)
{
	Camera.x += xc;
	Camera.y += yc;
}

void LIT::SetCamera(int xc, int yc)
{
	Camera.x = xc;
	Camera.y = yc;
}

SDL_Renderer * LIT::PushRenderer()
{
	return SoftRenderer;
}

GraphicsObject::GraphicsObject(int idef)
{
	ID = idef;
}

GraphicsObject::~GraphicsObject()
{
	SDL_DestroyTexture(ObjectTexture);
}

void GraphicsObject::LoadGraphicObject(std::string filename, SDL_Renderer* renderer)
{
	SDL_Surface * TextureLoader = IMG_Load(filename.c_str());
	ObjectTexture = SDL_CreateTextureFromSurface(renderer, TextureLoader);
	SDL_FreeSurface(TextureLoader);
}

void GraphicsObject::DrawGraphicObject(SDL_Renderer* renderer, float x, float y, float z, float w, float h, float l)
{
	renderQuad.x = x;
	renderQuad.y = y;
	renderQuad.w= w;
	renderQuad.h = h;
	SDL_RenderCopyEx(renderer, ObjectTexture, NULL, &renderQuad, NULL, NULL, SDL_FLIP_NONE);
}

void GraphicsObject::CleanUp()
{
	SDL_DestroyTexture(ObjectTexture);
	ObjectTexture = NULL;
}

void GraphicsObject::CreateBlankTexture(SDL_Renderer* renderer, float width, float height)
{
	//Blank = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}
