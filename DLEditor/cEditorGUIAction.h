#ifndef CEDITORGUIACTION_H_
#define CEDITORGUIACTION_H_

#include "cAction.h"
#include "cTile.h"
#include "cParser.h"
#include "cGUIBasicButton.h"
#include "cGUI.h"
#include <fstream>

class cLoadButtonAction : public cAction
{
public:
	void Init(const char* filename,
	cGraphics* graphics, SDL_Texture* bitmap,
	cGUI& gui);

	bool LoadButton(const char* filename,
	cGraphics* graphics, SDL_Texture* bitmap,
	cGUI& gui);

	virtual void Execute();		// Wrapper
private:
	const char* m_Filename;
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;
	cGUI& m_GUI;
	cParser m_Parser;
};

#endif

