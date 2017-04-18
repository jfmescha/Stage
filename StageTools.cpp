#include "StageTools.h"

Tick::Tick()
{
}

Tick::~Tick()
{
}

void Tick::StartTick(int tickrateset)
{
	TimerStartPoint = std::chrono::steady_clock::now();
	ProcTime = TimerStartPoint;
	TickRate = std::chrono::milliseconds(tickrateset);
	frames = 0;
}

bool Tick::TickCheck()
{
	if (ProcTime + TickRate < std::chrono::steady_clock::now())
	{
		frames = 0;
		return true;
	}
	else
	{
		return false;
	}
}

void Tick::UpdateTick()
{
	ProcTime += TickRate;
	frames++;
}

int Tick::PushFPS()
{
	return frames;
}

Ticker::Ticker()
{
	Running = false;
	Paused = false;
	RunningTicks = 0;
	PausedTicks = 0;
}

void Ticker::Start()
{
	Running = true;
	Paused = false;
	RunningTicks = SDL_GetTicks();
	PausedTicks = 0;
}

void Ticker::Stop()
{
	Running = false;
	Paused = false;
	RunningTicks = 0;
	PausedTicks = 0;
}

void Ticker::Pause()
{
	if (Running && !Paused)
	{
		Paused = true;
		PausedTicks = SDL_GetTicks() - RunningTicks;
		RunningTicks = 0;
	}
}

void Ticker::UnPause()
{
	if (Running && Paused)
	{
		Paused = false;
		RunningTicks = SDL_GetTicks() - PausedTicks;
		PausedTicks = 0;
	}
}

Uint32 Ticker::PushTicks()
{
	if (Running)
	{
		if (Paused)
			return PausedTicks;
		else
			return (SDL_GetTicks() - RunningTicks);
	}
	else
		return 0;
}

bool Ticker::PushStatus()
{
	return Running;
}

bool Ticker::PushPauseStatus()
{
	return Paused;
}

FPSTicker::FPSTicker(int pushfps)
{
	FPS = pushfps;
	if (FPS != 0)
		TicksPS = 1000 / FPS;
	else
		TicksPS = 1000;
	Frames = 0;
	FrameCount = 0;
	FPSClock.Start();
	TickTracker.Start();
}

bool FPSTicker::TickCheck()
{
	if (FPS != 0)
	{
		if (TickTracker.PushTicks() < TicksPS)
			return false;
		else
			return true;
	}
	else
		return true;
}

void FPSTicker::UpdateTick()
{
	TickTracker.Start();
	FrameCount++;
}

int FPSTicker::PushFPS()
{
	return FrameCount / (FPSClock.PushTicks() / 1000.f);
}
