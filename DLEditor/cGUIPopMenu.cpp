#include "cGUIPopMenu.h"

cGUIPopMenu::cGUIPopMenu()	{
	m_Activate = false;
	m_Type = "entity";
}

cGUIPopMenu::~cGUIPopMenu()	{
}

cGUIPopMenu::cGUIPopMenu(std::string type, int x, int y)	{
	//Comment: x and y are the coordinates of the entity/tile
	//i.e. the respective m_X and m_Y. So the we should move
	//out own m_X 32 pixels away and keep the same m_Y for the 
	//first menu object;
	//Assuming that the menu objects are also 32 * 32, then
	//the first object is at (m_X+32, m_Y), the second is at
	//(m_X+32, m_Y+32), the thrid is at (m_X+32, m_Y+64)
}

void cGUIPopMenu::Draw()	{
	if (m_Activate == false)	return;
	m_Menu[0].m_X = m_X + 32;
	m_Menu[0].m_Y = m_Y;
	if (m_Type == "entity")	{
		m_Menu[1].m_X = m_X + 32;
		m_Menu[1].m_Y = m_Y + 32;
		m_Menu[2].m_X = m_X + 32;
		m_Menu[2].m_Y = m_Y + 64;
	}
	else	{
		m_Menu[1].m_X = -32;
		m_Menu[1].m_Y = -32;
		m_Menu[2].m_X = m_X + 32;
		m_Menu[2].m_Y = m_Y + 32;
	}
	std::vector<cStaticButton>::iterator it;
	for (it = m_Menu.begin(); it != m_Menu.end(); it++)	{
		(*it).Draw();
	}
}

void cGUIPopMenu::DrawHide(std::string type, int x, int y)	{
	m_Activate = !m_Activate;
	if (m_Activate == true)	{
		m_Type = type;
		m_X = x;
		m_Y = y;
	}
}

void cGUIPopMenu::ShutDown()	{
	m_Activate = false;
}

std::string cGUIPopMenu::ReturnMenuID(int x, int y)	{
	std::vector<cStaticButton>::iterator it;
	for (it = m_Menu.begin(); it != m_Menu.end(); it++)	{
		if ((*it).OnClick(x, y))	return (*it).GetID();
	}
}