//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// Description: The interface for all game states. Note that this is only an
// interface and can't be instantiated. 
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Defines.h"
#include "cGraphics.h"
#include "cInput.h"
#include "cTimer.h"

// cState needs to know that cStateManager exists 
class cStateManager;

class cState
{
public:	
	cState(cGraphics* graphics,	cInput* input) : m_Graphics(graphics),
												 m_Input(input),
												 m_IsRunning(true)
	{}

	cState() {}

	// This is the method to call from the game loop. Run() takes a pointer
	// to the state manager so it can change states. Run() returns false
	// if the user chooses to quit the game.
	virtual bool Run(cStateManager* state_manager)=0;

	// All states must handle their own input. Since state changes
	// will most often be made through user input, HandleInput() also
	// needs access to the state manager.
	virtual void HandleInput(cStateManager* state_manager)=0;

protected:
	cGraphics* m_Graphics;
	cInput*    m_Input;

	bool m_IsRunning;  // each Run() method should return this value
	int  m_ID;		   // each state has unique ID for walking
};

// Aaron Cox, 2005