#pragma once
#include <vector>
#include <SDL.h>

class BindElement
{
private:
	//Active
	bool isActive;
	int BindID;
	int ElementID;
	//Name Op
	std::string BindName;

public:
	//C/D
	BindElement();
	~BindElement();

	//Activate switch/ Pull
	bool Active();
	void SwitchActive();
	//Bind ID pull, change
	int PullBindID();
	void SetBindID(int);
	void SetName(std::string);
	std::string PullName();
	//Element ID pull, change
	int PullElementID();
	void SetElementID(int);

};

class Puppeteer
{
private:
	//Bind List
	std::vector<BindElement> BindList;
	bool KeyStater[104] = { false };
	bool KeyChecker[104] = { false };
	int BindListSize;
	int ElementList;
	//SDL event
	SDL_Event EventHandler;
	bool Quiter;

	int MouseX;
	int MouseY;
	bool LeftMouse, RightMouse;

public:
	//Constuct/Deconstruct
	Puppeteer();
	~Puppeteer();

	//Event Handler
	void Perform();

	//Activate/DeActivate
	void SetBind(int, int);
	void SetBind(int, int, std::string);
	void DeBind(int, int);
	//Check Pull
	void CheckPull(int);
	bool CheckBind(int);
	bool CheckBind(std::string);
	// 0 Left Mouse | 1 Right Mouse
	bool KeyCheck(int);
	bool KeyCheck(std::string);
	void KeyCheckSwap(int);
	void KeyCheckSwap(std::string);
	//BindElement Locator
	int BindElementLocator(int);
	int BindElementLocator(std::string);
	//Mouse
	int GetMouseX();
	int GetMouseY();
	// -1 Left | 1 Right
	bool GetMouseButtonDown(int);

	//Quit pusher
	bool Quit();

};