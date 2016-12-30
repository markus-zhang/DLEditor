#include "cGameLevel.h"
#include "math.h"

//cGameLevel::cGameLevel()
//{
//	m_ID = "TESTTILE";
//	UpdateCamera();
//}
//
//cGameLevel::~cGameLevel()
//{
//	m_TileTexture = NULL;
//	m_PlayerSprite = NULL;
//}

void cGameLevel::Update()
{
	UpdateCamera();
	m_XBias = m_Camera.GetX() - GAME_MAP_WIDTH / 2;
	m_YBias = m_Camera.GetY() - GAME_MAP_HEIGHT / 2;

	//std::cout << m_Camera.GetX() << " " << m_Camera.GetY() << "\n";
}
void cGameLevel::Draw()
{
	//New Draw function:
	//Centers on the camera
	//The Center is draw at (128, 128)
	//Then you have your baises
	//std::cout << m_PlayerX << " " << m_PlayerY << "\n";
	//std::cout << m_Camera.GetX() << " " << m_Camera.GetY() << "\n";
	
	//std::cout << m_XBias << " " << m_YBias << "\n";
	for (size_t i = 0; i<m_Map.size(); i++)
	{
		m_Map[i].GameDraw(m_XBias, m_YBias);
	}
}

//Camera Related
int cGameLevel::GetMapNorthBorder()
{
	if (m_Map.size() <= 0)
	{
		return 0;
	}
	
	int temp = 1000;	//Random large number
	std::vector<cTile>::iterator it;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		if ((*it).GetY() <= temp)	temp = (*it).GetY();
	}
	return temp;
}

int cGameLevel::GetMapSouthBorder()
{
	if (m_Map.size() <= 0)
	{
		return 0;
	}

	int temp = 0;	//Random small number
	std::vector<cTile>::iterator it;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		if ((*it).GetY() >= temp)	temp = (*it).GetY();
	}
	//std::cout << "South Border is " << temp << "\n";
	return temp;
}

int cGameLevel::GetMapWestBorder()
{
	if (m_Map.size() <= 0)
	{
		return 0;
	}

	int temp = 1000;	//Random large number
	std::vector<cTile>::iterator it;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		if ((*it).GetX() <= temp)	temp = (*it).GetX();
	}
	return temp;
}

int cGameLevel::GetMapEastBorder()
{
	if (m_Map.size() <= 0)
	{
		return 0;
	}

	int temp = 0;	//Random small number
	std::vector<cTile>::iterator it;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		if ((*it).GetX() >= temp)	temp = (*it).GetX();
	}
	return temp;
}

void cGameLevel::UpdateCamera()
{
	//if (m_PlayerX >= GAME_MAP_WIDTH / 2)
	//{
	//	if (m_PlayerY >= GAME_MAP_HEIGHT / 2)
	//	{
	//		// Regular Camera
	//		m_Camera.Update(m_PlayerX, m_PlayerY);
	//	}
	//	else
	//	{
	//		// We can center on X, but not on Y
	//		// Then Camera.Y should be the middle number of
	//		// GAME_MAP_HEIGHT / 2, say 128
	//		// The maximum Y of the whole map, say 1600, minus
	//		// GAME_MAP_HEIGHT / 2, i.e. 1472
	//		// and m_PlayerY, 
	//		// If m_PlayerY is too small, use 128
	//		// If it's too large, use 1472,
	//		// otherwise use m_PlayerY
	//	}
	//}
	//else
	//{
	//	if (m_PlayerY >= GAME_MAP_HEIGHT / 2)
	//	{
	//		// We can center on Y, but not X
	//	}
	//	else
	//	{
	//		// We can center on neither of x or y
	//	}
	//}
	m_Camera.Update(
		MiddleNumber(m_PlayerX, /*GAME_MAP_WIDTH / 2*/256, GetMapEastBorder() - GAME_MAP_WIDTH / 2 + 32),
		MiddleNumber(m_PlayerY, /*GAME_MAP_HEIGHT / 2*/256, GetMapSouthBorder() - GAME_MAP_HEIGHT / 2 + 32));
}