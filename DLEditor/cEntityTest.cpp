#include "cEntityTest.h"

cEntityTest::cEntityTest()
{
}
cEntityTest::~cEntityTest() {}

void cEntityTest::Init() 
{
	m_CurrentAnimation = "IDLE";
}

void cEntityTest::Update()
{
	std::vector<cAnimation>::iterator it;
	for (it = m_Animation.begin(); it != m_Animation.end(); it++)
	{
		if ((*it).GetID() == m_CurrentAnimation)
		{
			(*it).Update();
			break;
		}
	}
}

void cEntityTest::SetAnimation(std::string id)
{
	// unordered_map version
	std::unordered_map <std::string, cAnimation> ::iterator it_m;
	it_m = m_AnimationMap.find(id);
	if (it_m == m_AnimationMap.end())
	{
		DebugMessage("Animation id NOT loaded or does NOT exist!");
		return;
	}
	else
	{
		m_CurrentAnimation = id;
	}

	// vector version
	std::vector<cAnimation>::iterator it_v;
	for (it_v = m_Animation.begin(); it_v != m_Animation.end(); it_v ++)
	{
		if ((*it_v).GetID() == id)
		{
			m_CurrentAnimation = id;
		}
		else
		{
			DebugMessage("Animation id NOT loaded or does NOT exist!");
		}
	}
	return;
}

void cEntityTest::PlayAnimation(std::string id)
{
	std::vector<cAnimation>::iterator it;
	for (it = m_Animation.begin(); it != m_Animation.end(); it++)
	{
		if ((*it).GetID() == id)
		{
			m_CurrentAnimation = id;
			(*it).Render(m_X, m_Y);
		}
	}
}

void cEntityTest::PlayAnimationBiased(std::string id, int xbias, int ybias)
{
	std::vector<cAnimation>::iterator it;
	for (it = m_Animation.begin(); it != m_Animation.end(); it++)
	{
		if ((*it).GetID() == id)
		{
			(*it).Render(m_X - xbias, m_Y - ybias);
		}
	}
}

void cEntityTest::PlayAnimation()
{
	std::vector<cAnimation>::iterator it;
	for (it = m_Animation.begin(); it != m_Animation.end(); it++)
	{
		if ((*it).GetID() == m_CurrentAnimation)
		{
			(*it).Render(m_X, m_Y);
		}
	}
}

void cEntityTest::Dump()
{
	//std::cout << m_Animation.size() << "\n";
	std::vector<cAnimation>::iterator it;
	for (it = m_Animation.begin(); it != m_Animation.end(); it++)
	{
		(*it).Dump();
	}
}

void cEntityTest::ResetPath(int start, int end)
{
	// Checking for error
	if (m_Path.size() <= 0)
	{
		DebugMessage("m_Path is NULL!");
		return;
	}
	// Copy the content to a new std::deque
	std::deque<cPathNode> temp;
	for (size_t i = start; i <= end; i++)
	{
		temp[i - start] = m_Path[i];
	}
	// Copy temp to m_Path
	m_Path.clear();
	m_Path = temp;
}

void cEntityTest::Walk()
{
	// Check for errors
	if (m_Path.size() <= 1)
	{
		DebugMessage("m_Path is NULL or should call AIAttack!");
		return;
	}
	// Move to the next pathnode
	std::cout << "Next location: " << m_Path[1].m_X << ", " << m_Path[1].m_Y;
	SetLocation(m_Path[1].m_X, m_Path[1].m_Y);
}