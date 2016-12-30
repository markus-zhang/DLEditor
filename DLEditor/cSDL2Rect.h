/*
	Create a rectangle on screen to emulate the effect
	of fade in and fade out, using Transparency
*/
#ifndef CSDL2RECT_H_
#define CSDL2RECT_H_

#include "../Source/Engine/cGraphics.h"
#include "../Source/Engine/cTimer.h"

struct cSDL2Color {
	int r, g, b;
};

class cSDL2Rect {
public:
	cSDL2Rect();
	~cSDL2Rect();
	void Init(int x, int y, int width, int height,
		int r, int g, int b, Uint8 alpha, int life);
	void Update();	
	void Suicide();
	void Render(cGraphics* graphics);
private:
	SDL_Rect m_Rect;	// Dimension of the rect
	cSDL2Color m_Color;	// Color of the rect
	Uint8 m_Alpha;		// Alpha of the rect
	int m_Life;			// # of miliseconds
	cTimer m_Timer;		// Timer
};

#endif // !CSDL2RECT_H_
