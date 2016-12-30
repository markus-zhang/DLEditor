#ifndef CENTITYFACTORY_H_
#define CENTITYFACTORY_H_

#include "cEntityTest.h"
#include <unordered_map>

class cEntityCreator
{
public:
	virtual cEntityTest* CreateEntity() const = 0;
	virtual ~cEntityCreator() {}
};

class cEntityFactory
{
private:
	std::unordered_map < std::string, cEntityCreator*> m_Creators;
public:
	bool RegisterCreator(std::string id, cEntityCreator* creator);
	cEntityTest* Create(std::string id);
};

class cEntityTestFactory
{
private:
	std::vector<cEntityTest*> m_Factory;
public:
	std::vector<cEntityTest*>& GetFactory()
	{
		return m_Factory;
	}

	bool RegisterEntity(cEntityTest* entity_test);
	cEntityTest* Create(std::string id);
};
#endif
