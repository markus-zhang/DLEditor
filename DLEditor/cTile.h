//Tile class
#include <string>
#include <vector>
#include <iostream>

#pragma once

#include "cGraphics.h"
#include "Defines.h"

class cTile
{
public:
	//x and y are position, img_x and img_y are clipper coordinates
	//width and height are of the clipped texture
	cTile();
	cTile(cGraphics* graphics, SDL_Texture* texture, int x, int y, 
		int img_x, int img_y, int width, int height, bool access,
		bool tempdisplay, int healthholder, int health, int blink,
		std::string id);
	~cTile();

	void Draw();
	void GameDraw(int x, int y);
	void DrawBias(int xbias, int ybias);

	SDL_Rect GetRect();

	// Accessors/Mutators 
	std::string GetID() const			{ return m_ID; }
	int GetX() const				{ return m_X; }
	int GetY() const				{ return m_Y; }
	int GetImageX() const			{ return m_ImageX; }
	int GetImageY() const			{ return m_ImageY; }
	int GetWidth()  const			{ return m_Width; }
	int GetHeight() const			{ return m_Height; }
	int GetAccess() const			{ return m_Access; }
	bool GetIsExit() const			{ return m_IsExit; }
	void SetGraph(cGraphics* graph)	{ m_Graphics = graph; }
	void SetPic(SDL_Texture* bitmap){ m_Bitmap = bitmap; }
	void SetX(int x)				{ m_X = x; }
	void SetY(int y)				{ m_Y = y; }
	void SetImageX(int x)			{ m_ImageX = x; }
	void SetImageY(int y)			{ m_ImageY = y; }
	void SetWidth(int width)		{ m_Width = width; }
	void SetHeight(int height)		{ m_Height = height; }
	void SetID(std::string id)			{ m_ID = id; }
	void SetAccess(int access)		{ m_Access = access; }
	void SetIsExit()				{ m_IsExit = 1; }

	void SetIsBlink(bool temp)		{ m_Blink = temp; }
	void SetHealth(int health)		{ m_Health = health; }
	void SetTrigger(bool trigger)	{ m_Trigger = trigger; }
	void SetSpecial(bool blink, int healthholder,
					int health, bool trigger);
	bool IsMe(int x, int y);
	bool IsBlink();

private:
	//WE NEED TO MOVE ALL THE SHARED DATA TO
	//A SEPERATE CLASS and PUT A POINTER TO
	//THAT CLASS HERE

	//Graphics
	cGraphics* m_Graphics;	
	SDL_Texture* m_Bitmap;	

	std::string m_ID;

	//Clip location
	int          m_ImageX;	//SHARED BY A LOT OF INSTANCES
	int          m_ImageY;	//SHARED BY A LOT OF INSTANCES

	//Screen location 
	int			m_X;
	int			m_Y;

	//Dimensions
	int			m_Width;	//SHARED BY A LOT OF INSTANCES
	int			m_Height;	//SHARED BY A LOT OF INSTANCES

	//Accessibility
	int		m_Access;		//SHARED BY A LOT OF INSTANCES

	//For Blinking
	bool		m_Blink;		// Blink or not?
	int			m_HealthHolder;	// Indicate the health value
	int			m_Health;		// How many cycles until death
	bool		m_Trigger;		// 0 for show, 1 for disappear

	//For level transition
	bool		m_IsExit;		// Is this tile an exit?
	std::string m_ExitID;		// ID of the next map	
	int         m_TargetX;		// Location of player after transition
	int         m_TargetY;		
};

//class cTileFile
//{
//public:
//	cTileFile();
//	cTileFile(int x, int y,	int img_x, int img_y, 
//			int width, int height, bool access);
//	~cTileFile();
//	void dump();			//For Debug
//
//	//Accessor
//	int GetX() { return m_X; }
//	int GetY() { return m_Y; }
//
//	//Clip location
//	int          m_ImageX;
//	int          m_ImageY;
//
//	//Screen location 
//	int m_X;
//	int m_Y;
//
//	//Dimensions
//	int m_Width;
//	int m_Height;
//
//	//Accessibility
//	bool m_Access;
//};