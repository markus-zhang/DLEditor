#include "cAnimationManager.h"

cAnimationManager::cAnimationManager()
{
	m_AnimationNum = 0;
}

cAnimationManager::~cAnimationManager()
{

}

void cAnimationManager::Register(cAnimation& animation)
{
	m_AniManager.emplace(animation.GetID(), animation);
}

void cAnimationManager::SetAnimation(std::string id)
{
	m_CurrentAnimation = id;
}

void cAnimationManager::Render(int x, int y)
{
	std::unordered_map<std::string, cAnimation>::iterator it;
	it = m_AniManager.find(m_CurrentAnimation);
	if (it != m_AniManager.end())
	{
		m_AniManager[m_CurrentAnimation].Render(x, y);
	}
}