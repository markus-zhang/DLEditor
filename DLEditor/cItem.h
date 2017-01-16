#ifndef CITEM_H_
#define CITEM_H_

#include <string>
#include <vector>
#include "DebugTool.h"
#include "cEffect.h"

enum EquipSlot
{
	WeaponSlot, ShieldSlot, LeftRingSlot, RightRingSlot,
	AmuletSlot, BootSlot, HelmSlot, CloakSlot
};

class cItem 
{
private:
	std::string m_Name;
	EquipSlot m_Slot;
	std::vector<cTurnEffect> m_Effect;
public:
	std::string GetName() { return m_Name; }
	void SetName(std::string name) { m_Name = name; }
	EquipSlot GetClass() { return m_Slot; }
	void SetSlot(EquipSlot slot) { m_Slot = slot; }

	std::vector<cTurnEffect>& GetEffect() { return m_Effect; }
	void AddEffect(cTurnEffect effect) { m_Effect.push_back(effect); }

	void Dump();
};

#endif