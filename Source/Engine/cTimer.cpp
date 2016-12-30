#include "cTimer.h"

cTimer::cTimer()
{
	// Tell SDL to intialize its timer component //
	SDL_Init(SDL_INIT_TIMER);

	Reset();	
}

cTimer::~cTimer() {}

// Return the number of milliseconds that have passed since ResetTicks() was last called //
Uint32 cTimer::GetMilliseconds()
{
	// Take the current time and subtract the time that ResetTicks() was last called //
	return SDL_GetTicks() - m_Ticks;
}

// Return the number of seconds that have passed since ResetTicks() was last called //
Uint32 cTimer::GetSeconds()
{
	return GetMilliseconds() / 1000;
}

// Reset the timer //
void cTimer::Reset()
{
	m_Ticks = SDL_GetTicks();
}

// Aaron Cox, 2005 
