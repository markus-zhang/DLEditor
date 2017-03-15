#include "cResManager.h"

cResManager::cResManager()
{}

cResManager::~cResManager()
{}

bool cResManager::IsEmpty()
{
	return m_Res.empty();
}

void cResManager::Clear()
{
	m_Res.clear();
}

void cResManager::AddRes(std::pair<std::string, SDL_Texture*> res)
{
	m_Res.insert(res);
}

void cResManager::RemoveRes(std::string resid)
{
	m_Res.erase(resid);
}