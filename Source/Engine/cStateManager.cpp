#include "cStatemanager.h"
#include <iostream>

cStateManager::cStateManager(cGraphics* graphics, cInput* input)
{
	m_GameState = new cGameState(graphics, input);
	//m_MenuState = new cMainMenuState(graphics, input);
	//m_ExitState = new cExitState(graphics, input);
	//m_WinState  = new cWinState(graphics, input);
	//m_LoseState = new cGameOverState(graphics, input);
	m_EditorState = new cEditorState(graphics, input);

	// Start in the editor
	m_CurrentState = m_EditorState;
}

cStateManager::~cStateManager()
{
	//delete m_LoseState;
	//delete m_WinState;
	//delete m_ExitState;
	//delete m_MenuState;
	//delete m_GameState;
	delete m_EditorState;
	
	m_CurrentState = NULL;
}

cState* cStateManager::CurrentState()
{
	return m_CurrentState;
}

void cStateManager::ChangeState(State new_state)
{
	switch (new_state)
	{
		//case State_Game:
		//{
		//	m_CurrentState = m_GameState;
		//} break;
		/*case State_Menu:
		{
			m_CurrentState = m_MenuState;
		} break;
		case State_Exit:
		{
			m_CurrentState = m_ExitState;
		} break;
		case State_Win:
		{
			m_CurrentState = m_WinState;
		} break;
		case State_Lose:
		{
			m_CurrentState = m_LoseState;
		} break;*/
		case State_Editor:
		{
			m_CurrentState = m_EditorState;
		} break;
	}
}

// Aaron Cox, 2005