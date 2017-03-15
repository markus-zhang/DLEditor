#ifndef CEDITORACTION_H_
#define CEDITORACTION_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cAction.h"
#include "cTile.h"
#include "cLevel.h"
#include "cParser.h"
#include "tinyxml2.h"

class cFile;
class cGUI;



class cSaveMapAction : public cAction
{
public:
	void Init(const char* filename,
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);

	bool SaveMap(const char* filename,
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);

	virtual void Execute();		// Wrapper
private:
	const char* m_Filename;
	std::vector<cTile> m_Map;
	std::string m_MapID;
	int m_PlayerX;
	int m_PlayerY;
};

class cSaveMapXMLAction : public cAction
{
public:
	void Init(const char* filename,
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);

	bool SaveMap(const char* filename,
		const std::vector<cTile>& mapvector,
		std::string mapid, int playerx, int playery);

	virtual void Execute();		// Wrapper
private:
	const char* m_Filename;
	std::vector<cTile> m_Map;
	std::string m_MapID;
	int m_PlayerX;
	int m_PlayerY;
	tinyxml2::XMLDocument m_XMLFile;
};

class cLoadMapAction : public cAction
{
public:
	void Init(const char* filename,
		cGraphics* graph, SDL_Texture* bitmap,
		cLevel& level);

	bool LoadMap(const char* filename,
		cGraphics* graph, SDL_Texture* bitmap,
		cLevel& level);

	virtual void Execute();		// Wrapper
private:
	const char* m_Filename;
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;
	cLevel& m_Level;
	cParser m_Parser;
};

/*class cLoadButtonAction : public cAction
{
public:
	void Init(const char* filename,
		cGraphics* graphics, SDL_Texture* bitmap,
		cGUI& gui);

	bool LoadButton(const char* filename,
		cGraphics* graphics, SDL_Texture* bitmap,
		cGUI& gui);

	virtual void Execute();		// Wrapper
private:
	const char* m_Filename;
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;
	cGUI& m_GUI;
	cParser m_Parser;
};*/

#endif
