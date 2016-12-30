#include "cStaticButton.h"
#include <iostream>

cStaticButton::cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
					int x, int y, int img_x, int img_y, 
					int width, int height)	{
	m_Graphics = graphics;
	m_Bitmap = bitmap;

	m_ID = "Blah";

	m_X = x;
	m_Y = y;

	m_ImageX = img_x;
	m_ImageY = img_y;

	m_Width = width;
	m_Height = height;
}

cStaticButton::cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int img_x, int img_y, int width, int height,
				std::string id)	{
	m_Graphics = graphics;
	m_Bitmap = bitmap;

	m_ID = id;

	m_X = x;
	m_Y = y;

	m_ImageX = img_x;
	m_ImageY = img_y;

	m_Width = width;
	m_Height = height;
}

void cStaticButton::Draw()	{
	m_Graphics->RenderTexture(m_Bitmap, m_ImageX, 
						m_ImageY, m_X, m_Y, m_Width, m_Height);
}

void cStaticButton::DrawBias(int xbias)	{
	m_Graphics->RenderTexture(m_Bitmap, m_ImageX, 
						m_ImageY, m_X-xbias, m_Y, m_Width, m_Height);
}

void cStaticButton::DrawModulate(Uint8 red, Uint8 green, Uint8 blue,
									int xbias)	{
	int m_X_new;
	m_X_new = m_X - xbias;
	m_Graphics->RenderTextureModulate(m_Bitmap, m_ImageX, 
						m_ImageY, m_X_new, m_Y, m_Width, m_Height,
						red, green, blue);
}

bool cStaticButton::OnClick(int x, int y)	{
	if (x < m_X + 32 && x > m_X && y < m_Y + 32 && y > m_Y)
		return true;
	return false;
}