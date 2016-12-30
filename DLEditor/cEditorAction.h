#ifndef CEDITORACTION_H_
#define CEDITORACTION_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "cTile.h"

class cFile;


class cAction
{
public:
	virtual void Execute() = 0;
};

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

#endif
