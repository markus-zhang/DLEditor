#ifndef CGUI_
#define CGUI_

#include "cStaticButton.h"
#include "cTextInput.h"
#include <vector>
#include "cEntity.h"
#include "cGUIPopMenu.h"
#include "cGUIBasicButton.h"

class cGUI
{
public:
	std::vector<cGUIBasicButton> m_BasicButton;
private:
	std::vector<cStaticButton> m_GeneralButton;
	std::vector<cStaticButton> m_TileButton;
	std::vector<cEntity> m_EntityButton;
	cGUIPopMenu m_PopMenu;

	int m_GeneralBoundaryX;		// To check if a GUI button
	int m_GeneralBoundaryY;		// has been clicked on
	int m_MaximumTileDisplay;	// set to 10
	int m_TileXBias, m_EntityXBias;
public:
	cGUI();
	~cGUI();
	/*void LoadGeneral(cGraphics* graphics, SDL_Texture* texture,
					cFile* filemanager, string filename);*/
	std::vector<cGUIBasicButton>& GetBasicButton() {
		return m_BasicButton;
	}
	std::vector<cStaticButton>& GetGeneralButton();
	std::vector<cStaticButton>& GetTileButton();
	std::vector<cEntity>& GetEntityButton();
	cGUIPopMenu& GetPopMenu();
	//cTextInput& GetInputBox()	{ return m_MapID; }
	int GetBoundaryX()	{ return m_GeneralBoundaryX; }
	int GetBoundaryY()	{ return m_GeneralBoundaryY; }
	int GetTileXBias()	{ return m_TileXBias; }
	void SetTileXBias(int xbias)	{ m_TileXBias = xbias; }
	void OnClickTileRightScroll();
	void OnClickTileLeftScroll();
	bool CanClickTileRightScroll();
	bool CanClickTileLeftScroll();
	void onClickEntityRightScroll();
	void onClickEntityLeftScroll();
	bool IsOnFloat(int mousex, int mousey);

	void Draw();

	void SetGeneralBoundary(int x, int y)	{ 
		m_GeneralBoundaryX = x;
		m_GeneralBoundaryY = y;
	}
	cEntity GetEntityByID(std::string ID, int x, int y);
};

#endif