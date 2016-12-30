#include "cLevel.h"

cLevel::cLevel() {}
cLevel::~cLevel() {}

int cLevel::GetTileAccess(int x, int y)
{
	//Locate Tile By Location
	std::vector<cTile>::iterator it;
	for (it=m_Map.begin(); it!=m_Map.end(); it++)
	{
		if ((*it).GetX()==x && (*it).GetY()==y)
			return (*it).GetAccess();
	}
	return 0;
}

void cLevel::OnEnter()
{
	DebugMessage("You have entered " + m_ID);
}

void cLevel::OnExit()
{
	DebugMessage("You have left " + m_ID);
}

void cLevel::RemoveTile(int x, int y, int xbias, int ybias)
{
	std::vector<cTile>::iterator it;
	if (m_Map.size() == 0)
	{
		std::cout << "No Map!" << "\n";
		return;
	}

	for (it = m_Map.begin(); it != m_Map.end(); it ++)
	{
		if ((*it).GetX() == x + xbias && 
			(*it).GetY() == y + ybias)	{
			DebugMessage("Found it!");
			m_Map.erase(it);
			return;
		}
	}
	DebugMessage("No tile at selection!");
}

void cLevel::RemoveEntity(int x, int y, int xbias, int ybias)
{
	std::vector<cEntity>::iterator it;
	if (m_Entity.size() == 0)
	{
		std::cout << "No Entity!" << "\n";
		return;
	}

	for (it = m_Entity.begin(); it != m_Entity.end(); it ++)
	{
		if ((*it).GetX() == x + xbias && 
			(*it).GetY() == y + ybias)
		{
			m_Entity.erase(it);
			break;
		}
	}
}

void cLevel::SaveMapState()
{
	if (m_Map.size() > 0)
		m_MapStack.push_back(m_Map);
}

void cLevel::SaveEntityState()
{
	if (m_Entity.size() > 0)
		m_EntityStack.push_back(m_Entity);
}

void cLevel::Undo()
{
	if (m_MapStack.size() == 0)
		DebugMessage("Cannot Undo!");
	else
	{
		m_Map = m_MapStack.back();
		m_MapStack.pop_back();
	}
}