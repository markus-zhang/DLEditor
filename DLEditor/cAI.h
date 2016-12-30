// The AI interface; Different AIs; AI Manager

#ifndef CAI_H_
#define CAT_H_

#include "cEntityFactory.h"
#include "cTile.h"
#include "cEffect.h"
#include "Enums.h"

class cAIState
{
public:
	virtual void Think() = 0;
	int CanMove(std::vector<cTile> map, int x, int y);
protected:
	cEntityTest* m_Player;
};

// Idle State, monsters move around randomly
class cIdleAIState : public cAIState
{
public:
	void Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player);
	void Think();
	void Update(cEntityTest* owner, std::vector<cTile>& map);
private:
	std::vector<cTile> m_Map;
	cEntityTest* m_Owner;
	
};

// Move State
//enum Direction	{North, South, West, East};
class cMoveAIState : public cAIState
{
public:
	cMoveAIState()
	{
		m_OwnerTraverse.m_X = 0;
		m_OwnerTraverse.m_Y = 0;
	}
	void Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player);
	void ThinkOld();
	void Think();
	void CalculatePath();	// Only called when player appears at a new place
	void RemoveBlock();		// Remove blockers from open_list
	bool RemoveDuplicateBlock(const cPathNode& test);
	cPathNode FindOptimal();// Find the optimal tile in open_list
	void DisplayPath();		// For debug
	void Update();
	void MoveCloser();
private:
	std::vector<cTile> m_Map;
	cEntityTest* m_Owner;
	//cEntityTest* m_Player;
	int m_Direction;
	cPathNode m_OwnerTraverse;
	std::deque<cPathNode> open_list;
	std::deque<cPathNode> close_list;
	std::deque<cPathNode> block_list;
};

// Attack State
class cAttackAIState : public cAIState
{
public:
	void Think();
	void Init(cEntityTest* owner, cEntityTest* player, cEffectFactory* factory);
	void Update(cEntityTest* owner, cEntityTest* target, cEffectFactory* effect_factory);
private:
	cEntityTest* m_Owner;
	cEntityTest* m_Player;
	cEffectFactory* m_Effect;
};

class cAIManager
{
public:
	cAIManager();
	~cAIManager();
	void Init(cEffectFactory* factory);

	void Think(cEntityTest* owner, cEntityTest* player);
	int CloseEnough(cEntityTest* owner, cEntityTest* player);
	bool CanMove(cEntityTest* owner, std::vector<cTile> map) const;
	//bool CanSeePlayer(cEntityTest* owner, cEntityTest* player);
	bool LOS(cEntityTest* owner, cEntityTest* player);
	void SetCurrentAI(cEntityTest* owner);
	void SetMap(const std::vector<cTile>& map)
	{
		m_Map = map;
	}
	//int CountVertices(int start_x, int start_y, int end_x, int end_y,
		//int tile_x, int tile_y, bool larger);

	bool LineInRectangle(int start_x, int start_y,
		int end_x, int end_y, int tile_x, int tile_y);

private:
	std::vector<cTile> m_Map;

	cIdleAIState* m_IdleAI;
	cMoveAIState* m_MoveAI;
	cAttackAIState* m_AttackAI;

	cAIState* m_CurrentAI;
	cEffectFactory* m_Effect;
};

#endif
