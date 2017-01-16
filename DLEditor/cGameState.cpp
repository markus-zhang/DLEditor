#include "cGameState.h"
#include "cStateManager.h"
#include "Math.h"
#include <iostream>
#include <fstream>

cGameState::cGameState(cGraphics* graphics, cInput* input) :
	cState(graphics, input) {
	m_Tilemap = m_Graphics->LoadTexture("Tileset.png",
		255, 255, 255);
	m_PlayerSprite = m_Graphics->LoadTexture("./Resource/Animation.png",
		255, 255, 255);
	m_PlayerSprite == NULL ? DebugMessage("Player Sprite NULL!") : DebugMessage("Player Sprite successfully loaded");
	//m_FileManager.LoadEntityTest("./Resource/entity.setting", m_Test, m_Graphics, m_TestSprite);

	//SetBias(m_World[m_CurrentLevel].GetXBias(), m_World[m_CurrentLevel].GetYBias());

	//Load World
	m_FileManager.LoadWorld("world.setting", m_Graphics, m_Tilemap, m_World);
	m_CurrentLevel = 0;

	//Load Player
	m_Player = m_FileManager.ReturnSingleEntityTest(
		"./Resource/entity.player.setting", m_Graphics,
		m_PlayerSprite);

	//Load Entity Factory for testing
	m_FileManager.LoadEntityTestFactory("./Resource/entity.setting",
		m_Graphics, m_PlayerSprite, m_EntityFactory.GetFactory());

	std::cout << "We have a total of " << (m_EntityFactory.GetFactory()).size() << " entities" << "\n";
	std::cout << m_EntityFactory.GetFactory()[0]->GetID() << " " << m_EntityFactory.GetFactory()[1]->GetID() << "\n";

	//Let's load some monsters for show
	//Manually set x and y, just for test
	m_Monsters.push_back(m_EntityFactory.Create("Goblin"));
	//m_Monsters.push_back(m_EntityFactory.Create("Orc"));
	m_Monsters[0]->SetLocation(128, 128);
	//m_Monsters[1]->SetLocation(192, 128);

	//Effect
	m_EffectFactory = new cEffectFactory;

	//AI
	m_AIManager.SetMap(m_World[0].GetMap());
	m_AIManager.Init(m_EffectFactory);
	m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());

	


	//m_Cursor = m_Graphics->LoadTexture("cursor.png", 255, 255, 255);
	//m_ButtonPic = m_Graphics->LoadTexture("GUIButton.png", 255, 255, 255);
	//m_EntityPic = m_Graphics->LoadTexture("Entity.png", 0, 0, 0);
	//m_TestPic = m_Graphics->LoadTexture("BasicButtonBackground.png", 255, 255, 255);
	//m_Painter = cCursor(m_Graphics, m_Cursor, EDITOR_MOUSE_X_START,
		//EDITOR_MOUSE_Y_START,
		//EDITOR_CURSOR_WIDTH, EDITOR_CURSOR_HEIGHT);
	//m_Mode = Mode_Tile;
	std::string test = "   <blah>   "+'\n';
	m_FileManager.RemoveSpace(test);
	std::cout << "test is " << test << "\n";

	//Test Inventory
	//m_FileManager.LoadInventoryFromFile("item.txt", m_Inventory);
	//vector<cItem>::iterator it;
	//for (it = m_Inventory.begin(); it != m_Inventory.end(); it++) {
	//(*it).Dump();
	//}
	//m_TitleTest = new cScrollTitle(m_Graphics);
	//m_TitleTest->PreprocessText();
	//m_TitleTest->PreprocessPara();
	//m_TitleTest->Dump();

	// Experimental
		//m_FileManager.LoadDMLObject();
		//std::string test = "     <name> Gobli n</name>";
		//m_FileManager.RemoveSpace(test);
	// Experimental end
}

cGameState::~cGameState() {

}

bool cGameState::Run(cStateManager* state_manager)
{
	static int last_tick = SDL_GetTicks();
	int this_tick = SDL_GetTicks();

	//If still in the same tick, sleep 
	if (this_tick <= last_tick)
	{
		SDL_Delay(1);
		return  m_IsRunning;
	}

	while (last_tick < this_tick)
	{
		HandleInput(state_manager);
		last_tick += 1000 / PHYSICS_FPS;
	}
	m_World[m_CurrentLevel].Update();
	m_EffectFactory->Update();
	//m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
	m_Player.Update();

	//Clear the screen before every frame
	m_Graphics->ClearScreen();

	m_World[m_CurrentLevel].Draw();

	// Test
	m_Player.PlayAnimationBiased("IDLE", 
		m_World[m_CurrentLevel].GetXBias(), 
		m_World[m_CurrentLevel].GetYBias());

	m_Monsters[0]->PlayAnimationBiased("IDLE", 
		m_World[m_CurrentLevel].GetXBias(), 
		m_World[m_CurrentLevel].GetYBias());

	/*m_Monsters[1]->PlayAnimationBiased("IDLE",
		m_World[m_CurrentLevel].GetXBias(),
		m_World[m_CurrentLevel].GetYBias());*/

	// Test END


	m_Graphics->Show();

	return m_IsRunning;
}

void cGameState::HandleInput(cStateManager* state_manager)
{
	// Make sure a new event has happened and handle key presses 
	if (m_Input->GetEvent())
	{
		// Handle user manually closing game window 
		if (m_Input->IsQuit())
		{
			m_IsRunning = false;
			return;  // game is over, exit the method
		}

		// Handle keyboard input here (keys being held down are handled below)
		switch (m_Input->GetKeyPressed())
		{
			/*case SDLK_ESCAPE:
			{
			state_manager->ChangeState(State_Menu);
			} break;*/
		case SDL_SCANCODE_Q:
		{
			DebugMessage("Test Monster Move");
			std::vector<cEntityTest*>::iterator it;
			for (it = m_Monsters.begin(); it != m_Monsters.end(); it++)
			{
				m_AIManager.Think(*it, &m_Player);
			}
			break;
		}
		case SDL_SCANCODE_UP: {
			m_World[m_CurrentLevel].GetY() >= m_World[m_CurrentLevel].GetMapNorthBorder() + GAME_GRID ? m_World[m_CurrentLevel].SetY(-32) : DebugMessage("Cannot move north!");

			m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
			std::cout << "Player at " << m_Player.GetX() << " " << m_Player.GetY() << "\n";
			DebugMessage("************************");
			std::vector<cEntityTest*>::iterator it;
			for (it = m_Monsters.begin(); it != m_Monsters.end(); it++)
			{
				m_AIManager.Think(*it, &m_Player);
			}
			//std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_DOWN: {
			m_World[m_CurrentLevel].GetY() <= m_World[m_CurrentLevel].GetMapSouthBorder() - 32 ? m_World[m_CurrentLevel].SetY(32) : DebugMessage("Cannot move south!");
			m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
			std::cout << "Player at " << m_Player.GetX() << " " << m_Player.GetY() << "\n";
			DebugMessage("************************");
			std::vector<cEntityTest*>::iterator it;
			for (it = m_Monsters.begin(); it != m_Monsters.end(); it++)
			{
				m_AIManager.Think(*it, &m_Player);
			}
			//std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_LEFT: {
			m_World[m_CurrentLevel].GetX() >= m_World[m_CurrentLevel].GetMapWestBorder() + 32 ? m_World[m_CurrentLevel].SetX(-32) : DebugMessage("Cannot move west!");
			m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
			std::cout << "Player at " << m_Player.GetX() << " " << m_Player.GetY() << "\n";
			DebugMessage("************************");
			std::vector<cEntityTest*>::iterator it;
			for (it = m_Monsters.begin(); it != m_Monsters.end(); it++)
			{
				m_AIManager.Think(*it, &m_Player);
			}
			//std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_RIGHT: {
			m_World[m_CurrentLevel].GetX() <= m_World[m_CurrentLevel].GetMapEastBorder() - 32 ? m_World[m_CurrentLevel].SetX(32) : DebugMessage("Cannot move east!");
			m_Player.SetLocation(m_World[m_CurrentLevel].GetX(), m_World[m_CurrentLevel].GetY());
			std::cout << "Player at " << m_Player.GetX() << " " << m_Player.GetY() << "\n";
			DebugMessage("************************");
			std::vector<cEntityTest*>::iterator it;
			for (it = m_Monsters.begin(); it != m_Monsters.end(); it++)
			{
				m_AIManager.Think(*it, &m_Player);
			}
			//std::cout << m_World[m_CurrentLevel].GetX() << " " << m_World[m_CurrentLevel].GetY() << "\n";
		}break;
		case SDL_SCANCODE_A: {
			// Attack
			// Ask for direction
			
		}break;


		}
	}
}

void cGameState::SetBias(int xbias, int ybias)
{
	m_XBias = xbias;
	m_YBias = ybias;
}