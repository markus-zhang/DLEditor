//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// Description: The state manager contains objects for each of the game states.
// To change states, call the ChangeState(), using one of the State enumerations
// as the paramter.
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cEditorState.h"
#include "cGameState.h"

class cStateManager
{
public:
	cStateManager(cGraphics* graphics, cInput* input);
	cStateManager() {}
	~cStateManager();

	// Return a pointer to the current state object
	cState* CurrentState();

	void ChangeState(State new_state);

private:

	cEditorState*	m_EditorState;
	cGameState*	m_GameState;

	cState* m_CurrentState;
};

// Aaron Cox, 2005
