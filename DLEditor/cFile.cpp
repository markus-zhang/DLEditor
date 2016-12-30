#include "cFile.h"

cFile::cFile(){}
cFile::~cFile(){}

void cFile::LoadDMLObject()
{
	cDMLObject parent;
	parent.m_Tag = "parent tag";
	parent.m_Parameter = "parent parameter";
	parent.m_ParameterValue = "parent parameter value";
	parent.m_Value = "";

	cDMLObject child;
	child.m_Tag = "child tag";
	child.m_Parameter = "";
	child.m_ParameterValue = "";
	child.m_Value = "child value";

	cDMLObject grandchild1;
	grandchild1.m_Tag = "grandchild1 tag";
	grandchild1.m_Parameter = "grandchild1 parameter";
	grandchild1.m_ParameterValue = "grandchild1 parameter value";
	grandchild1.m_Value = "grandchild1 value";

	cDMLObject grandchild2;
	grandchild2.m_Tag = "grandchild2 tag";
	grandchild2.m_Parameter = "grandchild2 parameter";
	grandchild2.m_ParameterValue = "grandchild2 parameter value";
	grandchild2.m_Value = "grandchild2 value";

	cDMLObjectNode* m_DMLTreeChild;
	cDMLObjectNode* m_DMLTreeGrandChild1;
	cDMLObjectNode* m_DMLTreeGrandChild2;

	m_DMLTree = new cDMLObjectNode(parent);
	m_DMLTreeChild = new cDMLObjectNode(child);
	m_DMLTreeGrandChild1 = new cDMLObjectNode(grandchild1);
	m_DMLTreeGrandChild2 = new cDMLObjectNode(grandchild2);
	
	m_DMLTree->AddChild(m_DMLTreeChild);
	m_DMLTreeChild->AddChild(m_DMLTreeGrandChild1);
	m_DMLTreeChild->AddChild(m_DMLTreeGrandChild2);

	m_DMLTree->Walk();
}

bool cFile::CheckFile(const char* filename, int filetype)
{
	switch (filetype)
	{
	case 0:		// Reading GUI ini
		std::string holder;
		std::ifstream gui_file (filename);
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
	std::ifstream map_file;
	map_file.open(guisetting);
	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
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
	std::ifstream map_file;
	map_file.open(guisetting);
	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
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
	std::ifstream map_file;
	map_file.open(entityfile);
	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
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

bool cFile::LoadMap(const char* filename, std::vector<cTile>& mapvector, 
					cGraphics* graph, SDL_Texture* bitmap)
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

bool cFile::LoadGameMap(const char* filename,
	cGraphics* graph, SDL_Texture* bitmap,
	cGameLevel& level)
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

	//Read map file line by line

	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		if (sTemp.length() <= 0) return false;
		if (sTemp.at(0) == '<') {
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

cGameLevel cFile::ReturnMap(const char* filename, cGraphics* graph,
	SDL_Texture* bitmap)
{
	cGameLevel level;
	//cEntityTest player;
	//player = ReturnSingleEntityTest("./Resource/entity.player.setting", graph, );
	std::ifstream map_file;
	map_file.open(filename);
	if (!map_file.is_open())
	{
		std::cout << "File " << filename << " not found!" << "\n";
	}

	std::string sTemp;
	cTile m_Holder;
	std::string PlayerStartX, PlayerStartY;

	//Read map file line by line
	//Head Lines
	getline(map_file, sTemp);
	if (sTemp.length() <= 0) DebugMessage("Empty Line!");
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
		//DebugMessage("Player X" + PlayerStartX);
	}
	else DebugMessage("Wrong data file!");

	// Get Player Start Y
	getline(map_file, sTemp);
	if (m_Parser.GetTag(sTemp) == "PlayerY")
	{
		PlayerStartY = m_Parser.GetContent(sTemp);
		//DebugMessage("Player Y" + PlayerStartY);
	}
	else DebugMessage("Wrong data file!");

	if (PlayerStartX.length() >= 0 && PlayerStartY.length() >= 0)
	{
		level.SetPlayerStart(atoi(PlayerStartX.c_str()),
			atoi(PlayerStartY.c_str()));
	}
	//std::cout << "Player X" << level.GetX() << "\n";

	while (!map_file.eof())
	{
		//getline(map_file, sTemp);
		//if (sTemp.length() <= 0) break;
		//if (sTemp.at(0) == '<') {
		//	//MODIFY NEED TO GET RID OF TAGS!!!
		//	level.SetID(m_Parser.GetContent(sTemp.c_str()));
		//	getline(map_file, sTemp);
		//}
		getline(map_file, sTemp);
		m_Holder.SetID(sTemp.c_str());

		getline(map_file, sTemp);
		m_Holder.SetX(atoi(sTemp.c_str()));
		//std::cout << m_Holder.GetX() << " ";

		getline(map_file, sTemp);
		m_Holder.SetY(atoi(sTemp.c_str()));
		//std::cout << m_Holder.GetY() << " ";

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
	level.SetTexture(bitmap);
	return level;
}

void cFile::LoadWorld(const char* worldfile,
	cGraphics* graph, SDL_Texture* bitmap,
	std::vector<cGameLevel>& world)
{
	std::ifstream world_file;
	world_file.open(worldfile);
	if (!world_file.is_open())
	{
		std::cout << "File not found!";
		return;
	}
	std::string sTemp;
	int count;
	count = 0;

	while (!world_file.eof())
	{
		count += 1;
		std::cout << count << "\n";
		getline(world_file, sTemp);
		if (sTemp.size() <= 0) return;
		DebugMessage(sTemp);
		world.push_back(ReturnMap(sTemp.c_str(), graph, bitmap));
	}
}

bool cFile::LoadEntityFromFile(const char* filename,
			std::vector<cEntity>& entityvector, 
			cGraphics* graph, SDL_Texture* bitmap)	{
	std::ifstream entity_file;
	entity_file.open(filename);
	if (!entity_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
	cEntity m_Holder;
	std::vector<cEntity>::iterator it;

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
	std::ifstream entity_file;
	entity_file.open(filename);
	if (!entity_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
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

bool cFile::LoadEntityTest(const char* filename, std::vector<cEntityTest>& entity,
	cGraphics* graphics, SDL_Texture* texture)
{
	DebugMessage("BEGIN TEST");
	std::ifstream entity_file;
	entity_file.open(filename);
	if (!entity_file.is_open())
	{
		DebugMessage("File not found!");
		return false;
	}

	std::string sTemp, sTag;
	cEntityTest m_Holder;

	//Read item file line by line

	while (!entity_file.eof())
	{
		getline(entity_file, sTemp);
		//DebugMessage(sTemp);
		sTag = m_Parser.GetTag(sTemp);
		//DebugMessage(sTag);
		if (sTag == "entity") {
			//A new entity
			cEntityTest item;
			while (!entity_file.eof()) {
				getline(entity_file, sTemp);
				sTag = m_Parser.GetTag(sTemp);
				//DebugMessage(sTag);
				if (sTemp == "</entity>") {
					DebugMessage("End of entity");
					//End of item
					item.SetGraphics(graphics, texture);
					entity.push_back(item);
					break;
				}
				if (sTag == "attribute") {
					//A new attribute
					cAttributes attribute;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</attribute>") {
							//End of Attribute
							DebugMessage("End of attributes");
							item.SetAttributes(attribute);
							break;
						}
						if (sTag == "hp") {
							attribute.m_HP = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "ac") {
							attribute.m_AC = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "dmgdice") {
							attribute.m_DmgDice = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "speed") {
							attribute.m_Speed = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "exp") {
							attribute.m_Exp = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "gold") {
							attribute.m_Gold = atoi(m_Parser.GetContent(sTemp).c_str());
						}
					}
				}
				if (sTag == "animation") {
					//A new animation
					cAnimation animation;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</animation>") {
							//End of Animation
							DebugMessage("End of animation");
							item.RegisterAnimation(animation);
							break;
						}
						if (sTag == "id") {
							animation.SetID(m_Parser.GetContent(sTemp));
						}
						if (sTag == "clipx") {
							animation.SetX(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "clipy") {
							animation.SetY(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "width") {
							animation.SetW(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "height") {
							animation.SetH(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "number") {
							std::cout << sTemp << "\n";
							animation.SetNum(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "deltatime") {
							animation.SetDelta(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "life") {
							std::cout << "Life " << m_Parser.GetContent(sTemp) << "\n";
							animation.SetLife(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
					}
				}
			}
		}
	}
	DebugMessage("END TEST");
	return true;
}

cEntityTest cFile::ReturnSingleEntityTest(const char* filename,
	cGraphics* graphics, SDL_Texture* texture)
{
	DebugMessage("BEGIN TEST");
	std::ifstream entity_file;
	entity_file.open(filename);
	assert(entity_file.is_open());

	std::string sTemp, sTag;
	cEntityTest item;

	//Read item file line by line

	while (!entity_file.eof())
	{
		getline(entity_file, sTemp);
		//DebugMessage(sTemp);
		sTag = m_Parser.GetTag(sTemp);
		//DebugMessage(sTag);
		if (sTag == "entity") {
			//A new entity
			while (!entity_file.eof()) {
				getline(entity_file, sTemp);
				sTag = m_Parser.GetTag(sTemp);
				//DebugMessage(sTag);
				if (sTemp == "</entity>") {
					DebugMessage("End of entity");
					//End of item
					item.SetGraphics(graphics, texture);
					//entity.push_back(item);
					break;
				}
				if (sTag == "id")
				{
					item.SetID(m_Parser.GetContent(sTemp));
					DebugMessage(m_Parser.GetContent(sTemp));
				}
				if (sTag == "attribute") {
					//A new attribute
					cAttributes attribute;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</attribute>") {
							//End of Attribute
							DebugMessage("End of attributes");
							item.SetAttributes(attribute);
							break;
						}
						if (sTag == "hp") {
							attribute.m_HP = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "ac") {
							attribute.m_AC = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "dmgdice") {
							attribute.m_DmgDice = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "speed") {
							attribute.m_Speed = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "exp") {
							attribute.m_Exp = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "gold") {
							attribute.m_Gold = atoi(m_Parser.GetContent(sTemp).c_str());
						}
					}
				}
				if (sTag == "animation") {
					//A new animation
					cAnimation animation;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</animation>") {
							//End of Animation
							DebugMessage("End of animation");
							item.RegisterAnimation(animation);
							break;
						}
						if (sTag == "id") {
							animation.SetID(m_Parser.GetContent(sTemp));
						}
						if (sTag == "clipx") {
							animation.SetX(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "clipy") {
							animation.SetY(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "width") {
							animation.SetW(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "height") {
							animation.SetH(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "number") {
							std::cout << sTemp << "\n";
							animation.SetNum(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "deltatime") {
							animation.SetDelta(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "life") {
							std::cout << "Life " << m_Parser.GetContent(sTemp) << "\n";
							animation.SetLife(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
					}
				}
			}
		}
	}
	DebugMessage("END TEST");
	return item;
}

bool cFile::LoadEntityTestFactory(const char* filename,
	cGraphics* graphics, SDL_Texture* texture,
	std::vector<cEntityTest*>& factory)
{
	DebugMessage("BEGIN TEST");
	std::ifstream entity_file;
	entity_file.open(filename);
	assert(entity_file.is_open());

	std::string sTemp, sTag;
	//cEntityTest* item = new cEntityTest;

	//Read item file line by line

	while (!entity_file.eof())
	{
		getline(entity_file, sTemp);
		//DebugMessage(sTemp);
		sTag = m_Parser.GetTag(sTemp);
		//DebugMessage(sTag);
		if (sTag == "entity") {
			//A new entity
			cEntityTest* item = new cEntityTest;
			while (!entity_file.eof()) {
				getline(entity_file, sTemp);
				sTag = m_Parser.GetTag(sTemp);
				//DebugMessage(sTag);
				if (sTemp == "</entity>") {
					DebugMessage("End of entity");
					//End of item
					item->SetGraphics(graphics, texture);
					factory.push_back(item);
					break;
				}
				if (sTag == "id")
				{
					item->SetID(m_Parser.GetContent(sTemp));
					DebugMessage(m_Parser.GetContent(sTemp));
				}
				if (sTag == "attribute") {
					//A new attribute
					cAttributes attribute;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</attribute>") {
							//End of Attribute
							//DebugMessage("End of attributes");
							item->SetAttributes(attribute);
							break;
						}
						if (sTag == "hp") {
							attribute.m_HP = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "ac") {
							attribute.m_AC = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "dmgdice") {
							attribute.m_DmgDice = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "speed") {
							attribute.m_Speed = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "exp") {
							attribute.m_Exp = atoi(m_Parser.GetContent(sTemp).c_str());
						}
						if (sTag == "gold") {
							attribute.m_Gold = atoi(m_Parser.GetContent(sTemp).c_str());
						}
					}
				}
				if (sTag == "animation") {
					//A new animation
					cAnimation animation;
					while (!entity_file.eof()) {
						getline(entity_file, sTemp);
						sTag = m_Parser.GetTag(sTemp);
						if (sTemp == "</animation>") {
							//End of Animation
							//DebugMessage("End of animation");
							item->RegisterAnimation(animation);
							break;
						}
						if (sTag == "id") {
							animation.SetID(m_Parser.GetContent(sTemp));
						}
						if (sTag == "clipx") {
							animation.SetX(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "clipy") {
							animation.SetY(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "width") {
							animation.SetW(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "height") {
							animation.SetH(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "number") {
							std::cout << sTemp << "\n";
							animation.SetNum(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "deltatime") {
							animation.SetDelta(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
						if (sTag == "life") {
							std::cout << "Life " << atoi(m_Parser.GetContent(sTemp).c_str()) << "\n";
							animation.SetLife(atoi(m_Parser.GetContent(sTemp).c_str()));
						}
					}
				}
			}
		}
	}
	DebugMessage("END TEST");
	std::cout << factory.size() << " items in factory" << "\n";
	return true;
}

bool cFile::LoadInventoryFromFile(const char* filename,
	std::vector<cItem>& inventory) {
	std::ifstream inv_file;
	inv_file.open(filename);
	if (!inv_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp, sTag;
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
					cItemEffect effect;
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
	std::ifstream newgui;
	newgui.open(newguisetting);
	if (!newgui.is_open())
	{
		std::cout << "File not found!";
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

bool cFile::SaveMap(const char* filename, const std::vector<cTile>& mapvector,
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
	for (auto it = mapvector.begin(); it != mapvector.end(); it ++)
	{
		std::string id = (*it).GetID();
		char access = id.at(0);	// First char of ID
		map_file << (*it).GetID()			<< "\n";
		map_file << (*it).GetX()			<< "\n";
		map_file << (*it).GetY() << "\n";
		map_file << (*it).GetImageX()		<< "\n";
		map_file << (*it).GetImageY()		<< "\n";
		map_file << (*it).GetWidth()		<< "\n";
		map_file << (*it).GetHeight()		<< "\n";
		//map_file << (*it).GetIsAccessible() << "\n";
		std::cout << (*it).GetX() << " " << (*it).GetY() << "\n";
		map_file << access << "\n";
	}
	map_file.close();
	return true;
}

bool cFile::SaveEntity(const char* filename, const std::vector<cEntity>& entityvector)
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
	std::vector<cEntity>::iterator it;
	std::ofstream map_file;

	// Clear the txt before writing
	map_file.open(filename, std::fstream::out | std::fstream::trunc);

	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	//Now save the data line by line
	for (auto it = entityvector.begin(); it != entityvector.end(); it ++)
	{
		std::string id = (*it).GetID();
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

void cFile::Remove(int x, int y, std::vector<cTile>& mapvector)
{
	// Remove the tile with index
	std::vector<cTile>::iterator it;
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
	std::ofstream loadfile(filename);
	if (loadfile.is_open())	return true;
	return false;
}

void cFile::RemoveSpace(std::string& line)
{
	assert(line.size() > 0);
	DebugMessage(line);
	std::string::iterator it;
	//Remove leading space
	for (it = line.begin(); it != line.end(); it++)
	{
		if ((*it) == ' ')
		{
			line.erase(it);
			it = line.begin();
		}
		if ((*it) == '<')
		{
			break;
		}
	}
	// Remove trailing space
	for (it = line.end() - 1; it != line.begin(); it--)
	{
		if ((*it) == ' ')
		{
			line.erase(it);
			it = line.end() - 1;
		}
		if ((*it) == '>')
		{
			break;
		}
	}
	DebugMessage(line);
	return;
}

// DML Experiment
void cFile::BuildDMLTree(std::string filename)
{/*
	// The purpose of the function is to load a well
	// defined entity.template into a DML tree
	DebugMessage("BEGIN BUILDING DML TREE");
	std::ifstream entity_template_file;
	entity_template_file.open(filename);
	assert(entity_template_file.is_open());

	std::string line;
	std::string tag;
	std::string parameter;
	std::string parameter_value;
	std::string value;

	// Begin read
	while (!entity_template_file.eof())
	{
		getline(entity_template_file, line);
		// Remove leading space
		RemoveSpace(line);
		if (line.size() <= 0)
		{
			continue;			// Empty Lines are not processed
		}

		// If not empty, is it legible?
		if (line.at(0) != '<')
		{
			continue;			// Might be comment or garbage
		}

		// Now we have a proper line
		// 1. Is it a full node? i.e. Is the right tag is present?
		if (IsFullNode(line))
		{
			// Then it's a leaf, as the roots are never full nodes
			cDMLObjectNode* leaf = BuildDMLNode(line);
		}
	}
	*/
}