#include "cEntityFactory.h"

bool cEntityFactory::RegisterCreator(std::string id, cEntityCreator* creator)
{
	std::unordered_map<std::string, cEntityCreator*>::iterator it;
	it = m_Creators.find(id);

	if (it == m_Creators.end())
	{
		// No existing copy found, Please register
		m_Creators[id] = creator;
		return true;
	}
	else
	{
		// Existing copy found
		delete creator;
		return false;
	}
}

cEntityTest* cEntityFactory::Create(std::string id)
{
	std::unordered_map<std::string, cEntityCreator*>::iterator it;
	it = m_Creators.find(id);
	
	if (it == m_Creators.end())
	{
		// Existing not found, could be wrong
		DebugMessage("No existing " + id + " found!");
		return NULL;
	}
	else
	{
		return m_Creators[id]->CreateEntity();
	}
}

bool cEntityTestFactory::RegisterEntity(cEntityTest* entity_test)
{
	std::string id;
	id = entity_test->GetID();

	if (id.size() <= 0)
	{
		return false;
	}

	std::vector<cEntityTest*>::iterator it;
	for (it = m_Factory.begin(); it != m_Factory.end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			// Existing found
			DebugMessage(id + " has already been registered!");
			return false;
		}
	}

	m_Factory.push_back(entity_test);
	DebugMessage(id + " is being registered!");
	return true;
}

cEntityTest* cEntityTestFactory::Create(std::string id)
{
	if (id.size() <= 0)
	{
		DebugMessage("NULL or Wrong id!");
		return NULL;
	}
	std::vector<cEntityTest*>::iterator it;
	for (it = m_Factory.begin(); it != m_Factory.end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			// Existing found
			DebugMessage(id + " is being created!");
			return (*it);
		}
	}
	DebugMessage(id + " has not been registered yet!");
	return NULL;
}