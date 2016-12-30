#include "cAnimation.h"

cAnimation::cAnimation()
{
	//test
	//m_Life = 5000;
}
cAnimation::~cAnimation() {}

void cAnimation::Init(std::string id, int numFrame,
	int x, int y, int width, int height,
	int deltaTime, int life)
{
	m_ID = id;
	m_NumFrame = numFrame;
	m_DimFrame.Set(x, y, width, height);
	m_DeltaTime = deltaTime;
	m_Life = life;

	m_AnimationTimer.Reset();
	m_LifeTimer.Reset();
}

void cAnimation::SetGraphics(cGraphics* graphics,
	SDL_Texture* texture)
{
	m_Graphics = graphics;
	m_Texture = texture;
}

void cAnimation::Update()
{
	//First check life
	if (m_Life < -1 && m_Life > -255)
	{
		//No need to do anything about this guy
		DebugMessage("No need to update");
		return;
	}
	else
	{
		if (m_Life > -255)
		{
			m_Life -= m_LifeTimer.GetMilliseconds();
			m_LifeTimer.Reset();
		}
	}
	//Next check frame
	if (m_AnimationTimer.GetMilliseconds() >= m_DeltaTime)
	{
		//Need to move to next/first frame
		if (m_CurrentFrame >= m_NumFrame - 1)
		{
			m_CurrentFrame = 0;
		}
		else
		{
			m_CurrentFrame += 1;
		}
		m_AnimationTimer.Reset();
	}
}

void cAnimation::Render(int x, int y)
{
	if (m_Texture == NULL)
	{
		DebugMessage("NULL ANIMATION TEXTURE");
		SDL_Delay(5000);
	}
	Update();
	if (m_Life >= -1 || m_Life == -255)
	{
		//Modify m_DimFrame before rendering
		m_DimFrame.m_X = m_CurrentFrame * m_DimFrame.m_Width;
		//std::cout << m_Life << "\n";
		m_Graphics->RenderTexture(m_Texture, x, y, m_DimFrame);
	}
}

//#include "cAnimation.h"
//
//cAnimation::cAnimation(std::string id, int numFrame,
//	int x, int y, int width, int height,
//	int deltaTime, int life)
//{
//	m_ID = id;
//	m_NumFrame = numFrame;
//	m_DimFrame.Set(x, y, width, height);
//	m_DeltaTime = deltaTime;
//	m_Life = life;
//
//	m_AnimationTimer.Reset();
//	m_LifeTimer.Reset();
//}
//
//cAnimation::~cAnimation() {}
//
//void cAnimation::Update()
//{
//	//First check life
//	m_Life -= m_LifeTimer.GetMilliseconds();
//	if (m_Life < -1)
//	{
//		//No need to do anything about this guy
//		return;
//	}
//	//Next check frame
//	if (m_AnimationTimer.GetMilliseconds() >= m_DeltaTime)
//	{
//		//Need to move to next/first frame
//		if (m_CurrentFrame >= m_NumFrame - 1)
//		{
//			m_CurrentFrame = 1;
//		}
//		else
//		{
//			m_CurrentFrame += 1;
//		}
//		m_AnimationTimer.Reset();
//	}
//}
//
//void cAnimation::Render(int x, int y)
//{
//	if (m_Life >= -1)
//	{
//		//Modify m_DimFrame before rendering
//		m_DimFrame.m_X = m_CurrentFrame * m_DimFrame.m_Width;
//		m_Graphics->RenderTexture(m_Texture, x, y, m_DimFrame);
//	}
//}