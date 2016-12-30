//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
//////////////////////////////////////////////////////////////////////////////////
#ifndef ENUMS_
#define ENUMS_

enum Direction
{
	/*Direction_Left,
	Direction_Right,
	Direction_Up,
	Direction_Down*/
	North, South, West, East
};

enum State
{
	//State_Game,  
	State_Menu,  
	State_Exit,  
	State_Win,   
	State_Lose, 
	State_Editor
};

enum EditorMode
{
	Mode_Tile,
	Mode_Object,
	Mode_Access
};

#endif