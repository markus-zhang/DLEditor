#include "cEffect.h"

cEffect::cEffect(std::string id)
{
	m_ID = id;
	m_LifeTimer.Reset();
}

void cEffect::Update()
{
	m_Life -= m_LifeTimer.GetMilliseconds();
	m_LifeTimer.Reset();
}

void cEffect::ApplyEffect()
{
	if (!m_Target)
	{
		DebugMessage("Effect Target cannot be found!");
		return;
	}
	if (m_ID == "00_MODHP")
	{
		if (m_Target)
		{
			if ((m_Target->GetAttributes()).m_HP > 0)
			{
				m_Target->GetAttributes().m_HP += m_Value;
			}
			else
			{
				DebugMessage("The target is already dead!");
			}
		}
	}

	if (m_ID == "01_POISON")
	{

	}
}

cTurnEffect::cTurnEffect()
{
	m_Owner = NULL;
	m_Target = NULL;
}

cTurnEffect::~cTurnEffect()
{
	m_Owner = m_Target = NULL;
}

void cTurnEffect::Update()
{
	m_Life -= 1;
}

void cTurnEffect::ApplyEffect()
{
	if (!m_Target)
	{
		DebugMessage("Effect Target cannot be found!");
		return;
	}
	if (m_ID == "00_MODHP")
	{
		DebugMessage("Physical damage");
		if (m_Target)
		{
			if ((m_Target->GetAttributes()).m_HP > 0)
			{
				m_Target->GetAttributes().m_HP += m_Value;
			}
			else
			{
				DebugMessage("The target is already dead!");
			}
		}
	}

	if (m_ID == "01_POISON")
	{

	}
}

cEffectFactory::cEffectFactory()
{

}

cEffectFactory::~cEffectFactory()
{
	m_EffectCreated.clear();
	m_EffectFactory.clear();
}

void cEffectFactory::Update()
{
	if (m_EffectCreated.empty())
	{
		//DebugMessage("Factory is empty yet");
		return;
	}
	
	std::vector<cTurnEffect>::iterator it;
	for (it = m_EffectCreated.begin(); it != m_EffectCreated.end();)
	{
		if ((*it).Expire())
		{
			m_EffectCreated.erase(it);
			if (m_EffectCreated.size() <= 0)
			{
				DebugMessage("No Effect");
				return;
			}
		}
		else
		{
			(*it).ApplyEffect();
			(*it).Update();
			++it;
		}
	}
}

void cEffectFactory::CreateEffect(std::string id, int life, int value, cEntityTest* owner, cEntityTest* target)
{
	// If there is no effect in the factory at all
	//DebugMessage("Creating effect");
	if (m_EffectFactory.size() <= 0)
	{
		//DebugMessage("Empty Factory");
		cTurnEffect new_effect;
		new_effect.SetID(id);
		new_effect.SetLife(life);
		new_effect.SetValue(value);
		if (owner && target)
		{
			new_effect.SetOwner(owner);
			new_effect.SetTarget(target);
		}
		m_EffectCreated.push_back(new_effect);
		//DebugMessage("Creating effect finished");
		return;
	}
	// First check if the effect has been registered
	std::vector<cTurnEffect>::iterator it;
	for (it = m_EffectFactory.begin(); it != m_EffectFactory.end(); it++)
	{
		if ((*it).GetID() == id)
		{
			cTurnEffect new_effect;
			new_effect.SetID(id);
			new_effect.SetLife(life);
			new_effect.SetValue(value);
			if (owner && target)
			{
				new_effect.SetOwner(owner);
				new_effect.SetTarget(target);
			}
			m_EffectCreated.push_back(new_effect);
		}
	}
	DebugMessage("Cannot create effect, something goes wrong!");
}
