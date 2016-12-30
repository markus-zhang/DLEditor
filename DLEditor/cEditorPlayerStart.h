#ifndef CEDITORPLAYERSTART_H_
#define CEDITORPLAYERSTART_H_

#include <string>
#include "cGraphics.h"

struct cEditorPlayerStart
{
	int m_X;
	int m_Y;
	std::string m_Text;
	int m_FontSize;
	cGraphics* m_Graphics;

	void Set(int x, int y, int size)
	{
		if (x >= 0 && y >= 0 && size > 0)
		{
			m_X = x;
			m_Y = y;
			m_FontSize = size;
		}
	}

	void Update()
	{
		m_Text = "Player location: " + std::to_string(m_X) + " " + std::to_string(m_Y);
		//DebugMessage(m_Text);
	}

	void Draw() {
		m_Graphics->RenderText(m_Text, m_FontSize, 0,0,0, PLAYERSTART_X, PLAYERSTART_Y);
	}

	void Dump()
	{
		std::cout << m_X << " " << m_Y << "\n";
	}
};

#endif
