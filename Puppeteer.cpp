#include "Puppeteer.h"
#include <iostream>

BindElement::BindElement()
{
	isActive = false;
	BindID = 0;
}

BindElement::~BindElement()
{
	isActive = false;
	BindID = 0;
}

bool BindElement::Active()
{
	return isActive;
}

void BindElement::SwitchActive()
{
	if (isActive)
		isActive = false;
	else
		isActive = true;
}

int BindElement::PullBindID()
{
	return BindID;
}

void BindElement::SetBindID(int tID)
{
	BindID = tID;
}

void BindElement::SetName(std::string tname)
{
	BindName = tname;
}

std::string BindElement::PullName()
{
	return BindName;
}

int BindElement::PullElementID()
{
	return ElementID;
}

void BindElement::SetElementID(int teID)
{
	ElementID = teID;
}

Puppeteer::Puppeteer()
{
	BindListSize = 1;
	ElementList = 0;
	Quiter = false;
	BindElement Temp;
	Temp.SetBindID(0);
	Temp.SetElementID(0);
	BindList.resize(1);
	BindList[0] = Temp;
	LeftMouse = false;
	RightMouse = false;
}

Puppeteer::~Puppeteer()
{
	BindList.clear();
}

void Puppeteer::Perform()
{
	while (SDL_PollEvent(&EventHandler) != 0)
	{
		switch (EventHandler.type)
		{
			case SDL_QUIT: Quiter = true;
			break;
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&MouseX, &MouseY);
			break;
			case SDL_MOUSEBUTTONDOWN:
				switch (EventHandler.button.button)
				{
				case SDL_BUTTON_LEFT:
					LeftMouse = true;
				break;
				case SDL_BUTTON_RIGHT:
					RightMouse = true;
				break;
				}
			break;
			case SDL_MOUSEBUTTONUP:
				LeftMouse = false;
				KeyChecker[0] = false;
				RightMouse = false;
				KeyChecker[2] = false;
			break;

		}
		if (EventHandler.type == SDL_KEYDOWN)
		{
			switch (EventHandler.key.keysym.sym)
			{
			case SDLK_LEFT:
				KeyStater[37] = true;
				break;
			case SDLK_UP:
				KeyStater[38] = true;
				break;
			case SDLK_RIGHT:
				KeyStater[39] = true;
				break;
			case SDLK_DOWN:
				KeyStater[40] = true;
				break;
			case SDLK_0:
				KeyStater[48] = true;
				break;
			case SDLK_1:
				KeyStater[49] = true;
				break;
			case SDLK_2:
				KeyStater[50] = true;
				break;
			case SDLK_3:
				KeyStater[51] = true;
				break;
			case SDLK_4:
				KeyStater[52] = true;
				break;
			case SDLK_5:
				KeyStater[53] = true;
				break;
			case SDLK_6:
				KeyStater[54] = true;
				break;
			case SDLK_7:
				KeyStater[55] = true;
				break;
			case SDLK_8:
				KeyStater[56] = true;
				break;
			case SDLK_9:
				KeyStater[57] = true;
				break;
			case SDLK_SPACE:
				KeyStater[32] = true;
				break;
			case SDLK_r:
				KeyStater[82] = true;
				break;
			case SDLK_w:
				KeyStater[87] = true;
				break;
			case SDLK_a:
				KeyStater[65] = true;
				break;
			case SDLK_s:
				KeyStater[83] = true;
				break;
			case SDLK_d:
				KeyStater[68] = true;
				break;
			}
		}
		if (EventHandler.type == SDL_KEYUP)
		{
			switch (EventHandler.key.keysym.sym)
			{
			case SDLK_LEFT:
				KeyStater[37] = false;
				KeyChecker[37] = false;
				break;
			case SDLK_UP:
				KeyStater[38] = false;
				KeyChecker[38] = false;
				break;
			case SDLK_RIGHT:
				KeyStater[39] = false;
				KeyChecker[39] = false;
				break;
			case SDLK_DOWN:
				KeyStater[40] = false;
				KeyChecker[40] = false;
				break;
			case SDLK_0:
				KeyStater[48] = false;
				KeyChecker[48] = false;
				break;
			case SDLK_1:
				KeyStater[49] = false;
				KeyChecker[49] = false;
				break;
			case SDLK_2:
				KeyStater[50] = false;
				KeyChecker[50] = false;
				break;
			case SDLK_3:
				KeyStater[51] = false;
				KeyChecker[51] = false;
				break;
			case SDLK_4:
				KeyStater[52] = false;
				KeyChecker[52] = false;
				break;
			case SDLK_5:
				KeyStater[53] = false;
				KeyChecker[53] = false;
				break;
			case SDLK_6:
				KeyStater[54] = false;
				KeyChecker[54] = false;
				break;
			case SDLK_7:
				KeyStater[55] = false;
				KeyChecker[55] = false;
				break;
			case SDLK_8:
				KeyStater[56] = false;
				KeyChecker[56] = false;
				break;
			case SDLK_9:
				KeyStater[57] = false;
				KeyChecker[57] = false;
				break;
			case SDLK_SPACE:
				KeyStater[32] = false;
				KeyChecker[32] = false;
				break;
			case SDLK_r:
				KeyStater[82] = false;
				KeyChecker[82] = false;
				break;
			case SDLK_w:
				KeyStater[87] = false;
				KeyChecker[87] = false;
				break;
			case SDLK_a:
				KeyStater[65] = false;
				KeyChecker[65] = false;
				break;
			case SDLK_s:
				KeyStater[83] = false;
				KeyChecker[83] = false;
				break;
			case SDLK_d:
				KeyStater[68] = false;
				KeyChecker[68] = false;
				break;
			}
		}
	}
	for (int i = 0; i < 104; i++)
	{
		if (KeyStater[i])
		{
			for (int e = 0; e < BindList.size(); e++)
			{
				if (BindList[e].PullElementID() == i)
				{
					if (!BindList[e].Active())
						BindList[e].SwitchActive();

				}
			}
		}
		else
		{
			for (int e = 0; e < BindList.size(); e++)
			{
				if (BindList[e].PullElementID() == i)
				{
					if (BindList[e].Active())
						BindList[e].SwitchActive();
				}
			}
		}
	}
}

void Puppeteer::SetBind(int tID, int eID)
{
	BindListSize++;
	ElementList++;
	BindList.resize(BindListSize);
	BindElement TempEl;
	TempEl.SetBindID(tID);
	TempEl.SetElementID(eID);
	BindList[BindListSize-1] = TempEl;
}

void Puppeteer::SetBind(int tID, int eID, std::string tn)
{
	BindListSize++;
	ElementList++;
	BindList.resize(BindListSize);
	BindElement TempEl;
	TempEl.SetBindID(tID);
	TempEl.SetElementID(eID);
	TempEl.SetName(tn);
	BindList[BindListSize - 1] = TempEl;
}

void Puppeteer::DeBind(int tID, int eID)
{
	BindList[BindElementLocator(tID)].SetElementID(eID);
}

void Puppeteer::CheckPull(int tID)
{
	BindList[BindElementLocator(tID)].SwitchActive();
}

bool Puppeteer::CheckBind(int tID)
{
	if (BindList[BindElementLocator(tID)].Active())
		return true;
	else
		return false;
}

bool Puppeteer::CheckBind(std::string tn)
{
	if (BindList[BindElementLocator(tn)].Active())
		return true;
	else
		return false;
}

bool Puppeteer::KeyCheck(int tID)
{
	return KeyChecker[BindList[BindElementLocator(tID)].PullElementID()];
}

bool Puppeteer::KeyCheck(std::string tn)
{
	return KeyChecker[BindList[BindElementLocator(tn)].PullElementID()];
}

void Puppeteer::KeyCheckSwap(int tID)
{
	KeyChecker[BindList[BindElementLocator(tID)].PullElementID()] = true;
}

void Puppeteer::KeyCheckSwap(std::string tn)
{
	KeyChecker[BindList[BindElementLocator(tn)].PullElementID()] = true;
}

int Puppeteer::BindElementLocator(int id)
{
	for (int i = 0; i < BindList.size(); i++)
	{
		if (BindList[i].PullBindID() == id)
			return i;
	}
	return 0;
}

int Puppeteer::BindElementLocator(std::string tn)
{
	for (int i = 0; i < BindList.size(); i++)
	{
		if (BindList[i].PullName() == tn)
			return i;
	}
	return 0;
}

int Puppeteer::GetMouseX()
{
	return MouseX;
}

int Puppeteer::GetMouseY()
{
	return MouseY;
}

bool Puppeteer::GetMouseButtonDown(int sel)
{
	if (sel == 0)
	{
		if (LeftMouse || RightMouse)
			return true;
	}
	else if (sel == -1)
		return LeftMouse;
	else if (sel == 1)
		return RightMouse;
	else
		return false;

	return false;
}

bool Puppeteer::Quit()
{
	return Quiter;
}
