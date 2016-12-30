/*
cSDL2BaseEntity class:
This is the base class for many other classes that we
are going to put on screen (effects, player, monsters,
static items, gui components, etc.)
*/

#ifndef CSDL2GAMEOBJECT_H_
#define CSDL2GAMEOBJECT_H_

#include "../Source/Engine/cGraphics.h"
#include "../Source/Engine/cTimer.h"

class cSDL2GameObject {
public:
	cSDL2GameObject();
	~cSDL2GameObject();

	void virtual Init(cGraphics* graphics, SDL_Texture* texture,
		int x, int y, int w, int h, int life) = 0;

	void virtual Update() = 0;
	void virtual Render() = 0;
protected:
	std::string m_ID, m_Name;
	cGraphics* m_Graphics;
	SDL_Texture* m_Texture;

	cDim m_Dimension;

	int m_Life;		// -1 is permanant
	cTimer m_Timer;
};

#endif
