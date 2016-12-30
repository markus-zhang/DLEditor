#include "cGUI.h"

cGUI::cGUI()	{
	m_GeneralBoundaryX = m_GeneralBoundaryY = 0;
	m_TileXBias = m_EntityXBias = 0;
	m_MaximumTileDisplay = EDITOR_TILE_MAXIMUM;
}
cGUI::~cGUI(){}

std::vector<cStaticButton>& cGUI::GetGeneralButton()	{
	return m_GeneralButton;
}

std::vector<cStaticButton>& cGUI::GetTileButton()	{
	return m_TileButton;
}

std::vector<cEntity>& cGUI::GetEntityButton()	{
	return m_EntityButton;
}

cGUIPopMenu& cGUI::GetPopMenu()	{
	return m_PopMenu;
}

void cGUI::Draw()
{
	if (m_TileButton.size() <= m_MaximumTileDisplay)	{
		for (size_t i=0; i < m_TileButton.size(); i++)	{
			m_TileButton[i].DrawBias(m_TileXBias);
		}
	}
	else	{
		for (size_t i=0; i < m_MaximumTileDisplay + m_TileXBias/32; i++)	{
			m_TileButton[i].DrawBias(m_TileXBias);
		}
	}
	for (size_t i=0; i<m_EntityButton.size(); i++)	{
		m_EntityButton[i].Draw();
	}
	for (size_t i=0; i<m_GeneralButton.size(); i++)	{
		if (m_GeneralButton[i].GetID()=="TileScrollRight" &&
			!CanClickTileRightScroll())	{
			//m_GeneralButton[i].DrawModulate(255,255,0,0);
			m_GeneralButton[i].Draw();
		}
		else if (m_GeneralButton[i].GetID()=="TileScrollLeft" &&
				!CanClickTileLeftScroll())
				//m_GeneralButton[i].DrawModulate(255,255,0,0);
				m_GeneralButton[i].Draw();
		else
			m_GeneralButton[i].Draw();
	}
	for (size_t i = 0; i<m_BasicButton.size(); i++) {
			m_BasicButton[i].Draw(0, 0);
	}
	m_PopMenu.Draw();
}

cEntity cGUI::GetEntityByID(std::string id, int x, int y)	{
	std::vector<cEntity>::iterator it;
	cEntity temp;
	for (it = m_EntityButton.begin(); it != m_EntityButton.end(); it++)	{
		if ((*it).GetID() == id)	{
			temp = *it;
			temp.SetX(x);
			temp.SetY(y);
			return temp;
		}
	}
}

void cGUI::OnClickTileRightScroll()	{
	//1. Check whether we can move to the right or not
	if (m_TileButton.size() <= m_MaximumTileDisplay + m_TileXBias/32)
		return;
	m_TileXBias += 32;
}

void cGUI::OnClickTileLeftScroll()	{
	//1. Check whether we can move to the left or not
	if (m_TileXBias < 32) return;
	m_TileXBias -= 32;
}

bool cGUI::CanClickTileRightScroll()	{
	if (m_TileButton.size() <= m_MaximumTileDisplay + m_TileXBias/32)
		return false;
	return true;
}

bool cGUI::CanClickTileLeftScroll()	{
	if (m_TileXBias < 32)	return false;
	return true;
}

bool cGUI::IsOnFloat(int mousex, int mousey) {
	std::vector<cGUIBasicButton>::iterator it;
	for (it = m_BasicButton.begin(); it != m_BasicButton.end(); it++) {
		if ((*it).IsOnFloat(mousex, mousey)) {
			(*it).OnFloat();
			return true;
		}
		else
		{
			(*it).Reset();
		}
	}
	//return m_TestButton.IsOnFloat(mousex, mousey);
}