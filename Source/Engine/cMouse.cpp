#include "cMouse.h"

cMouse::cMouse(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int img_x, int img_y,
				int width, int height)
{
	m_Graphics = graphics;
	m_Cursor = bitmap; 
	SetX(x); 
	SetY(y); 
	m_ImageX = img_x; 
	m_ImageY = img_y; 
	m_Width = width; 
	m_Height = height;
}

void cMouse::Draw()
{
	m_Graphics->RenderTexture(m_Cursor, m_ImageX, m_ImageY,
		GetX(), GetY(), m_Width, m_Height);
}