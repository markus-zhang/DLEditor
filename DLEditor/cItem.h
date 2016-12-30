#ifndef CITEM_H_
#define CITEM_H_

#include <string>
#include <vector>
#include "DebugTool.h"

struct cItemEffect {
	std::string m_Effect;
	int m_Value;
};


class cItem {
private:
	std::string m_Name;
	std::string m_Class;
	std::vector<cItemEffect> m_Effect;
	int m_HP;
public:
	std::string GetName() { return m_Name; }
	void SetName(std::string name) { m_Name = name; }
	std::string GetClass() { return m_Class; }
	void SetClass(std::string itemclass) { m_Class = itemclass; }
	void SetHP(int hp) { m_HP = hp; }
	std::vector<cItemEffect>& GetEffect() { return m_Effect; }
	void AddEffect(cItemEffect effect) { m_Effect.push_back(effect); }
	void ReduceEffect();

	void Dump();
};

#endif