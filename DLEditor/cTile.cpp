#include "cTile.h"

cTile::cTile(){}
cTile::~cTile(){}

cTile::cTile(cGraphics* graphics, SDL_Texture* bitmap, int x, int y, 
		int img_x, int img_y, int width, int height, bool access,
		bool tempdisplay, int healthholder, int health, int blink,
		std::string id)
{
	m_Graphics = graphics;
	m_Bitmap = bitmap; 
	m_X = x; 
	m_Y = y;
	m_ImageX = img_x; 
	m_ImageY = img_y; 
	m_Width = width; 
    m_Height = height;
	m_Access = access;
	m_Blink = 0;
	m_HealthHolder = 0;
	m_Health = 1;
	m_Trigger = 0;
	m_ID = id;
}

void cTile::Draw()
{	
	if (m_Blink == 1)
	{
		//cout << "I blink" << " ";
		if (m_Health == 0)
		{
			m_Health = m_HealthHolder;	// Restore Health
			m_Trigger = !m_Trigger;
			return;
		}

		m_Health -= 1;

		if (m_Trigger == 0)
		{
			//cout << "Disappear" << "\n";
			return;						// Do not draw in this cycle
		}
		//cout << "I'm here" << "\n";
	}
	// Must note that the original tileset is 16*16
	// But we will double it to 32*32 by forcing
	// displaying m_Width as 32 and m_Height as 32
	m_Graphics->RenderTileSet(m_Bitmap, m_ImageX, m_ImageY, m_X, m_Y, 
								TILE_WIDTH, TILE_HEIGHT, 
								TILE_DISPLAY_WIDTH, TILE_DISPLAY_HEIGHT);
}

void cTile::GameDraw(int xbias, int ybias)
{
	int m_X_new = m_X - xbias;
	int m_Y_new = m_Y - ybias;
	if (m_X == 192 && m_Y == 288)
	{
		
		//std::cout << "Center is: " << m_ID << " " << m_X_new << " " << m_Y_new << "\n";
	}

	m_Graphics->RenderTileSet(m_Bitmap, m_ImageX, m_ImageY, m_X_new, m_Y_new,
		TILE_WIDTH, TILE_HEIGHT,
		TILE_DISPLAY_WIDTH, TILE_DISPLAY_HEIGHT);
}

void cTile::DrawBias(int xbias, int ybias)
{	
	if (m_X >= EDITOR_MOUSE_X_MAX+xbias || 
		m_Y >= EDITOR_MOUSE_Y_MAX+ybias) return;
	if (m_X < xbias || m_Y < ybias) return;	// Do not draw
	int m_X_new, m_Y_new;
	m_X_new = m_X - xbias;
	m_Y_new = m_Y - ybias;
	if (m_Blink == 1)
	{
		//cout << "I blink" << " ";
		if (m_Health == 0)
		{
			m_Health = m_HealthHolder;	// Restore Health
			m_Trigger = !m_Trigger;
			return;
		}

		m_Health -= 1;

		if (m_Trigger == 0)
		{
			//cout << "Disappear" << "\n";
			return;						// Do not draw in this cycle
		}
		//cout << "I'm here" << "\n";
	}
	// Must note that the original tileset is 16*16
	// But we will double it to 32*32 by forcing
	// displaying m_Width as 32 and m_Height as 32
	m_Graphics->RenderTileSet(m_Bitmap, m_ImageX, m_ImageY, 
								m_X_new, m_Y_new, 
								TILE_WIDTH, TILE_HEIGHT, 
								TILE_DISPLAY_WIDTH, TILE_DISPLAY_HEIGHT);
}

SDL_Rect cTile::GetRect()
{
	SDL_Rect r;
	r.x = m_X;  
	r.y = m_Y; 
	r.w = m_Width;
	r.h = m_Height;	
	return r;
}

void cTile::SetSpecial(bool blink, int healthholder, int health,
						bool trigger)
{
	m_Blink = blink;
	m_HealthHolder = healthholder;
	m_Health = health;
	m_Trigger = trigger;
}

bool cTile::IsMe(int x, int y)
{
	if (m_X == x && m_Y == y)
		return true;
	else
		return false;
}

bool cTile::IsBlink()
{
	return m_Blink;
}