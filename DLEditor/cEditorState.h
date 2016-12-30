//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// Description: This is the class for the main game state. 
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Enums.h"
#include "cState.h"
#include "cTile.h"
#include "cMouse.h"
#include "cGUI.h"
#include "cStaticButton.h"
#include "cCursor.h"
#include "cLevel.h"
#include "cFile.h"
#include <vector>
#include <stack>
#include "DebugTool.h"
#include "sqlite3.h"
#include "cDatabase.h"
#include "cEditorPlayerStart.h"


class cEditorState : public cState
{
public:
	cEditorState(cGraphics* graphics, cInput* input);

	~cEditorState();

	//void SaveMap(const char* filename);		// To save tiles
	
	virtual bool Run(cStateManager* state_manager);
	virtual void HandleInput(cStateManager* state_manager);
	virtual void BlinkTile();
	std::string GetEntityIDByLocation();
	std::string GetTileIDByLocation();
	void DeleteTile();
	
private:
	int GetNearestX();
	int GetNearestY();

	void Load(const char* mapfile, const char* entityfile);

	int	TileCount;
	int m_Mode;				// Tile, Obj and Access modes

	int GUIBoundaryX;		// To check if a GUI button
	int GUIBoundaryY;		// has been clicked on

	int EntityBoundaryX;	// To check if clicks on Entity
	int EntityBoundaryY;

	bool b_Error;			// Critical error flag

	void Reset();

	//SDL 2.0 code
	SDL_Texture* m_Tilemap;		// contains the tileset
	SDL_Texture* m_Cursor;		// contains the painter cursor
	SDL_Texture* m_ButtonPic;	// contains resources of buttons
	SDL_Texture* m_EntityPic;	// contains the sprite sheet of entities
	SDL_Texture* m_TestPic;

	cCursor m_Painter;
	/*
		Method of showing and saving and loading the map
		1. Map boundary is 1024*1024
		2. We will only show 512*512 at any given time
		3. First we check m_XBias and m_YBais (from 0~512)
		4. say that m_XBias = 64 and m_YBias = 192
		5. which means we will show any tile that m_X>=64
		6. and m_Y>=192, i.e. we need to modify the Draw()
		7. of cTile:
		8. Two parameters will be passed to Draw(), 64 and 192
		9. Draw() will check if the current tile has m_X >=64
		10. and m_Y >= 192, if yes then substract both values
		11. and make m_X_new = m_X-64, m_Y_new = m_Y-192
	*/
	std::vector<cTile>	m_MapVector;				// contains the map information
	int m_XBias, m_YBias;						// scrolling parameters
	//vector<cTile>	m_MapShowVector;			// tiles for show if larger than editor
	std::vector<cEntity> m_EntityVector;				// contains the entity information
	std::vector<std::string> m_EntityIDVector;			// contains the entity id
	cGUI m_GUI;
	//vector<cStaticButton> m_GUIButtonVector;
	std::vector<cStaticButton> m_GUIEntityVector;
	std::vector<cStaticButton> m_GUITileVector;

	cLevel m_LevelManager;

	std::vector < std::vector<cTile> > m_MapStack;		// For Undo
	std::vector < std::vector<cEntity> > m_EntityStack;	// For Undo

	cFile m_FileManager;

	cTextInput m_MapID;
	bool m_MapIDInput;

	//Database
	cDatabase m_Enemy;				// To read the table Enemy
	cDatabase m_EditorConfig;		// All configuration
	//sqlite3* m_database;
	//sqlite3_stmt* m_statement;
	//vector<string> m_tableid;

	//Items
	//vector<cItem> m_Inventory;

	//Scroll Title
	//cScrollTitle* m_TitleTest;
	cEditorPlayerStart m_PlayerStart;
}; 