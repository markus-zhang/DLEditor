#include "cEditorButtonAction.h"
#include "DebugTool.h"

void cSaveMapAction::Init(const char* filename,
	const std::vector<cTile>& mapvector,
	std::string mapid, int playerx, int playery)
{
	m_Filename = filename;
	m_Map = mapvector;
	m_MapID = mapid;
	m_PlayerX = playerx;
	m_PlayerY = playery;
}

bool cSaveMapAction::SaveMap(const char* filename,
	const std::vector<cTile>& mapvector,
	std::string mapid, int playerx, int playery)
{
	/*	Saves the map to the file designated
	*****************
	Sample structure of map.txt:
	0		#ClipX
	0		#ClipY
	128		#ScreenX
	32		#ScreenY
	64		#Width
	32		#Height
	1		#Accessible
	******************
	Maybe we can also use TinyXML
	*/
	std::cout << mapvector.size() << "\n";
	std::vector<cTile>::iterator it;
	std::ofstream map_file;
	std::string id = mapid;

	// Clear the txt before writing
	map_file.open(filename, std::fstream::out | std::fstream::trunc);

	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}
	//Now save the data line by line
	//Save map id first
	map_file << "<MapID>" << id << "</MapID>" << "\n";
	//Save player start next
	map_file << "<PlayerX>" << std::to_string(playerx) << "</PlayerX>" << "\n";
	map_file << "<PlayerY>" << std::to_string(playery) << "</PlayerY>" << "\n";
	for (auto it = mapvector.begin(); it != mapvector.end(); it++)
	{
		std::string id = (*it).GetID();
		char access = id.at(0);	// First char of ID
		map_file << (*it).GetID() << "\n";
		map_file << (*it).GetX() << "\n";
		map_file << (*it).GetY() << "\n";
		map_file << (*it).GetImageX() << "\n";
		map_file << (*it).GetImageY() << "\n";
		map_file << (*it).GetWidth() << "\n";
		map_file << (*it).GetHeight() << "\n";
		//map_file << (*it).GetIsAccessible() << "\n";
		std::cout << (*it).GetX() << " " << (*it).GetY() << "\n";
		map_file << access << "\n";
	}
	map_file.close();
	return true;
}

void cSaveMapAction::Execute()
{
	if (m_Filename != NULL && m_Map.size() >= 0 &&
		m_MapID.length() > 0 && m_PlayerX >= 0 && m_PlayerY >= 0)
	{
		SaveMap(m_Filename, m_Map, m_MapID, m_PlayerX, m_PlayerY);
	}
	else
	{
		DebugMessage("SaveMapAction::Execute: Some elements are NULL or of length 0!");
	}
}

/////////////////////////////////////////////////////

void cSaveMapXMLAction::Init(const char* filename,
	const std::vector<cTile>& mapvector,
	std::string mapid, int playerx, int playery)
{
	m_Filename = filename;
	m_Map = mapvector;
	m_MapID = mapid;
	m_PlayerX = playerx;
	m_PlayerY = playery;
}

bool cSaveMapXMLAction::SaveMap(const char* filename,
	const std::vector<cTile>& mapvector,
	std::string mapid, int playerx, int playery)
{
	// The root 
	tinyxml2::XMLNode* pRoot = m_XMLFile.NewElement("MAP");
	m_XMLFile.InsertFirstChild(pRoot);

	// Map id
	tinyxml2::XMLElement* pID = m_XMLFile.NewElement("MapID");
	pID->SetText(mapid.c_str());	// tinyXML2 cannot take string
	pRoot->InsertEndChild(pID);

	// PlayerX and PlayerY
	tinyxml2::XMLElement* pPlayer = m_XMLFile.NewElement("PlayerX");
	pPlayer->SetText(playerx);
	pRoot->InsertEndChild(pPlayer);
	pPlayer = m_XMLFile.NewElement("PlayerY");
	pPlayer->SetText(playery);
	pRoot->InsertEndChild(pPlayer);

	// Map data
	tinyxml2::XMLElement* pTiles = m_XMLFile.NewElement("TILES");
	pRoot->InsertEndChild(pTiles);
	for (auto it = mapvector.begin(); it != mapvector.end(); it++)
	{	
		std::string id = (*it).GetID();
		char access = id.at(0);	// First char of ID
		tinyxml2::XMLElement* pMapElement = m_XMLFile.NewElement("ID");
		pMapElement->SetText((*it).GetID().c_str());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("X");
		pMapElement->SetText((*it).GetX());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("Y");
		pMapElement->SetText((*it).GetY());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("ImageX");
		pMapElement->SetText((*it).GetImageX());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("ImageY");
		pMapElement->SetText((*it).GetImageY());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("Width");
		pMapElement->SetText((*it).GetWidth());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("Height");
		pMapElement->SetText((*it).GetHeight());
		pTiles->InsertEndChild(pMapElement);

		pMapElement = m_XMLFile.NewElement("Access");
		pMapElement->SetText(access);
		pTiles->InsertEndChild(pMapElement);
	}
	//	Save
	m_XMLFile.SaveFile(filename);
	return true;
}

void cSaveMapXMLAction::Execute()
{
	if (m_Filename != NULL && m_Map.size() >= 0 &&
		m_MapID.length() > 0 && m_PlayerX >= 0 && m_PlayerY >= 0)
	{
		SaveMap(m_Filename, m_Map, m_MapID, m_PlayerX, m_PlayerY);
	}
	else
	{
		DebugMessage("SaveMapAction::Execute: Some elements are NULL or of length 0!");
	}
}

/////////////////////////////////////////////////////

void cLoadMapAction::Init(const char* filename,
	cGraphics* graph, SDL_Texture* bitmap,
	cLevel& level)
{
	m_Filename = filename;
	m_Graphics = graph;
	m_Bitmap = bitmap;
	m_Level = level;
}

void cLoadMapAction::Execute()
{
	LoadMap(m_Filename, m_Graphics, m_Bitmap, m_Level);
}

bool cLoadMapAction::LoadMap(const char* filename,
	cGraphics* graph, SDL_Texture* bitmap,
	cLevel& level)
{
	std::ifstream map_file;
	map_file.open(filename);
	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
	cTile m_Holder;
	std::string PlayerStartX, PlayerStartY;

	//Read map file line by line
	//Head Lines
	getline(map_file, sTemp);
	if (sTemp.length() <= 0) return false;
	//Get Map ID
	if (m_Parser.GetTag(sTemp) == "MapID") {
		//MODIFY NEED TO GET RID OF TAGS!!!
		DebugMessage(m_Parser.GetTag(sTemp));
		level.SetID(m_Parser.GetContent(sTemp.c_str()));
	}
	else DebugMessage("Wrong data file!");

	// Get Player Start X
	getline(map_file, sTemp);
	if (m_Parser.GetTag(sTemp) == "PlayerX")
	{
		PlayerStartX = m_Parser.GetContent(sTemp);
		DebugMessage(PlayerStartX);
	}
	else DebugMessage("Wrong data file!");

	getline(map_file, sTemp);
	// Get Player Start Y
	if (m_Parser.GetTag(sTemp) == "PlayerY")
	{
		PlayerStartY = m_Parser.GetContent(sTemp);
		DebugMessage(PlayerStartY);
	}
	else DebugMessage("Wrong data file!");

	if (PlayerStartX.length() >= 0 && PlayerStartY.length() >= 0)
	{
		level.SetPlayerStart(atoi(PlayerStartX.c_str()),
			atoi(PlayerStartY.c_str()));
	}

	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		if (sTemp.length() <= 0) break;
		m_Holder.SetID(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.SetX(atoi(sTemp.c_str()));
		//cout << m_Holder.GetX() << " ";

		getline(map_file, sTemp);
		m_Holder.SetY(atoi(sTemp.c_str()));
		//cout << m_Holder.m_Y << " ";

		getline(map_file, sTemp);
		m_Holder.SetImageX(atoi(sTemp.c_str()));
		//cout << m_Holder.m_ImageX << " ";

		getline(map_file, sTemp);
		m_Holder.SetImageY(atoi(sTemp.c_str()));
		//cout << m_Holder.m_ImageY << " ";

		getline(map_file, sTemp);
		m_Holder.SetWidth(atoi(sTemp.c_str()));
		//cout << m_Holder.m_Width << " ";

		getline(map_file, sTemp);
		m_Holder.SetHeight(atoi(sTemp.c_str()));
		//cout << m_Holder.m_Height << " ";

		getline(map_file, sTemp);
		m_Holder.SetAccess(atoi(sTemp.c_str()));

		//m_Holder.dump();
		m_Holder.SetGraph(graph);
		m_Holder.SetPic(bitmap);
		level.GetMap().push_back(m_Holder);
	}
	map_file.close();
	return true;
}
