#ifndef CGAMELEVEL_
#define CGAMELEVEL_

#include "cTile.h"
#include "cEntity.h"
#include "cCamera.h"

class cGameLevel
{
public:
	/*cGameLevel();
	~cGameLevel();*/

	std::vector<cTile>& GetMap() { return m_Map; }
	std::vector<cEntity>& GetEntity() { return m_Entity; }

	int GetTileAccess(int x, int y);
	int GetX() { return m_PlayerX; }
	int GetY() { return m_PlayerY;  }

	void SetX(int xmod) { m_PlayerX += xmod; }
	void SetY(int ymod) { m_PlayerY += ymod; }
	void SetID(std::string id) { m_ID = id; }
	//void OnEnter(int x, int y);
	//void OnExit();

	void SetTexture(SDL_Texture* texture)
	{
		m_TileTexture = texture;
	}
	/*void SetPlayer(cEntityTest player)
	{
		m_Player = player;
	}*/
	void Draw();

	void RemoveTile(int x, int y, int xbias, int ybias);
	void RemoveEntity(int x, int y, int xbias, int ybias);

	void PushTile();
	void SetPlayerStart(int x, int y)
	{
		m_PlayerX = x;
		m_PlayerY = y;
	}

	//Camera Related
	int GetMapNorthBorder();
	int GetMapSouthBorder();
	int GetMapWestBorder();
	int GetMapEastBorder();
	void InitialCamera();
	void UpdateCamera();

	//GameState
	int GetXBias() { return m_XBias; }
	int GetYBias() { return m_YBias; }

	//Main Update
	void Update();

private:
	SDL_Texture* m_TileTexture;
	SDL_Texture* m_PlayerSprite;
	
	std::string m_ID;
	std::vector<cEntity> m_Entity;
	std::vector<cTile>   m_Map;
	std::vector < std::vector<cTile> > m_MapStack;		// For Undo
	std::vector < std::vector<cEntity> > m_EntityStack;	// For Undo
	int m_XBias, m_YBias;
	cCamera m_Camera;
	int m_PlayerX, m_PlayerY;
};

#endif