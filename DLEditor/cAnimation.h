/*
We assume that each frame in the animation has the same 
dimension, and we only need to know the x and y of the
first frame to deduce the coordinates of other frames,
i.e. they share same y but different x (in the same row)
*/

#ifndef CANIMATION_H_
#define CANIMATION_H_

//#include "cGraphics.h"
//#include "cTimer.h"
//
//class cAnimation {
//public:
//	cAnimation(std::string id, int numFrame,
//		int x, int y, int width, int height,
//		int deltaTime, int life);
//	~cAnimation();
//
//	std::string GetID() { return m_ID; }
//
//	//Update() will check if we need to change m_CurrentFrame
//	//It will also check if we need to remove it
//	void Update();
//	void Render(int x, int y);	// Parameter from owner
//private:
//	cGraphics* m_Graphics;
//	SDL_Texture* m_Texture;
//
//	std::string m_ID;	// e.g. "IDLE", "PAIN"
//	int m_NumFrame;		// number of frames of animation
//	int m_CurrentFrame;	// current frame (starts from 0)
//	cDim m_DimFrame;	// x, y and dimension of 1st frame
//	int m_DeltaTime;	// how many miliseconds between two frams
//	cTimer m_AnimationTimer, m_LifeTimer;
//	int m_Life;			// how many miliseconds to show
//};

#include "cGraphics.h"
#include "cTimer.h"
#include "DebugTool.h"

class cAnimation {
public:
	cAnimation();
	~cAnimation();

	void Init(std::string id, int numFrame,
		int x, int y, int width, int height,
		int deltaTime, int life);

	std::string GetID() { return m_ID; }

	void SetID(std::string id) { m_ID = id; }
	void SetX(int x) { m_DimFrame.m_X = x; }
	void SetY(int y) { m_DimFrame.m_Y = y; }
	void SetW(int w) { m_DimFrame.m_Width = w; }
	void SetH(int h) { m_DimFrame.m_Height = h; }
	void SetNum(int num) { m_NumFrame = num; }
	void SetDelta(int delta) { m_DeltaTime = delta; }
	void SetLife(int life) { m_Life = life; }
	void SetGraphics(cGraphics* graphics,
		SDL_Texture* texture);

	//Update() will check if we need to change m_CurrentFrame
	//It will also check if we need to remove it
	void Update();
	void Render(int x, int y);	// Parameter from owner
	void Dump()
	{
		std::cout << m_ID << " " << m_NumFrame << " " << m_DeltaTime << " " << m_Life << "\n";
	}
private:
	cGraphics* m_Graphics;
	SDL_Texture* m_Texture;

	std::string m_ID;	// e.g. "IDLE", "PAIN"
	int m_NumFrame;		// number of frames of animation
	int m_CurrentFrame;	// current frame (starts from 0)
	cDim m_DimFrame;	// x, y and dimension of 1st frame
	int m_DeltaTime;	// how many miliseconds between two frams
	cTimer m_AnimationTimer, m_LifeTimer;
	int m_Life;			// how many miliseconds to show
};


#endif
