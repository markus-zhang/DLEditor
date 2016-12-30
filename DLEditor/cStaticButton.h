#ifndef CSTATICBUTTON_
#define CSTATICBUTTON_

// Header file for buttons on GUI
#include "cGraphics.h"
#include "Defines.h"

class cStaticButton
{
public:
	cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y,
				int img_x, int img_y, int width, int height);

	cStaticButton(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y,
				int img_x, int img_y, int width, int height,
				std::string id);
	
	cStaticButton() {}
	int GetX()			{ return m_X; }
	int GetY()			{ return m_Y; }
	std::string GetID()	{ return m_ID; }
	void Draw();
	void DrawBias(int xbias);
	void DrawModulate(Uint8 red, Uint8 green, Uint8 blue,
						int xbias);
	bool OnClick(int x, int y);

//private:
	std::string m_ID;
	//Graphics
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;

	//Screen location 
	int m_X;
	int m_Y;

	//Clip location
	int m_ImageX;
	int m_ImageY;

	//Dimensions
	int m_Width;
	int m_Height;
};
#endif