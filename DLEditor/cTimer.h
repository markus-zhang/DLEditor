#pragma once

#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_TTF.lib")

#include "SDL.h" 

class cTimer
{
public:
	cTimer();
	~cTimer();

	// Return the number of milliseconds that have passed since Reset() was last called 
	Uint32 GetMilliseconds();

	// Return the number of seconds that have passed since Reset() was last called 
	Uint32 GetSeconds();

	// Reset the timer 
	void Reset();

private:
	// This variable stores the time the Reset() was 
	// last called at. See GetMilliseconds() for its use. 
	Uint32 m_Ticks;
};
