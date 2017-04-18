#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <GL\GLU.h>
#include <string>

class LIT
{
private:
	SDL_Window* SoftWindow;
	SDL_Surface* SoftScreenSurface;
	SDL_Renderer* SoftRenderer;
	TTF_Font *DefaultFont;
	SDL_Surface * TextBox;
	SDL_Texture * TextTexture;

	SDL_Rect Camera;

public:
	//Constructors
	LIT();
	~LIT();
	SDL_Rect fillRect;

	//Software
	void InitSoftware(int, int);
	void RenderSoftware();
	void RenderUpdateSoft();
	void CloseSoftware();
	//Software rendering
	void DrawSoftBox(float, float, float, float, int, int, int);
	void DrawSoftRect(float, float, float, float, int, int, int);
	void DrawSoftText(float, float, int, int, int, std::string);

	SDL_Rect PushCamera();
	void PanCamera(int, int);
	void SetCamera(int, int);

	//Push Renderer
	SDL_Renderer * PushRenderer();

};

class GraphicsObject
{
private:
	int ID;
	SDL_Texture * ObjectTexture;
	//SDL_Texture * Blank;
	SDL_Rect renderQuad;

public:
	GraphicsObject(int);
	~GraphicsObject();
	void LoadGraphicObject(std::string, SDL_Renderer*);
	void DrawGraphicObject(SDL_Renderer*,float, float, float, float, float, float);
	void CleanUp();

	//Streamer
	void CreateBlankTexture(SDL_Renderer*, float, float);

};