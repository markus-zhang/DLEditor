#ifndef CENTITYTEST_H_
#define CENTITYTEST_H_

#include <unordered_map>
#include <queue>
#include <vector>
#include "cGraphics.h"
#include "cAnimation.h"

struct cPathNode
{
	int m_X;
	int m_Y;
};
struct cAttributes
{
	int m_HP;
	int m_AC;
	int m_DmgDice;
	int m_NumDmgDice;
	int m_Speed;
	int m_Exp;
	int m_Gold;
};
class cEntityTest
{
public:
	cEntityTest();
	~cEntityTest();

	int GetX() { return m_X; }
	int GetY() { return m_Y; }
	std::string GetID() { return m_ID; }
	cAttributes& GetAttributes() { return m_Attributes; }
	std::deque<cPathNode>& const GetPath()
	{
		return m_Path;
	}
	void SetPath(std::deque<cPathNode> path)
	{
		m_Path = path;
	}
	void ResetPath(int start, int end);
	void cEntityTest::DisplayPath()
	{
		if (m_Path.size() <= 0)
		{
			DebugMessage("Path is NULL!");
			return;
		}
		std::deque<cPathNode>::iterator it;
		for (it = m_Path.begin(); it != m_Path.end(); it++)
		{
			std::cout << (*it).m_X << "," << (*it).m_Y << " ";
		}
		std::cout << "First element is " << m_Path[0].m_X << ", " << m_Path[0].m_Y << "\n";
	}
	void Walk();

	void SetID(std::string id)
	{
		if (id.size() > 0)
		{
			m_ID = id;
		}
	}

	void SetAttributes(cAttributes attributes)
	{
		m_Attributes = attributes;
	}
	void SetLocation(int x, int y)
	{
		m_X = x;
		m_Y = y;
	}
	void RegisterAnimation(cAnimation ani)
	{
		m_Animation.push_back(ani);
	}
	void Update();
	void SetAnimation(std::string id);
	void PlayAnimation(std::string id);
	void PlayAnimationBiased(std::string id,
		int xbias, int ybias);
	void PlayAnimation();
	void Init();
	void Dump();
	void SetGraphics(cGraphics* graphics, SDL_Texture* texture)
	{
		std::vector<cAnimation>::iterator it;
		for (it = m_Animation.begin(); it != m_Animation.end(); it++)
		{
			(*it).SetGraphics(graphics, texture);
		}
	}
private:
	std::string m_ID;
	cAttributes m_Attributes;
	int m_X, m_Y;

	//Animation
	std::vector<cAnimation> m_Animation;
	std::string m_CurrentAnimation;
	std::unordered_map<std::string, cAnimation> m_AnimationMap;

	//AI
	std::deque<cPathNode> m_Path;	// Updated when see the player at a new place

};

#endif

