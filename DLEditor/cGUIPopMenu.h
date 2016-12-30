/* Once right clicked on a tile, or an entity, depending on 
which mode is activated, a pop menu will appear on the
right side of the tile/entity. The coordinates is to be
passed as parameters.
Rules:
1. Right click on the pop menu destroys it;
2. There is to be three sub-menus:
	1) Delete, i.e. to delete the tile/entity
	2) Set target ID, this appears when a changelevel
	   entity has been right clicked. A text-input box
	   will immediately appear on the right side of the
	   sub-menu with a "Save" button
	3) Cancel, the pop menu simply destroys itself.
*/
#ifndef CGUIPOPMENU_H_
#define CGUIPOPMENU_H_

#include "cGraphics.h"
#include <vector>
#include "cStaticButton.h"

class cGUIPopMenu	{
private:
	std::vector<cStaticButton> m_Menu;
	int m_X, m_Y;
	std::string m_Type;
	bool m_Activate;
public:
	//1 for tile 2 for entity
	cGUIPopMenu();
	cGUIPopMenu(std::string type, int x, int y);	
	~cGUIPopMenu();
	std::vector<cStaticButton>& GetMenu()	{ return m_Menu; }
	bool GetActivated()	{ return m_Activate; }
	void Draw();
	int Size()	{ return m_Menu.size(); }
	void DrawHide(std::string type, int x, int y);
	void ShutDown();
	std::string ReturnMenuID(int x, int y);
	//void OnClick();
};

#endif