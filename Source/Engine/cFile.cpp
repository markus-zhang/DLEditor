#include "cFile.h"

cFile::cFile(){}
cFile::~cFile(){}

bool cFile::CheckFile(const char* filename, int filetype)
{
	switch (filetype)
	{
	case 0:		// Reading GUI ini
		string holder;
		ifstream gui_file (filename);
		gui_file >> holder;				// First item
		// If the first item starts with # then it's OK

		break;
	}
	return true;
}

bool cFile::LoadGeneralButton(const char* guisetting, 
							cGraphics* graphics,
							SDL_Texture* guitexture,
							std::string type, cGUI& gui)
{
	/*	LoadGUI, essentially is the same as LoadMap
		Instead of loading tiles,
		LoadGUI reads "gui.ini" and load GUI
		gui.jpg contains the bitmap of all icons and menus
		*****************
		Sample structure of gui.ini:
		Save	#ID
		0		#ScreenX
		0		#ScreenY
		128		#ClipX
		32		#ClipY
		64		#Width
		32		#Height
		******************
		Maybe we can also use TinyXML
	*/
	ifstream map_file;
	map_file.open(guisetting);
	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cStaticButton m_Holder;
	//Read map file line by line
	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		m_Holder.m_ID = sTemp.c_str();
		
		getline(map_file, sTemp);
		m_Holder.m_X = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.m_Y = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.m_ImageX = atoi(sTemp.c_str());
		//cout << m_Holder.m_ImageX << " ";

		getline(map_file, sTemp);
		m_Holder.m_ImageY = atoi(sTemp.c_str());
		//cout << m_Holder.m_ImageY << " ";

		getline(map_file, sTemp);
		m_Holder.m_Width = atoi(sTemp.c_str());
		//cout << m_Holder.m_Width << " ";

		getline(map_file, sTemp);
		m_Holder.m_Height = atoi(sTemp.c_str());
		//cout << m_Holder.m_Height << " ";

		m_Holder.m_Graphics = graphics;
		m_Holder.m_Bitmap = guitexture;
		
		if (type=="gui")
		{
			gui.GetGeneralButton().push_back(m_Holder);
			//m_GUIButtonVector.push_back(m_Holder);
		}
		if (type=="tile")
		{
			gui.GetTileButton().push_back(m_Holder);
		}
	}
	gui.SetGeneralBoundary((gui.GetGeneralButton())[0].GetX(),
						(gui.GetGeneralButton())[0].GetY());
	return true;
}

bool cFile::LoadPopMenu(const char* guisetting, 
							cGraphics* graphics,
							SDL_Texture* guitexture,
							cGUI& gui)
{
	ifstream map_file;
	map_file.open(guisetting);
	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cStaticButton m_Holder;
	//Read map file line by line
	while (!map_file.eof())	{
		if (getline(map_file, sTemp))	{
			if (sTemp  == "[/Popmenu]")
				break;
		}
		if (getline(map_file, sTemp))	{
			if (sTemp  == "[Popmenu]")	{
				while (!map_file.eof())	{
					getline(map_file, sTemp);
					m_Holder.m_ID = sTemp.c_str();
		
					getline(map_file, sTemp);
					m_Holder.m_X = atoi(sTemp.c_str());

					getline(map_file, sTemp);
					m_Holder.m_Y = atoi(sTemp.c_str());

					getline(map_file, sTemp);
					m_Holder.m_ImageX = atoi(sTemp.c_str());
					//cout << m_Holder.m_ImageX << " ";

					getline(map_file, sTemp);
					m_Holder.m_ImageY = atoi(sTemp.c_str());
					//cout << m_Holder.m_ImageY << " ";

					getline(map_file, sTemp);
					m_Holder.m_Width = atoi(sTemp.c_str());
					//cout << m_Holder.m_Width << " ";

					getline(map_file, sTemp);
					m_Holder.m_Height = atoi(sTemp.c_str());
					//cout << m_Holder.m_Height << " ";

					m_Holder.m_Graphics = graphics;
					m_Holder.m_Bitmap = guitexture;

					gui.GetPopMenu().GetMenu().push_back(m_Holder);
				}
			}
		}
	}
	std::cout << gui.GetPopMenu().Size() << std::endl;
	return true;
}

bool cFile::LoadEntityButton(const char* entityfile, cGraphics* graphics,
							SDL_Texture* entitytexture, cGUI& gui)
{
	/*	*****************
		Sample structure of entity.txt:
		Cleric	<- ID
		0		<- X coordination of its position of entity sprite sheet
		32		<- Y coordination of its position of entity sprite sheet
		0		<- Clip X
		0		<- Clip Y
		32		<- Width
		32		<- Height
		20		<- HP
		10		<- Gold dropped
		5		<- Exp rewarded
		0		<- Interactive?
		1		<- Direction
		4		<- # of frames
		******************
	*/
	ifstream map_file;
	map_file.open(entityfile);
	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cEntity m_Holder;
	//Read map file line by line
	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		m_Holder.SetID(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.SetX(atoi(sTemp.c_str()));
		//cout << m_Holder.m_X << " ";

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
		m_Holder.SetHP(atoi(sTemp.c_str()));

		getline(map_file, sTemp);
		m_Holder.SetGold(atoi(sTemp.c_str()));

		getline(map_file, sTemp);
		m_Holder.SetExp(atoi(sTemp.c_str()));

		getline(map_file, sTemp);
		m_Holder.SetInt(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.SetDir(atoi(sTemp.c_str()));

		getline(map_file, sTemp);
		m_Holder.SetFrame(atoi(sTemp.c_str()));

		//SDL_Delay(100);

		//m_Holder.dump();
		m_Holder.InitialCurrentFrame();	// Set default as there is
										//	such information in .ini
		m_Holder.SetGraph(graphics);
		m_Holder.SetPic(entitytexture);
		gui.GetEntityButton().push_back(m_Holder);
	}
	return true;
}

bool cFile::LoadMap(const char* filename, vector<cTile>& mapvector, 
					cGraphics* graph, SDL_Texture* bitmap)
{
	ifstream map_file;
	map_file.open(filename);
	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cTile m_Holder;

	//Read map file line by line

	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		if (sTemp.length() <= 0) return false;
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
		//cout << m_Holder.m_Access << "\n";

		//SDL_Delay(100);

		//m_Holder.dump();
		m_Holder.SetGraph(graph);
		m_Holder.SetPic(bitmap);
		mapvector.push_back(m_Holder);
	}
	return true;
}

bool cFile::LoadMap(const char* filename, 
					cGraphics* graph, SDL_Texture* bitmap, 
					cLevel& level)
{
	ifstream map_file;
	map_file.open(filename);
	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cTile m_Holder;

	//Read map file line by line

	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		if (sTemp.length() <= 0) return false;
		if (sTemp.at(0) == '<')	{
			//MODIFY NEED TO GET RID OF TAGS!!!
			level.SetID(m_Parser.GetContent(sTemp.c_str()));
			getline(map_file, sTemp);
		}

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
	return true;
}

bool cFile::LoadEntityFromFile(const char* filename,
			vector<cEntity>& entityvector, 
			cGraphics* graph, SDL_Texture* bitmap)	{
	ifstream entity_file;
	entity_file.open(filename);
	if (!entity_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cEntity m_Holder;
	vector<cEntity>::iterator it;

	//Read entity file line by line

	while (!entity_file.eof())
	{
		getline(entity_file, sTemp);
		if (sTemp.length() <= 0) return false;
		m_Holder.SetID(sTemp.c_str());


		getline(entity_file, sTemp);
		m_Holder.SetX(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetY(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetImageX(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetImageY(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetWidth(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetHeight(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetHP(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetGold(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetExp(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetInt(sTemp.c_str());

		getline(entity_file, sTemp);
		m_Holder.SetDir(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetFrame(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetType(atoi(sTemp.c_str()));

		m_Holder.SetGraph(graph);
		m_Holder.SetPic(bitmap);
		m_Holder.InitialCurrentFrame();
		m_Holder.SetAniRate();
		entityvector.push_back(m_Holder);
	}
	return true;
}

bool cFile::LoadEntityFromFile(const char* filename,
								cGraphics* graph, SDL_Texture* bitmap,
								cLevel& level)	{
	ifstream entity_file;
	entity_file.open(filename);
	if (!entity_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp;
	cEntity m_Holder;

	//Read entity file line by line

	while (!entity_file.eof())
	{
		getline(entity_file, sTemp);
		if (sTemp.length() <= 0) return false;
		m_Holder.SetID(sTemp.c_str());


		getline(entity_file, sTemp);
		m_Holder.SetX(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetY(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetImageX(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetImageY(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetWidth(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetHeight(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetHP(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetGold(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetExp(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetInt(sTemp.c_str());

		getline(entity_file, sTemp);
		m_Holder.SetDir(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetFrame(atoi(sTemp.c_str()));

		getline(entity_file, sTemp);
		m_Holder.SetType(atoi(sTemp.c_str()));

		m_Holder.SetGraph(graph);
		m_Holder.SetPic(bitmap);
		m_Holder.InitialCurrentFrame();
		m_Holder.SetAniRate();
		(level.GetEntity()).push_back(m_Holder);
	}
	return true;
}

bool cFile::LoadInventoryFromFile(const char* filename,
	vector<cItem>& inventory) {
	ifstream inv_file;
	inv_file.open(filename);
	if (!inv_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	string sTemp, sTag;
	cItem m_Holder;

	//Read item file line by line

	while (!inv_file.eof())
	{
		getline(inv_file, sTemp);
		//DebugMessage(sTemp);
		sTag = m_Parser.GetTag(sTemp);
		//DebugMessage(sTag);
		if (sTag == "Item") {
			//A new item
			cItem item;
			while (!inv_file.eof()) {
				getline(inv_file, sTemp);
				sTag = m_Parser.GetTag(sTemp);
				//DebugMessage(sTag);
				if (sTemp == "</Item>") {
					DebugMessage("End of Item");
					//End of item
					inventory.push_back(item);
					break;
				}
				if (sTag == "Name")		{
					item.SetName(m_Parser.GetContent(sTemp));
				}
				if (sTag == "Class")	{
					item.SetClass(m_Parser.GetContent(sTemp));
				}
				if (sTag == "HP") {
					int hp = atoi(m_Parser.GetContent(sTemp).c_str());
					item.SetHP(hp);
				}
				if (sTag == "Effect") {
					cEffect effect;
					effect.m_Effect = m_Parser.GetContent(sTemp);
					effect.m_Value = m_Parser.ExtractTagValue(sTag);
					item.AddEffect(effect);
				}
			}
		}
	}
	std::cout << "You have " << inventory.size() << " items." <<"\n";
	return true;
}

bool cFile::LoadBasicButtonFromFile(std::string newguisetting, cGraphics* graphics,
	SDL_Texture* newguitexture, cGUI& gui) {
	ifstream newgui;
	newgui.open(newguisetting);
	if (!newgui.is_open())
	{
		cout << "File not found!";
		return false;
	}

	std::string sTemp, sTag;
	cItem m_Holder;

	//Read item file line by line

	while (!newgui.eof())
	{
		getline(newgui, sTemp);
		//DebugMessage(sTemp);
		sTag = m_Parser.GetTag(sTemp);
		//DebugMessage(sTag);
		if (sTag == "cGUIBasicButton") {
			//A new basic button
			cGUIBasicButton button;
			std::string id, caption;
			int x, y, width, height;
			while (!newgui.eof()) {
				getline(newgui, sTemp);
				sTag = m_Parser.GetTag(sTemp);
				//DebugMessage(sTag);
				if (sTemp == "</cGUIBasicButton>") {
					DebugMessage("End of Button");
					//End of Button
					button.Load(graphics, newguitexture,
						x, y, 0, 0, width, height, id, caption);
					gui.GetBasicButton().push_back(button);
					break;
				}
				if (sTag == "id") {
					id = m_Parser.GetContent(sTemp);
				}
				if (sTag == "caption") {
					caption = m_Parser.GetContent(sTemp);
					DebugMessage(caption);
				}
				if (sTag == "x") {
					x = atoi(m_Parser.GetContent(sTemp).c_str());
				}
				if (sTag == "y") {
					y = atoi(m_Parser.GetContent(sTemp).c_str());
				}
				if (sTag == "width") {
					width = atoi(m_Parser.GetContent(sTemp).c_str());
				}
				if (sTag == "height") {
					height = atoi(m_Parser.GetContent(sTemp).c_str());
				}
			}
		}
	}
	return true;
}

bool cFile::SaveMap(const char* filename, const vector<cTile>& mapvector,
					std::string mapid)
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
	vector<cTile>::iterator it;
	ofstream map_file;
	std::string id = mapid;

	// Clear the txt before writing
	map_file.open(filename, fstream::out | fstream::trunc);

	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	//Now save the data line by line
	//Save map id first
	map_file << "<MapID>" << id << "</MapID>" << "\n";
	for (auto it = mapvector.begin(); it != mapvector.end(); it ++)
	{
		string id = (*it).GetID();
		char access = id.at(0);	// First char of ID
		map_file << (*it).GetID()			<< "\n";
		map_file << (*it).GetX()			<< "\n";
		map_file << (*it).GetY()			<< "\n";
		map_file << (*it).GetImageX()		<< "\n";
		map_file << (*it).GetImageY()		<< "\n";
		map_file << (*it).GetWidth()		<< "\n";
		map_file << (*it).GetHeight()		<< "\n";
		//map_file << (*it).GetIsAccessible() << "\n";
		map_file << access << "\n";
	}
	map_file.close();
	return true;
}

bool cFile::SaveEntity(const char* filename, const vector<cEntity>& entityvector)
{
	/*	Saves the entity to the file designated
		*****************
		Sample structure of entity.sav:
		Cleric	#m_ID
		0		#m_X
		0		#m_Y
		128		#Image_X
		32		#Image_Y
		32		#m_Width
		32		#m_Height
		10		#m_HP
		20		#m_Gold
		10		#m_Exp
		0		#m_Int
		0		#m_Direct
		0		#m_Frame
		******************
		No need to save the default variables e.g. m_CurrentFrame
		Maybe we can also use TinyXML
	*/
	vector<cEntity>::iterator it;
	ofstream map_file;

	// Clear the txt before writing
	map_file.open(filename, fstream::out | fstream::trunc);

	if (!map_file.is_open())
	{
		cout << "File not found!";
		return false;
	}

	//Now save the data line by line
	for (auto it = entityvector.begin(); it != entityvector.end(); it ++)
	{
		string id = (*it).GetID();
		char type = id.at(0);	// First char of ID

		map_file << (*it).GetID()			<< "\n";
		map_file << (*it).GetX()			<< "\n";
		map_file << (*it).GetY()			<< "\n";
		map_file << (*it).GetImageX()		<< "\n";
		map_file << (*it).GetImageY()		<< "\n";
		map_file << (*it).GetWidth()		<< "\n";
		map_file << (*it).GetHeight()		<< "\n";
		map_file << (*it).GetHP()			<< "\n";
		map_file << (*it).GetGold()			<< "\n";
		map_file << (*it).GetExp()			<< "\n";
		map_file << (*it).GetInteractive()	<< "\n";
		map_file << (*it).GetDirect()		<< "\n";
		map_file << (*it).GetFrame()		<< "\n";
		map_file << type					<< "\n";
	}
	map_file.close();
	return true;
}

void cFile::Remove(int x, int y, vector<cTile>& mapvector)
{
	// Remove the tile with index
	vector<cTile>::iterator it;
	if (mapvector.size() == 0)
	{
		//cout << "No Save!" << "\n";
		return;
	}

	for (it = mapvector.begin(); it != mapvector.end(); it ++)
	{
		if ((*it).GetX() == x && (*it).GetY() == y)
		{
			mapvector.erase(it);
			break;
		}
	}
}

//Utility fiesystem functions

bool cFile::CanFindFile(std::string filename) {
	ofstream loadfile(filename);
	if (loadfile.is_open())	return true;
	return false;
}