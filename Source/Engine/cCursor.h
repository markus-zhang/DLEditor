// Header file for the painter

#pragma once

#include "cGraphics.h"
#include "Defines.h"

class cCursor
{
public:
	cCursor(cGraphics* graphics, SDL_Texture* bitmap, 
			int x, int y, int width, int height);

	cCursor();

	void Draw();

	// Accessors/Mutators 
	int GetX() { return m_X; }
	int GetY() { return m_Y; }
	int GetWidth()  { return m_Width; }
	int GetHeight() { return m_Height; }
	void SetX(int x) { m_X = x; }
	void SetY(int y) { m_Y = y; }

	// Movement
	void MoveLeft()		{ m_X -= EDITOR_CURSOR_WIDTH; }
	void MoveRight()	{ m_X += EDITOR_CURSOR_WIDTH; }
	void MoveUp()		{ m_Y -= EDITOR_CURSOR_HEIGHT; }		
	void MoveDown()		{ m_Y += EDITOR_CURSOR_HEIGHT; }

	// Test if can move
	bool CanMoveLeft()	{ return m_X > 0; }
	bool CanMoveRight() { return m_X + EDITOR_CURSOR_WIDTH
							< EDITOR_MOUSE_X_MAX; }
	bool CanMoveUp()	{ return m_Y > 128; }
	bool CanMoveDown()	{ return m_Y + EDITOR_CURSOR_HEIGHT 
							< EDITOR_MOUSE_Y_MAX; }

private:
	cGraphics* m_Graphics;
	SDL_Texture* m_Bitmap;		// Container for the sprite

	// Screen location 
	int m_X;
	int m_Y;

	// Dimensions, set in defines.h
	int m_Width;
	int m_Height;
};