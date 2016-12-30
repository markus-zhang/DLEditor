#ifndef CGUIBASICBUTTON_H_
#define CGUIBASICBUTTON_H_

// Header file for buttons on GUI
//#include <functional>
#include "cGraphics.h"
#include "Defines.h"
//#include "cFile.h"
#include "cEditorAction.h"

//cFile file;

class cGUIBasicButton
{
public:
	bool Load(cGraphics* graphics, SDL_Texture* bitmap,
		int x, int y,
		int img_x, int img_y, int width, int height,
		std::string id, std::string caption);

	int GetX() { return m_X; }
	int GetY() { return m_Y; }

	std::string GetID() { return m_ID; }
	std::string GetCaption()	{ return m_Caption; }
	
	void AlterRenderStatus() { m_RenderStatus = !m_RenderStatus; }
	void Draw(int xbias, int ybias);

	bool IsOnFloat(int mousex, int mousey);
	void OnFloat();
	void Reset();
	void OnClick();

private:
	std::string m_ID;
	//Graphics
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;
	bool m_RenderStatus;		//0 for normal, 1 for OnMouseFloat

	//Text
	std::string m_Caption;
	int m_TextRed, m_TextGreen, m_TextBlue;

	//Screen location 
	int m_X;
	int m_Y;

	//Clip location
	int m_ImageX;		//Use m_RenderStatus to modify
	int m_ImageY;		//This will be fixed
	int m_ImageXDefault;
	int m_ImageYDefault;

	//Dimensions
	int m_Width;
	int m_Height;
public:

	//Action
	//cAction* m_Action;
};
#endif