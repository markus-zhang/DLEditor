#include "cSDL2Rect.h"

cSDL2Rect::cSDL2Rect()	{
	m_Life = -1;	// Permanent display until removed from manager
}

cSDL2Rect::~cSDL2Rect() {}

void cSDL2Rect::Init(int x, int y, int width, int height,
	int r, int g, int b, Uint8 alpha, int life) {
	m_Rect.x = x;
	m_Rect.y = y;
	m_Rect.w = width;
	m_Rect.h = height;

	m_Color.r = r;
	m_Color.g = g;
	m_Color.b = b;

	m_Alpha = alpha;
	m_Life = life;
	m_Timer.Reset();
}

void cSDL2Rect::Update() {
	m_Life -= m_Timer.GetMilliseconds();
	//Debug
	
}

void cSDL2Rect::Suicide() {
	m_Life = 0;
}

void cSDL2Rect::Render(cGraphics* graphics) {
	if (m_Life >= -1) {
		graphics->RenderRect(m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h,
			m_Color.r, m_Color.g, m_Color.b, m_Alpha);
	}
}