#include "cEditorState.h"
#include "cStateManager.h"
#include "Math.h"
#include <iostream>
#include <fstream>

cEditorState::cEditorState(cGraphics* graphics, cInput* input) : 
				cState(graphics, input)	{
	m_Tilemap = m_Graphics->LoadTexture("Tileset.png",
										255, 255, 255);
	m_Cursor = m_Graphics->LoadTexture("cursor.png", 255, 255, 255);
	m_ButtonPic = m_Graphics->LoadTexture("GUIButton.png", 255, 255, 255);
	m_EntityPic = m_Graphics->LoadTexture("Entity.png", 0, 0, 0);
	m_TestPic = m_Graphics->LoadTexture("BasicButtonBackground.png", 255, 255, 255);
	m_Painter = cCursor(m_Graphics, m_Cursor, EDITOR_MOUSE_X_START,
						EDITOR_MOUSE_Y_START, 
						EDITOR_CURSOR_WIDTH, EDITOR_CURSOR_HEIGHT);
	m_Mode = Mode_Tile;

	// Load Buttons
	m_FileManager.LoadBasicButtonFromFile("newgui.ini",
		m_Graphics, m_TestPic, m_GUI);
	m_FileManager.LoadGeneralButton("gui.ini", m_Graphics, m_ButtonPic,
									"gui", m_GUI);
	//Test, Delete
	m_FileManager.LoadGeneralButton("guitexture.ini", m_Graphics, m_Tilemap,
									"tile", m_GUI);
	//m_GUI.m_BasicButton[0].m_Action = new cTestAction;
	// Test end
	m_FileManager.LoadPopMenu("gui.ini", m_Graphics, m_ButtonPic,
								m_GUI);
	m_FileManager.LoadEntityButton("entity.ini", m_Graphics, m_EntityPic,
									m_GUI);
	// Load database and test
	//m_Enemy.OpenDB("../Resource/enemy.db");
	//m_Enemy.GetIndex("IdIndexEnemy");
	//m_Enemy.GetValueByDoubleIndex("ID", "0Cleric", "HP", "Enemy");

	m_XBias = 0;
	m_YBias = 0;	// Initially there is no bias

	m_MapID.SetGraphics(m_Graphics);
	m_MapIDInput = false;

	m_PlayerStart.m_Graphics = m_Graphics;
	m_PlayerStart.Set(m_Painter.GetX(), m_Painter.GetY(), PLAYERSTART_FONT_SIZE);
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
}

cEditorState::~cEditorState()	{

}

bool cEditorState::Run(cStateManager* state_manager)	{
	static int last_tick = SDL_GetTicks();
  	int this_tick = SDL_GetTicks();


	//Test Database
	//int test = sqlite3_open("entity.db", &m_database);
	//if(test){
	//	cout << "Database connection failed";
	//	SDL_Delay(5000);
	//}

	////string table = "enemy";
	////string lookup = "HP";
	////string index = "*";
	////string syntax = "select "+index+" from "+table;
	//if(sqlite3_prepare_v2(m_database, "select * from IdIndexEnemy", 
	//	-1, &m_statement, 0) == SQLITE_OK)
	//{
	//	int cols = sqlite3_column_count(m_statement);
	//	int result = 0;
	//	string s;
	//	while(true)
	//	{
	//		result = sqlite3_step(m_statement);
	//		
	//		if(result == SQLITE_ROW)
	//		{
	//			//for(int col = 0; col < cols; col++)
	//			//{
	//			//	s = (char*)sqlite3_column_text(
	//			//		m_statement, col);
	//			//	//do something with it
	//			//	cout << s << "\n";
	//			//}
	//			s = (char*)sqlite3_column_text(m_statement, 0);
	//			m_tableid.push_back(s);
	//		}
	//		else
	//		{
	//			break;   
	//		}
	//	}
	//	sqlite3_finalize(m_statement);
	//}
	//sqlite3_close(m_database);

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

	//Clear the screen before every frame
	m_Graphics->ClearScreen();

	//m_TitleTest->Draw(255, 0, 0);

	m_MapID.Draw();

	BlinkTile();
	for (size_t i=0; i<(m_LevelManager.GetMap()).size(); i++)
	{
		(m_LevelManager.GetMap())[i].DrawBias(m_XBias, m_YBias - EDITOR_MOUSE_Y_START);
	}

	for (size_t i=0; i<(m_LevelManager.GetEntity()).size(); i++)
	{
		(m_LevelManager.GetEntity())[i].SetCurrentFrame();
		(m_LevelManager.GetEntity())[i].DrawBias(m_XBias, m_YBias);
	}

	m_GUI.Draw();

	m_PlayerStart.Update();
	m_PlayerStart.Draw();

	m_Painter.Draw();

	m_Graphics->Show();

	
	
	return m_IsRunning;
}

void cEditorState::HandleInput(cStateManager* state_manager)
{
	// Make sure a new event has happened and handle key presses 
	if (m_Input->GetEvent()) 
	{
		// Handle user manually closing game window 
		if ( m_Input->IsQuit() )
		{			
			m_IsRunning = false;

			return;  // game is over, exit the method
		}
		
		//Not sure if it works, testing
		if (m_Input->GetMouseMoved()) {
			m_GUI.IsOnFloat(m_Input->GetX(), m_Input->GetY());
		}
		// Handle keyboard input here (keys being held down are handled below)
		switch (m_Input->GetKeyPressed())
		{
			/*case SDLK_ESCAPE:
			{
				state_manager->ChangeState(State_Menu);			
			} break;*/

			case SDL_SCANCODE_BACKSPACE:	{
				if (m_MapID.m_EnableEditing == 1 && m_MapID.m_InputText.size() > 0)
					m_MapID.Delete();
			}break;

			case SDL_SCANCODE_P:
			{
				//std::cout << m_Painter.GetX() << " " << m_Painter.GetY() << "\n";
				m_PlayerStart.Set(m_Painter.GetX()+m_XBias, m_Painter.GetY()+m_YBias- EDITOR_MOUSE_Y_START, PLAYERSTART_FONT_SIZE);
				//m_PlayerStart.Dump();
			} break;

			case SDL_SCANCODE_LEFT:
			{
				if (m_Painter.CanMoveLeft()) m_Painter.MoveLeft();
			} break;

			case SDL_SCANCODE_RIGHT:
			{
				if (m_Painter.CanMoveRight()) m_Painter.MoveRight();
			} break;
			
			case SDL_SCANCODE_UP:
			{
				if (m_Painter.CanMoveUp()) m_Painter.MoveUp();
			} break;

			case SDL_SCANCODE_DOWN:
			{
				if (m_Painter.CanMoveDown()) m_Painter.MoveDown();
			} break;

			case SDL_SCANCODE_D:
			{
				//DumpMap();
			} break;

			// Delete tile
			case SDL_SCANCODE_DELETE:
			{
				if ((m_LevelManager.GetMap()).size() > 0)
				{
					m_LevelManager.SaveMapState();
					std::cout << "Old state saved " << (m_LevelManager.GetMap()).size() <<"\n";
				}
				m_LevelManager.RemoveTile(m_Painter.GetX(),
										m_Painter.GetY(), m_XBias, 
										m_YBias);
			} break;

			// Undo
			case SDL_SCANCODE_U:
			{
				m_LevelManager.Undo();
				
			} break;

			//case SDL_SCANCODE_S:
			//{
			//	m_FileManager.SaveMap("map1.txt",
			//					m_LevelManager.GetMap(),
			//					m_MapID.GetText());
			//	m_FileManager.SaveEntity("entity.sav",
			//					m_LevelManager.GetEntity());
			//} break;

			//case SDL_SCANCODE_L:
			//{
			//	//Load Map
			//	Load("map1.txt", "entity.sav");
			//} break;
		}

		// Handle Mouse input
		switch (m_Input->GetMousePressed())
		{
			case 1:		// Left Mouse Clisk
			{
				// We need to judge where does it click
				// Add codes for tiles and entities
				int x = m_Input->GetX();
				int y = m_Input->GetY();

				//	Test Code!!!!!!!!!!!!	//
				m_GUI.OnClick(m_MapID.GetText().c_str(), m_MapVector, 
					m_MapID.GetText().c_str(), m_PlayerStart.m_X, m_PlayerStart.m_Y);
				break;
				//	End of Test Code        //
				
				// Click on TextInput
				if (x <= 420 + m_MapID.GetWidth() && x >= 420)	{
					if (y <= m_MapID.GetWidth())	{
						DebugMessage("Text input");
						m_MapIDInput = !m_MapIDInput;
						if (m_MapIDInput == true)	{
							//SDL_StartTextInput();
							m_Input->SetCurrent(&m_MapID);
						}
						else	{
							SDL_StopTextInput();
							m_Input->SetCurrent(NULL);
						}
					}
				}

				// Click on Pop menu
				if (m_GUI.GetPopMenu().GetActivated() == 1)	{
					std::string temp = m_GUI.GetPopMenu().
						ReturnMenuID(m_Input->GetX(), m_Input->GetY());
					if	(temp == "PopDelete")	{
						DebugMessage("Delete");
						DeleteTile();
					}
					if	(temp == "PopSet") DebugMessage("Set");
					if	(temp == "PopReturn")	{
						DebugMessage("Return");
						m_GUI.GetPopMenu().ShutDown();
					}
				}

				// Click on tileset
				if (x < TILE_MENU_X_TOTAL	&& y <= TILE_MENU_Y_TOTAL)
				{
					m_LevelManager.SaveMapState();

					/* Paint the tile
			       Note that in reality tileset is 16*16
				   But we will display every tile as 32*32
				   So when we push, must divide GetNearestX
				   and GetNearestY by 2 as they divide 32!
				   But when draw (see draw() in cTile.cpp
				   We must draw as 32*32 */

					// Before push_back, delete duplicate
					m_LevelManager.RemoveTile(m_Painter.GetX(),
										m_Painter.GetY(), m_XBias, 
										m_YBias - EDITOR_MOUSE_Y_START);

					//RemoveTile();
					std::string id = GetTileIDByLocation();

					(m_LevelManager.GetMap()).push_back(cTile(m_Graphics, m_Tilemap,
								m_Painter.GetX()+m_XBias, m_Painter.GetY()+m_YBias- EDITOR_MOUSE_Y_START,
								GetNearestX()+m_GUI.GetTileXBias(), GetNearestY(),
								TILE_WIDTH, TILE_HEIGHT,1,
								0,0,1,0,id));	//m_XBias for screen coordinate
												//m_GUI.GetTileXBias() for src coordinate

					DebugMessage("One tile pushed");
				}
				
				// If click on Tile Scroll buttons
				if (x >= TILE_MENU_X_TOTAL	&& x < TILE_MENU_X_TOTAL+32 &&
					y <= TILE_MENU_Y_TOTAL)	{
					DebugMessage("You clicked on Tile Right Scroll");
					m_GUI.OnClickTileRightScroll();
				}
				if (x >= TILE_MENU_X_TOTAL+32	&& x < TILE_MENU_X_TOTAL+64 &&
					y <= TILE_MENU_Y_TOTAL)	{
					DebugMessage("You clicked on Tile Left Scroll");
					m_GUI.OnClickTileLeftScroll();
				}

				/* Click on entityset */
				DebugMessage("");
				//If clicked on entity
				if (x <= ENTITY_MENU_WIDTH * 
					(m_GUI.GetEntityButton()).size()
					&& y <= ENTITY_MENU_HEIGHT &&
					y > ENTITY_MENU_HEIGHT - 32)
				{
					m_LevelManager.SaveEntityState();
					
					//RemoveEntity();
					m_LevelManager.RemoveEntity(m_Painter.GetX(),
										m_Painter.GetY(), m_XBias, 
										m_YBias);
					std::string id = GetEntityIDByLocation();
					cEntity temp = m_GUI.GetEntityByID(id,
									m_Painter.GetX(), m_Painter.GetY());
					//This is wrong, need to push back cEntity(...)
					//The right way is to extract all information from temp
					//and use push_back(cEntity(...))
					(m_LevelManager.GetEntity()).push_back(cEntity(m_Graphics,
					m_EntityPic, temp.GetX(), temp.GetY(),
					temp.GetImageX(), temp.GetImageY(), 
					temp.GetWidth(), temp.GetHeight(),
					temp.GetID(), temp.GetHP(), temp.GetGold(),
					temp.GetExp(), temp.GetInteractive(), 
					0, temp.GetFrame()));

					DebugMessage((m_LevelManager.GetEntity()).size()+
									"");

					DebugMessage("One entity pushed");
				}

				// If clicks on Save Button
				if (x > m_GUI.GetBoundaryX() && x <= m_GUI.GetBoundaryX() + EDITOR_GUI_WIDTH)
				{
					DebugMessage("Saving...");
					if (y <= m_GUI.GetBoundaryY() + EDITOR_GUI_HEIGHT)	
						/*m_FileManager.SaveMap("map1.txt", 
											m_LevelManager.GetMap(),
											m_MapID.GetText());*/
						m_FileManager.SaveMap(m_MapID.GetText().c_str(),
							m_LevelManager.GetMap(),
							m_MapID.GetText(),
							m_PlayerStart.m_X, m_PlayerStart.m_Y);
						m_FileManager.SaveEntity("entity.sav",
								m_LevelManager.GetEntity());
				}
				//Click on Load
				if (x > m_GUI.GetBoundaryX() + EDITOR_GUI_WIDTH
					&& x <= m_GUI.GetBoundaryX() + 2 * EDITOR_GUI_WIDTH)
				{
					if (y <= m_GUI.GetBoundaryY() + EDITOR_GUI_HEIGHT)	
					{
						Load(m_MapID.GetText().c_str(), "entity.sav");	
					}
				}

				if (x > m_GUI.GetBoundaryX() + 2 * EDITOR_GUI_WIDTH
					&& x<= m_GUI.GetBoundaryX() + 3 * EDITOR_GUI_WIDTH)
				{
					if (y <= m_GUI.GetBoundaryY() + EDITOR_GUI_HEIGHT)
					{
						m_IsRunning = 0;	// Quit
					}
				}

				if (x > m_GUI.GetBoundaryX() + 3 * EDITOR_GUI_WIDTH
					&& x<= m_GUI.GetBoundaryX() + 4 * EDITOR_GUI_WIDTH)
				{
					if (m_XBias > EDITOR_BIAS_X_MIN)
					{
						m_XBias -= 32;	// Scroll to left
					}
				}

				if (x > m_GUI.GetBoundaryX() + 4 * EDITOR_GUI_WIDTH
					&& x<= m_GUI.GetBoundaryX() + 5 * EDITOR_GUI_WIDTH)
				{
					if (m_XBias < EDITOR_BIAS_X_MAX)
					{
						m_XBias += 32;	// Scroll to right
					}
				}
			}break;
			
			case 2:
			{
				//Middle Button Event
			}break;

			case 3:
			{
				//Right Button Event
				if (m_Input->GetX() < EDITOR_MOUSE_X_MAX &&
					m_Input->GetY() < EDITOR_MOUSE_Y_MAX &&
					m_Input->GetY() > EDITOR_MOUSE_Y_START)	{
					//Relocate the cursor
					m_Painter.SetX(GetNearestX());
					m_Painter.SetY(GetNearestY());
				
					m_GUI.GetPopMenu().DrawHide("entity", GetNearestX(),
						GetNearestY());
				}
			}break;
		}
	}

	// Handle keys being held down (find the code at cGameState)
}

int cEditorState::GetNearestX()	{
	if (m_Input->GetX() > 0)
	{
		if (m_Input->GetX() % 32 == 0)	return m_Input->GetX();
		return ((int) (m_Input->GetX() / 32)) * 32;
	}
	return 0;
}

int cEditorState::GetNearestY()	{
	if (m_Input->GetY() > 0)
	{
		if (m_Input->GetY() % 32 == 0)	return m_Input->GetY();
		return ((int) (m_Input->GetY() / 32)) * 32;
	}
	return 0;
}

void cEditorState::BlinkTile()	{
	// Check where the cursor is
	int x = m_Painter.GetX()+m_XBias;
	int y = m_Painter.GetY()+m_YBias;
	std::vector<cTile>::iterator it;

	if ((m_LevelManager.GetMap()).size()==0)	{
		return;
	}
	// Check which tile is under the cursor rightnow
	for (it = (m_LevelManager.GetMap()).begin();
			it != (m_LevelManager.GetMap()).end(); it ++)	{
		// If the cursor has left, unblink it
		if ((*it).IsBlink())	{
			if ((*it).GetX() != x || (*it).GetY() != y - EDITOR_MOUSE_Y_START)	{
				(*it).SetIsBlink(0);
			}
		}
		if ((*it).GetX() == x && (*it).GetY() == y - EDITOR_MOUSE_Y_START)	{
			if ((*it).IsBlink())	{
				return;
			}
			(*it).SetSpecial(1, EDITOR_BUTTON_BLINK, 
								EDITOR_BUTTON_BLINK, 0);
		}
	}
}

std::string cEditorState::GetEntityIDByLocation()	{
	int x = m_Painter.GetX();
	int y = m_Painter.GetY();
	//Now we compare those values against 
	//entities in m_GUIEntityVector
	std::vector<cEntity>::iterator it;
	for (it = (m_GUI.GetEntityButton()).begin();
			it!= (m_GUI.GetEntityButton()).end(); it++)	{
		if ((*it).GetX() == GetNearestX() && 
			(*it).GetY() == GetNearestY())	{
			DebugMessage("Found" + (*it).GetID());
			return (*it).GetID();
			break;
		}
	}
	return "N/A";
}

std::string cEditorState::GetTileIDByLocation()	{
	int x = m_Painter.GetX();
	int y = m_Painter.GetY();
	//Now we compare those values against 
	//entities in m_GUIEntityVector
	std::vector<cStaticButton>::iterator it;
	for (it = m_GUI.GetTileButton().begin(); it!= m_GUI.GetTileButton().end(); it++)	{
		if ((*it).m_X == GetNearestX() && 
			(*it).m_Y == GetNearestY())
		{
			return (*it).m_ID;
			break;
		}
	}
	return "N/A";
}

void cEditorState::Load(const char* mapfile, const char* entityfile)	{
	(m_LevelManager.GetMap()).clear();
	//Load Map
	m_FileManager.LoadMap(mapfile, m_Graphics, m_Tilemap,
						m_LevelManager);
	//Set Player Start for editor, actually just set painter
	m_Painter.SetX(m_LevelManager.GetX());
	m_PlayerStart.m_X = m_LevelManager.GetX();
	m_Painter.SetY(m_LevelManager.GetY());
	m_PlayerStart.m_Y = m_LevelManager.GetY();
	(m_LevelManager.GetEntity()).clear();
	
	m_FileManager.LoadEntityFromFile(entityfile, m_Graphics,
								m_EntityPic, m_LevelManager);
}

void cEditorState::DeleteTile()	{
	if ((m_LevelManager.GetMap()).size() > 0)
	{
		m_LevelManager.SaveMapState();
		std::cout << "Old state saved " << (m_LevelManager.GetMap()).size() <<"\n";
	}
	m_LevelManager.RemoveTile(m_Painter.GetX(), m_Painter.GetY(),
		m_XBias, m_YBias);
}