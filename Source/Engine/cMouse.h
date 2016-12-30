#ifndef CMOUSE_
#define CMOUSE_

#include "cGraphics.h"

class cMouse
{
public:
	cMouse(cGraphics* graphics, SDL_Texture* bitmap,
			int x, int y, int img_x, int img_y,
			int width, int height);
	cMouse() {}

	// Rendering method
	void Draw();

	// Accessors/Mutators
	int GetX() { return m_Position.x; }
	int GetY() { return m_Position.y; }
	int GetWidth()  { return m_Width; }
	int GetHeight() { return m_Height; }
	void SetX(int x) { m_Position.x = x; }
	void SetY(int y) { m_Position.y = y; }

private:
	// Top left position
	SDL_Point m_Position;

	// For drawing
	cGraphics* m_Graphics;
	SDL_Texture* m_Cursor;
	int m_ImageX;
	int m_ImageY;

	// Dimensions of cursor texture
	int m_Width;
	int m_Height;
};
#endif