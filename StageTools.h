#pragma once
#include <chrono>
#include <SDL.h>

class StageTools
{
private:

public:

};

class Ticker
{
private:
	bool Running, Paused;
	Uint32 RunningTicks;
	Uint32 PausedTicks;

public:
	Ticker();
	//Ticker Controls
	void Start();
	void Stop();
	void Pause();
	void UnPause();
	Uint32 PushTicks();

	bool PushStatus();
	bool PushPauseStatus();
};
class FPSTicker
{
private:
	Ticker FPSClock;
	Ticker TickTracker;
	int FPS;
	int TicksPS;
	int Frames;
	int FrameCount;

public:
	FPSTicker(int);
	bool TickCheck();
	void UpdateTick();

	int PushFPS();
};

//Legacy
class Tick
{
private:
	std::chrono::steady_clock::time_point TimerStartPoint;
	std::chrono::steady_clock::time_point ProcTime;

	std::chrono::steady_clock::duration TickRate;
	int frames;

public:
	Tick();
	~Tick();

	void StartTick(int);

	bool TickCheck();
	void UpdateTick();

	int PushFPS();

};
//Legacy
