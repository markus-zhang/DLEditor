//////////////////////////////////////////////////////////////////////////////////
// Project: Dragonlance Ultima spin-off
// Description: The base class for all game entities.
//////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "cGraphics.h"
#include "Defines.h"
#include "cTimer.h"
#include <iostream>
#include "DebugTool.h"

class cEntity
{
public:
	//SDL 2.0 code
	cEntity(cGraphics* graphics, SDL_Texture* bitmap, int x, int y, 
		int img_x, int img_y, int width, int height,
		std::string id, int hp, int gold, int exp, bool interactive,
		int direction, int frame);
	
	cEntity() {}

	// This can be overloaded for animated entities
	virtual void Draw();
	virtual void DrawBias(int xbias, int ybias);
	
	// Return an SDL_Rect storing the cEntity's location and dimensions 
	SDL_Rect GetRect();

	// Accessors/Mutators 
	int GetX()				const	{ return m_X; }
	int GetY()				const	{ return m_Y; }
	int GetImageX()			const	{ return m_ImageX; }
	int GetImageY()			const	{ return m_ImageY; }
	int GetWidth()			const	{ return m_Width; }
	int GetHeight()			const	{ return m_Height; }
	std::string GetID()			const	{ return m_ID; }
	int GetHP()				const	{ return m_HP; }
	int GetGold()			const	{ return m_Gold; }
	int GetExp()			const	{ return m_Exp; }
	bool GetInteractive()	const	{ return m_Int; }
	int GetDirect()			const	{ return m_Direct; }
	int GetFrame()			const	{ return m_Frame; }

	void SetX(int x)				{ m_X = x; }
	void SetY(int y)				{ m_Y = y; }
	void SetImageX(int image_x)		{ m_ImageX = image_x;}
	void SetImageY(int image_y)		{ m_ImageY = image_y;}
	void SetWidth(int width)		{ m_Width = width;}
	void SetHeight(int height)		{ m_Height = height;}
	void SetID(std::string id)			{ m_ID = id;}
	void SetType(int type)			{ m_Type = type; }
	void SetHP(int hp)				{ m_HP = hp;}
	void SetGold(int gold)			{ m_Gold = gold;}
	void SetExp(int exp)			{ m_Exp = exp;}
	void SetInt(std::string inter)		
	{
		if (inter == "0")
		{
			m_Int = 0;
			return;
		}
		m_Int = 1;
	}
	void SetDir(int direction)		{ m_Direct = direction;}
	void SetFrame(int frame)		{ m_Frame = frame;}
	void SetGraph(cGraphics* graph)	{ m_Graphics = graph; }
	void SetPic(SDL_Texture* pic)	{ m_Bitmap = pic; }
	void InitialCurrentFrame()		{ m_CurrentFrame = 0; }
	void SetCurrentFrame();		// Modify Image_X and Image_Y
	void SetAniRate()				{ m_AnimationRate = ENTITY_ANIMATE_RATE; }
	
protected:
	// For drawing 
	cGraphics*   m_Graphics;

	//SDL 2.0 code
	SDL_Texture* m_Bitmap;
	int          m_ImageX;
	int          m_ImageY;

	// Screen location 
	int m_X;
	int m_Y;

	// Dimensions
	int m_Width;
	int m_Height;

	// Game
	std::string m_ID;			// Unique ID
	int m_Type;				// 0:Character 1:Interactive 2:Static
	int m_HP;				// 0 if it cannot be attacked
	int m_Gold;				// Gold dispensed when destroyed
	int m_Exp;				// Exp rewarded when destroyed
	bool m_Int;				// Is it interactive?
	int m_Direct;			// Direction (0E1S2W3N)
	int m_Frame;			// Number of Frames
	int m_CurrentFrame;
	int m_AnimationRate;	// How many ms for 1 frame
	cTimer m_AnimationTimer;
};

// Markus Zhang, 2016