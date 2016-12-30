#ifndef CLEVEL_
#define CLEVEL_

#include "cTile.h"
#include "cEntity.h"

class cLevel
{
public:
	cLevel();
	~cLevel();

	std::vector<cTile>& GetMap(){ return m_Map; }
	std::vector<cEntity>& GetEntity() { return m_Entity; }
	std::vector< std::vector<cTile> >& GetMapStack() { return m_MapStack; }
	std::vector< std::vector<cEntity> >& GetEntityStack() { return m_EntityStack; }

	int GetTileAccess(int x, int y);
	int GetX() { return m_PlayerX; }
	int GetY() { return m_PlayerY; }
	void SetID(std::string id)	{ m_ID = id; }
	void SetPlayerStart(int x, int y)
	{
		m_PlayerX = x;
		m_PlayerY = y;
	}
	void OnEnter();
	void OnExit();

	void RemoveTile(int x, int y, int xbias, int ybias);
	void RemoveEntity(int x, int y, int xbias, int ybias);
	void SaveMapState();
	void SaveEntityState();
	void Undo();

	void PushTile();
private:
	std::string m_ID;
	std::vector<cEntity> m_Entity;
	std::vector<cTile>   m_Map;
	std::vector < std::vector<cTile> > m_MapStack;		// For Undo
	std::vector < std::vector<cEntity> > m_EntityStack;	// For Undo
	int m_PlayerX, m_PlayerY;
};

#endif