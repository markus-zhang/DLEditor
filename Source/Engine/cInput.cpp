#include "cInput.h"
#include <iostream>

using namespace std;

cInput::cInput(void)
{
	for (int i=0; i<323; i++)
	{
		m_KeysHeld[i] = false;
	}
	m_Current = NULL;
}

cInput::~cInput(void) {}

bool cInput::GetEvent()
{
	// Fill the event structure with event information //
	if (SDL_PollEvent(&m_Event))
	{
		// Tell m_KeysHeld that a key has been pressed //
		if (m_Event.type == SDL_KEYDOWN)
		{
			/*cout << m_Event.key.keysym.scancode;
			SDL_Delay(1000);*/
			m_KeysHeld[m_Event.key.keysym.scancode] = true;
		}
		// Tell m_KeysHeld that a key has been released //
		if (m_Event.type == SDL_KEYUP)
		{
			m_KeysHeld[m_Event.key.keysym.scancode] = false;
		}
		// Tell the engine that a button has been pressed //
		if (m_Event.type == SDL_MOUSEMOTION		|| 
			m_Event.type == SDL_MOUSEBUTTONDOWN	||
			m_Event.type == SDL_MOUSEBUTTONUP	)
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			SetX(x);
			SetY(y);
		}

		if (m_Event.type == SDL_TEXTINPUT)	{
			if (m_Current != NULL)	{
				AppendString(m_Current, m_Event.text.text);
			}
		}
		return true;
	}

	// No event has occured //
	return false;
}

void cInput::AppendString(cTextInput* textinput, std::string input)	{
	textinput->Append(input);
}

// Return true if user has manually closed the window //
bool cInput::IsQuit()
{
	if (m_Event.type == SDL_QUIT)
		return true;

	return false;
}

// If a key has been pressed, return its SDL key code. Return -1 if no key was pressed. //
int cInput::GetKeyPressed()
{
	if (m_Event.type == SDL_KEYDOWN)
	{
		return m_Event.key.keysym.scancode;
	}
	return -1;
}

int cInput::GetMousePressed()
{
	if (m_Event.type == SDL_MOUSEBUTTONDOWN && 
		m_Event.button.button == SDL_BUTTON_LEFT)
	{
		return 1;
	}
	
	if (m_Event.type == SDL_MOUSEBUTTONDOWN && 
		m_Event.button.button == SDL_BUTTON_RIGHT)
	{
		return 3;
	}

	if (m_Event.type == SDL_MOUSEBUTTONDOWN && 
		m_Event.button.button == SDL_BUTTON_MIDDLE)
	{
		return 2;
	}

}

bool cInput::GetMouseMoved() {
	if (m_Event.type == SDL_MOUSEMOTION)
		return true;
	return false;
}

// Return true if the given key is being held down //
bool cInput::KeyHeld(int key)
{
	return m_KeysHeld[key];
}

// Aaron Cox, 2005 
