#include "cCursor.h"

cCursor::cCursor(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int width, int height)
{
	m_Graphics = graphics;
	m_Bitmap = bitmap;
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

cCursor::cCursor() {}

void cCursor::Draw()
{
	m_Graphics->RenderTexture(m_Bitmap, NULL, NULL, m_X, m_Y, 
								m_Width, m_Height);
}