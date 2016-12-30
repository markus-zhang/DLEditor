#include "cEntity.h"

cEntity::cEntity(cGraphics* graphics, SDL_Texture* bitmap, int x, 
	int y, int img_x, int img_y, int width, int height, 
	std::string id, int hp, int gold, int exp, bool interactive,
	int direction, int frame) :
	m_Graphics(graphics),
	m_Bitmap(bitmap), 
	m_X(x), 
	m_Y(y), 
	m_ImageX(img_x), 
	m_ImageY(img_y), 
	m_Width(width), 
	m_Height(height),
	m_ID (id),
	m_HP (hp),
	m_Gold (gold),
	m_Exp (exp),
	m_Int (interactive),
	m_Direct (direction),
	m_Frame (frame),
	m_CurrentFrame (0),
	m_AnimationRate (ENTITY_ANIMATE_RATE),
	m_AnimationTimer (cTimer())
{
}

void cEntity::SetCurrentFrame()
{
	if ( m_AnimationTimer.GetMilliseconds() >= m_AnimationRate )
	{
		if (m_CurrentFrame == m_Frame - 1) 
			m_CurrentFrame = 0;	 // Go back to the first frame
		else 
			m_CurrentFrame += 1;
		m_AnimationTimer.Reset();
	}
	//cout << "Current frame is: " << m_CurrentFrame << "\n";
}

void cEntity::Draw()
{
	int imageX;		// True clip coordinates, Note that m_ImageY does not change
	imageX = m_ImageX + 32 * m_CurrentFrame;
	m_Graphics->RenderTexture(m_Bitmap, imageX, m_ImageY, m_X, m_Y, 
		m_Width, m_Height);
}

void cEntity::DrawBias(int xbias, int ybias)
{
	if (m_X < xbias || m_Y < ybias) return;	// Do not draw
	int m_X_new, m_Y_new;
	m_X_new = m_X - xbias;
	m_Y_new = m_Y - ybias;
	int imageX;		// True clip coordinates, Note that m_ImageY does not change
	imageX = m_ImageX + 32 * m_CurrentFrame;
	m_Graphics->RenderTexture(m_Bitmap, imageX, m_ImageY, 
		m_X_new, m_Y_new, 
		m_Width, m_Height);
}

SDL_Rect cEntity::GetRect()
{
	SDL_Rect r;
	r.x = (int)m_X;  // float to int
	r.y = (int)m_Y;  // float to int
	r.w = m_Width;
	r.h = m_Height;	
	return r;
}

// Aaron Cox, 2005
// Markus Zhang, 2016