#include "cEditorGUIAction.h"

void cLoadButtonAction::Init(const char* filename,
	cGraphics* graphics, SDL_Texture* bitmap, cGUI& gui)
{
	m_Filename = filename;
	m_Graphics = graphics;
	m_Bitmap = bitmap;
	m_GUI = gui;
}

bool cLoadButtonAction::LoadButton(const char* filename,
	cGraphics* graphics, SDL_Texture* bitmap, cGUI& gui)
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
	map_file.open(filename);
	if (!map_file.is_open())
	{
		std::cout << "File not found!";
		return false;
	}

	std::string sTemp;
	cGUIBasicButton m_Button;
	//Read map file line by line
	while (!map_file.eof())
	{
		getline(map_file, sTemp);
		//m_Holder.m_ID = sTemp.c_str();
		const char* m_ID = sTemp.c_str();

		getline(map_file, sTemp);
		//m_Holder.m_X = atoi(sTemp.c_str());
		int m_X = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		//m_Holder.m_Y = atoi(sTemp.c_str());
		int m_Y = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		//m_Holder.m_ImageX = atoi(sTemp.c_str());
		int m_ImageX = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		//m_Holder.m_ImageY = atoi(sTemp.c_str());
		int m_ImageY = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		//m_Holder.m_Width = atoi(sTemp.c_str());
		int m_Width = atoi(sTemp.c_str());

		getline(map_file, sTemp);
		//m_Holder.m_Height = atoi(sTemp.c_str());
		int m_Height = atoi(sTemp.c_str());

		//cGraphics* m_Graphics = graphics;
		//SDL_Texture* m_Bitmap = bitmap;

		m_Button.Load(graphics, bitmap, m_X, m_Y,
			m_ImageX, m_ImageY, m_Width, m_Height,
			m_ID, m_ID);

		gui.m_BasicButton.push_back(m_Button);

		/*if (type == "gui")
		{
			gui.GetGeneralButton().push_back(m_Holder);
			m_GUIButtonVector.push_back(m_Holder);
		}
		if (type == "tile")
		{
			gui.GetTileButton().push_back(m_Holder);
		}*/
	}
	//gui.SetGeneralBoundary((gui.GetGeneralButton())[0].GetX(),
		//(gui.GetGeneralButton())[0].GetY());
	return true;
}

void cLoadButtonAction::Execute()
{
	LoadButton(m_Filename, m_Graphics, m_Bitmap, m_GUI);
}