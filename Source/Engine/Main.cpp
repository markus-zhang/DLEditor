//////////////////////////////////////////////////////////////////////////////////
// Project: SDL Game Engine
// Description: This is the entry point for any game using the SDL Game Engine
//////////////////////////////////////////////////////////////////////////////////

#include "Defines.h"
#include "cGraphics.h"
#include "cInput.h"
#include "cStateManager.h"
#include <iostream>
//#include "cBoard.h"

//bool queen(int column, cBoard& game);
//cBoard m_EightQueen;

// Note that the parameters and return type here are required by SDL, 
// even though you'll probably never use them. 
int main(int argc, char **argv)
{
	cGraphics* graphics = new cGraphics(EDITOR_WIDTH, EDITOR_HEIGHT,
		EDITOR_TITLE); 
	cInput* input = new cInput();
	cStateManager* stateManager =new cStateManager(graphics, input);

	//if (queen(0, m_EightQueen))	m_EightQueen.Draw();

	while ( stateManager->CurrentState()->Run(stateManager) ) {}

	delete input;
	delete graphics;

	return 0;
}

//bool queen(int column, cBoard& game)	{
//	std::cout << "Column is now" << column << std::endl;
//	if (column > 7)	{
//		std::cout << "Complete!" << std::endl;
//		return true;
//	}
//	int row;
//	row = 0;
//	while (row < 8)	{
//		//std::cout << "Column: " << column << " Row: " << row << std::endl;
//		if (m_EightQueen.PlaceQueen(row, column))	{
//			std::cout << "Next column" << std::endl;
//			column ++;
//			if (!queen(column, game))	{
//				std::cout << "Must move back!" << std::endl;
//				column --;
//				row ++;
//				std::cout << "Column is " << column << std::endl;
//				std::cout << "Row is " << row << std::endl;
//			}
//			else	return true;
//		}
//		else	row ++;
//		if (row >= 4)	m_EightQueen.RemoveDuplicate(0, column);
//	}
//	return false;
//}