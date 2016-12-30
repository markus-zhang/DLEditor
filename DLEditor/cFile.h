#ifndef CFILE_
#define CFILE_
// File load/save class

#include <fstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include "cLevel.h"
#include "cGameLevel.h"
#include "cStaticButton.h"
#include "cGUI.h"
#include "cEntity.h"
#include "cEntityTest.h"
#include "DebugTool.h"
#include "cParser.h"
#include "cItem.h"
//#include "cPlayerEntity.h"
#include "cGUIBasicButton.h"
#include "cDMLParser.h"


class cFile
{
friend class cEditorState;
private:
	//cTile m_Tile;		// Information holder
	//vector<cTileFile>	m_MapFile;

	//vector<cStaticButton> m_GUIButtonVector;	//Save/Load/etc.
	//vector<cStaticButton> m_TileButtonVector;	//Tile buttons
	//vector<cEntity>	m_EntityButtonVector;		//Entity buttons
	std::vector<cEntity> m_Entity;					//Entities
	std::vector<std::string> m_EntityString;
	std::vector<cTile> m_Map;
	std::vector < std::vector<cTile> > m_MapStack;		// For Undo
	std::vector < std::vector<cEntity> > m_EntityStack;	// For Undo
	cParser m_Parser;

	// Experimental
	cDMLObjectNode* m_DMLTree;

public:
	// Experimental
	void LoadDMLObject();
	cFile();
	~cFile();

	// CheckFile checks if:
	// 1. File does not exist;
	// 2. File is not of proper arrangement;
	// 3. File is copy-protected.
	// Filetype = GUI ini / Map file
	bool CheckFile(const char* filename, int filetype);

	// "guisetting" gives the information of
	// 1. The name of GUI components (e.g. Save Button)
	// 2. Followed by its position on screen
	// 3. Followed by the position on tileset (clip) of first frame
	// 4. Followed by width and height
	// 5. Followed by the position on tileset of second frame

	/*void Load(const char* gui, const char* tile, const char* entity,
			cGraphics* graphics, SDL_Texture* guitexture,
			SDL_Texture* tiletexture, SDL_Texture* entitytexture);*/

	//bool LoadGUI(const char* guisetting);
	/*bool LoadGUI(const char* guisetting, cGraphics* graphics,
				SDL_Texture* guitexture, std::string type);*/

	bool LoadGeneralButton(const char* tilesetting, cGraphics* graphics,
				SDL_Texture* tiletexture, std::string type,
				cGUI& gui);
	bool LoadPopMenu(const char* tilesetting, cGraphics* graphics,
				SDL_Texture* tiletexture, cGUI& gui);
	bool LoadEntityButton(const char* entitysetting, cGraphics* graphics,
				SDL_Texture* entitytexture, cGUI& gui);

	/*bool LoadEntityGUI(const char* entityfile);
	bool LoadEntityGUI(const char* entityfile, cGraphics* graphics,
				SDL_Texture* entitytexture);*/

	bool SaveEntity(const char* filename, const std::vector<cEntity>& entityvector);
	bool LoadEntityFromFile(const char* filename,
			std::vector<cEntity>& entityvector,
			cGraphics* graph, SDL_Texture* bitmap);
	bool LoadEntityFromFile(const char* filename,
			cGraphics* graph, SDL_Texture* bitmap,
			cLevel& level);
	bool LoadEntityTest(const char* filename, std::vector<cEntityTest>& entity,
		cGraphics* graphics, SDL_Texture* texture);
	cEntityTest ReturnSingleEntityTest(const char* filename,
		cGraphics* graphics, SDL_Texture* texture);
	bool LoadEntityTestFactory(const char* filename,
		cGraphics* graphics, SDL_Texture* texture,
		std::vector<cEntityTest*>& factory);
	bool LoadInventoryFromFile(const char* filename,
		std::vector<cItem>& inventory);
	bool LoadBasicButtonFromFile(std::string newguisetting, cGraphics* graphics,
		SDL_Texture* newguitexture, cGUI& gui);

	void LoadInputBox(cGraphics* graphics, SDL_Texture* texture, cGUI& gui);

	//bool LoadMap(const char* filename);
	bool LoadMap(const char* filename, std::vector<cTile>& mapvector, 
				cGraphics* graph, SDL_Texture* bitmap);
	bool LoadMap(const char* filename, cGraphics* graph,
				SDL_Texture* bitmap, cLevel& level);
	cGameLevel ReturnMap(const char* filename, cGraphics* graph,
		SDL_Texture* bitmap);
	bool LoadGameMap(const char* filename, cGraphics* graph,
		SDL_Texture* bitmap, cGameLevel& level);
	void LoadWorld(const char* worldfile, 
		cGraphics* graph, SDL_Texture* bitmap,
		std::vector<cGameLevel>& world);
	//bool SaveMapOld(const char* filename);

	bool SaveMap(const char* filename, 
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);

	void Remove(int x, int y, std::vector<cTile>& mapvector);

	// Utility filesystem functions
	bool CanFindFile(std::string filename);
	void RemoveSpace(std::string& line);

	// DML Experiment
	void BuildDMLTree(std::string filename);
	bool IsFullNode(std::string line);
	cDMLObjectNode* BuildDMLNode(std::string line);
};
#endif