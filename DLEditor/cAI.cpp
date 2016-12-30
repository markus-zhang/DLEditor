#include "cAI.h"
#include <random>
#include <stdlib.h>
#include <algorithm>

int cAIState::CanMove(std::vector<cTile> map, int x, int y)
{
	if (m_Player->GetX() == x && m_Player->GetY() == y)
	{
		DebugMessage("Cannot collide with player");
		return 0;
	}
	//DebugMessage("CanMove()");
	std::vector<cTile>::iterator it;
	for (it = map.begin(); it != map.end(); it ++)
	{
		if ((*it).GetX() == x && (*it).GetY() == y)
		{
			return (*it).GetAccess();
		}
	}
	DebugMessage("Cannot move");
	return 0;
}

void cIdleAIState::Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player)
{
	if (map.size() <= 0 || !owner || !player)
	{
		DebugMessage("cIdleAIState: Error Init() NULL object");
		return;
	}
	m_Map = map;
	m_Owner = owner;
	m_Player = player;
}

void cIdleAIState::Think()
{
	Update(m_Owner, m_Map);
}

void cIdleAIState::Update(cEntityTest* owner, std::vector<cTile>& map)
{
	DebugMessage("I'm idle");
	// Generate random interger from 1-4
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(1, 5);
	auto direction = uni(rng);

	//std::cout << "Direction is " << direction << "\n";
	//direction = 5;	// Testing
	switch (direction)
	{
	case 1:	// North
	{
		int x_new = owner->GetX();
		int y_new = owner->GetY() - 32;
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}
	case 2:	// South
	{
		int x_new = owner->GetX();
		int y_new = owner->GetY() + 32;
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}	
	case 3:	// East
	{
		int x_new = owner->GetX() + 32;
		int y_new = owner->GetY();
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}	
	case 4:	// West
	{
		int x_new = owner->GetX() - 32;
		int y_new = owner->GetY();
		
		if (CanMove(map, x_new, y_new) > 0)
		{
			owner->SetLocation(x_new, y_new);
		}
		break;
	}
	case 5:	// Idle
	{
		break;
	}
	}
}

void cMoveAIState::Init(std::vector<cTile> map, cEntityTest* owner, cEntityTest* player)
{
	if (map.size() <= 0 || !owner || !player)
	{
		DebugMessage("cMoveAIState: Error Init() NULL object");
		return;
	}
	m_Map = map;
	m_Owner = owner;
	m_Player = player;
}

void cMoveAIState::ThinkOld()
{
	std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
	// Init() auto called by AIManager, calculate direction
	// And then call Update()
	// 1. Check if on same row/column
	if (m_Owner->GetX() == m_Player->GetX())
	{
		// Same column monster is north
		DebugMessage("Monster is due north of Player");
		if (m_Owner->GetY() < m_Player->GetY())
		{
			if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() + GAME_GRID))
			{
				m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() + GAME_GRID);
				return;
			}
			else
			{
				// Check the closet open node in South and move to it
				//             M
				// *****   ***************** *
				//             P
				// M will move to the opening to the left
				std::vector<cTile>::iterator it;
				int distance_x = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetY() == m_Owner->GetY() + GAME_GRID)
					{
						if (abs((*it).GetX() - m_Owner->GetX()) <= distance_x)
						{
							distance_x = abs((*it).GetX() - m_Owner->GetX());
							// Set direction
							(*it).GetX() >= m_Owner->GetX() ? m_Direction = East : m_Direction = West;
							Update();
							return;
						}
					}
				}
			}
		}
		else
		{
			// Same column monster is south
			DebugMessage("Monster is due south of Player");
			if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() - 32))
			{
				m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() - 32);
				return;
			}
			else
			{
				// Check the closet open node in Nouth and move to it
				//             P
				// *****   ***************** *
				//             M
				// M will move to the opening to the left
				std::vector<cTile>::iterator it;
				int distance_x = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetY() == m_Owner->GetY() - GAME_GRID)
					{
						if (abs((*it).GetX() - m_Owner->GetX()) <= distance_x)
						{
							distance_x = abs((*it).GetX() - m_Owner->GetX());
							// Set direction
							(*it).GetX() >= m_Owner->GetX() ? m_Direction = East : m_Direction = West;
							Update();
							return;
						}
					}
				}
			}
		}
	}
	
	if (m_Owner->GetY() == m_Player->GetY())
	{
		// Same row monster is west
		DebugMessage("Monster is due west of Player");
		if (m_Owner->GetX() < m_Player->GetX())
		{
			if (CanMove(m_Map, m_Owner->GetX() + GAME_GRID, m_Owner->GetY()))
			{
				m_Owner->SetLocation(m_Owner->GetX() + 32, m_Owner->GetY());
				return;
			}
			else
			{
				// Check the closet open node in East and move to it
				std::vector<cTile>::iterator it;
				int distance_y = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetX() == m_Owner->GetX() + GAME_GRID)
					{
						if (abs((*it).GetY() - m_Owner->GetY()) <= distance_y)
						{
							distance_y = abs((*it).GetY() - m_Owner->GetY());
							// Set direction
							(*it).GetY() >= m_Owner->GetY() ? m_Direction = North : m_Direction = South;
							Update();
							return;
						}
					}
				}
			}
		}
		else
		{
			// Same column monster is east
			DebugMessage("Monster is due east of Player");
			if (CanMove(m_Map, m_Owner->GetX() - GAME_GRID, m_Owner->GetY()))
			{
				m_Owner->SetLocation(m_Owner->GetX() - GAME_GRID, m_Owner->GetY());
				return;
			}
			else
			{
				// Check the closet open node in West and move to it
				std::vector<cTile>::iterator it;
				int distance_y = 5120;
				for (it = m_Map.begin(); it != m_Map.end(); it++)
				{
					if ((*it).GetX() == m_Owner->GetX() - GAME_GRID)
					{
						if (abs((*it).GetY() - m_Owner->GetY()) <= distance_y)
						{
							distance_y = abs((*it).GetY() - m_Owner->GetY());
							// Set direction
							(*it).GetY() >= m_Owner->GetY() ? m_Direction = North : m_Direction = South;
							Update();
							return;
						}
					}
				}
			}
		}
	}
	// When they are not in the same row and column
	// Simply move closer
	DebugMessage("Not in the same row or column");
	MoveCloser();
	Update();
}

void cMoveAIState::Think()
{
	// Do not move, yet, just a test
	// We don't need to call CalculatePath() if:
	// 1. The end node of close_list (actually the one on the entity)
	//	  is the same as the player entity
	// 2. The coordinate of the monster entity is in close_list
	// Then we only need to erase the nodes that are not useful in close_list
	// and call Update
	// Update() simply "teleport" the monster to the next node
	DebugMessage("Moving");
	std::cout << m_Owner->GetPath().size() << "\n";
	int start, end;
	bool recalculate = true;
	//for (start = 0; start < (m_Owner->GetPath()).size(); start++)
	//{
	//	if ((m_Owner->GetPath())[start].m_X == m_Owner->GetX() &&
	//		(m_Owner->GetPath())[start].m_Y == m_Owner->GetY())
	//	{
	//		for (end = start; end < (m_Owner->GetPath()).size(); end++)
	//		{
	//			if ((m_Owner->GetPath())[end].m_X == m_Player->GetX() &&
	//				(m_Owner->GetPath())[end].m_Y == m_Player->GetY())
	//			{
	//				// Remove the lements before start and after end
	//				m_Owner->ResetPath(start, end);
	//				recalculate = false;
	//				break;
	//			}
	//		}
	//		break;
	//	}
	//}
	//if (recalculate == true)
	//{
	//	CalculatePath();
	//}
	CalculatePath();
	// Walk the entity
	m_Owner->Walk();
}

void cMoveAIState::CalculatePath()
{
	//DebugMessage("Calculating Path");
	int current_x, current_y;
	if (m_OwnerTraverse.m_X == m_Player->GetX() &&
		m_OwnerTraverse.m_Y == m_Player->GetY())
	{
		// Stop the recursion and write into EntityTest
		DebugMessage("I have found a path to the player:");
		m_Owner->SetPath(close_list);
		m_Owner->DisplayPath();

		// Clean up
		close_list.clear();
		open_list.clear();
		m_OwnerTraverse.m_X = m_OwnerTraverse.m_Y = 0;
		return;
	}
	else
	{
		if (m_OwnerTraverse.m_X == 0 && m_OwnerTraverse.m_Y == 0)
		{
			// Not initiated
			//DebugMessage("Not initiated");
			current_x = m_Owner->GetX();
			current_y = m_Owner->GetY();

			// Prepare block_list
			block_list.clear();
			std::vector<cTile>::iterator it;
			for (it = m_Map.begin(); it != m_Map.end(); it++)
			{
				if ((*it).GetAccess() == 0)
				{
					int x = (*it).GetX();
					int y = (*it).GetY();
					std::cout << "Blocker" << x << " " << y << "\n";
					block_list.push_front(cPathNode{ x, y });
				}
			}
		}
		else
		{
			// Already initiated
			//DebugMessage("Already Initiated");
			
			current_x = m_OwnerTraverse.m_X;
			current_y = m_OwnerTraverse.m_Y;
			std::cout << "current is " << current_x << " " << current_y << "\n";
		}
	}
	// Calculate each tile the monster is to traverse and put into the queue
	
	int dest_x = m_Player->GetX();
	int dest_y = m_Player->GetY();

	// Start from the starting point
	close_list.push_back(cPathNode{ current_x, current_y });

	// Push all surrounding coordinates into open_list
	// Note that close_list must NOT be cleared until solved
	open_list.clear();

	open_list.push_front(cPathNode{ current_x - GAME_GRID, current_y - GAME_GRID });	// NW
	open_list.push_front(cPathNode{ current_x, current_y - GAME_GRID });	// N
	open_list.push_front(cPathNode{ current_x + GAME_GRID, current_y - GAME_GRID });	// NE
	open_list.push_front(cPathNode{ current_x + GAME_GRID, current_y});	// E
	open_list.push_front(cPathNode{ current_x + GAME_GRID, current_y + GAME_GRID });	// SE
	open_list.push_front(cPathNode{ current_x , current_y + GAME_GRID });	// S
	open_list.push_front(cPathNode{ current_x - GAME_GRID, current_y + GAME_GRID });	// SW
	open_list.push_front(cPathNode{ current_x - GAME_GRID, current_y});	// W

	//DebugMessage(" All neighboring nodes pushed!");
	std::cout << "We now have " << open_list.size() << "\n";

	// Remove blockers and close_list elements from open_list
	//RemoveBlock();
	if (open_list.size() == 0)
	{
		DebugMessage("All known nodes tried and failed!");
		return;
	}

	// Find the next node
	m_OwnerTraverse = FindOptimal();

	// Next search
	open_list.clear();	// clear for next node
	CalculatePath();
}

void cMoveAIState::RemoveBlock()
{
	DebugMessage("Removing blocks");
	// Check close_list elements for duplicates
	//std::cout << open_list.size() << " " << close_list.size() << " " << block_list.size() << "\n";
	if (open_list.size() <= 0)
	{
		DebugMessage("open_list NULL error!");
	}
	int close = 0;
	std::deque<cPathNode>::iterator it;
	for (it = open_list.begin(); it != open_list.end(); it++)
	{
		//DebugMessage("Checking open_list");
		if (close_list.size() <= 0)
		{
			DebugMessage("No close list yet");
			break;
		}
		std::deque<cPathNode>::iterator it2;
		for (it2 = close_list.begin(); it2 != close_list.end(); it2++)
		{
			if ((*it).m_X == (*it2).m_X && (*it).m_Y == (*it2).m_Y)
			{
				open_list.erase(it);
				DebugMessage("Found a duplicate for close");
				std::cout << "Close: " << (*it2).m_X << " " << (*it2).m_Y << "\n";
				it = open_list.begin();
				close += 1;
				break;
			}
		}
	}
	// Check open_list elements for blockers
	open_list.erase(std::remove_if(open_list.begin(), open_list.end(),
		[&](cPathNode& node) {return RemoveDuplicateBlock(node); }), open_list.end());

	//std::cout << open_list.size() << " " << close_list.size() << " " << block_list.size() << "\n";
	//for (it = open_list.begin(); it != open_list.end(); )
	//{
	//	std::deque<cPathNode>::iterator it2;
	//	//DebugMessage("Checking block_list");
	//	for (it2 = block_list.begin(); it2 != block_list.end(); it2 ++)
	//	{
	//		if ((*it).m_X == (*it2).m_X && (*it).m_Y == (*it2).m_Y)
	//		{
	//			open_list.erase(it);
	//			DebugMessage("Found a duplicate for blocker");
	//			std::cout << "Blocker: " << (*it2).m_X << " " << (*it2).m_Y << "\n";
	//			break;
	//		}
	//		else
	//		{
	//			continue;
	//		}
	//		it++;
	//	}
	//}
	
	DebugMessage("Removing ending");
	return;
}

bool cMoveAIState::RemoveDuplicateBlock(const cPathNode& test)
{
	if (block_list.empty())
	{
		return false;
	}
	std::deque<cPathNode>::iterator it;
	for (it = block_list.begin(); it != block_list.end(); it++)
	{
		if (test.m_X == (*it).m_X && test.m_Y == (*it).m_Y)
		{
			return true;
		}
	}
	return false;
}

cPathNode cMoveAIState::FindOptimal()
{
	std::deque<cPathNode>::iterator it4;
	for (it4 = open_list.begin(); it4 != open_list.end(); it4++)
	{
		std::cout << "Open list BEFORE: " << (*it4).m_X << " " << (*it4).m_Y << "\n";
	}
	RemoveBlock();
	std::deque<cPathNode>::iterator it3;
	for (it3 = open_list.begin(); it3 != open_list.end(); it3++)
	{
		std::cout << "Open list AFTER: " << (*it3).m_X << " " << (*it3).m_Y << "\n";
	}
	// Return the only one
	if (open_list.size() == 1)
	{
		return open_list[0];
	}

	// Given an open_list, find the optimal next node
	int value = 65535;	// Random large number
	std::deque<cPathNode>::iterator it;
	cPathNode optimal;
	for (it = open_list.begin(); it != open_list.end(); it++)
	{
		if (abs((*it).m_X - m_Player->GetX()) + abs((*it).m_Y - m_Player->GetY()) <= value)
		{
			value = abs((*it).m_X - m_Player->GetX()) + abs((*it).m_Y - m_Player->GetY());
			optimal.m_X = (*it).m_X;
			optimal.m_Y = (*it).m_Y;
		}
	}
	return optimal;
}

void cMoveAIState::DisplayPath()
{
	if (close_list.size() <= 0)
	{
		DebugMessage("Close list is NULL!");
		return;
	}
	std::deque<cPathNode>::iterator it;
	for (it = close_list.begin(); it != close_list.end(); it++)
	{
		std::cout << (*it).m_X << "," << (*it).m_Y << " ";
	}
}

void cMoveAIState::MoveCloser()
{
	// So we already know they are not in same row/column
	int distance = abs(m_Owner->GetX() - m_Player->GetX()) +
		abs(m_Owner->GetY() - m_Player->GetY());
	// Loop through surrounding 4 tiles to find a better tile
	if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() - GAME_GRID))
	{
		// North, check if distance is shorter
		if (abs(m_Owner->GetX() - m_Player->GetX()) +
			abs(m_Owner->GetY() - GAME_GRID - m_Player->GetY()) < distance)
		{
			m_Direction = North;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX(), m_Owner->GetY() + GAME_GRID))
	{
		// South, check if distance is shorter
		if (abs(m_Owner->GetX() - m_Player->GetX()) +
			abs(m_Owner->GetY() + GAME_GRID - m_Player->GetY()) < distance)
		{
			m_Direction = South;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX() - GAME_GRID, m_Owner->GetY()))
	{
		// West, check if distance is shorter
		if (abs(m_Owner->GetX() - GAME_GRID - m_Player->GetX()) +
			abs(m_Owner->GetY() - m_Player->GetY()) < distance)
		{
			m_Direction = West;
		}
	}
	if (CanMove(m_Map, m_Owner->GetX() + GAME_GRID, m_Owner->GetY()))
	{
		// East, check if distance is shorter
		if (abs(m_Owner->GetX() + GAME_GRID - m_Player->GetX()) +
			abs(m_Owner->GetY() - m_Player->GetY()) < distance)
		{
			m_Direction = East;
		}
	}
}

void cMoveAIState::Update()
{
	DebugMessage("Updating Monster");
	switch (m_Direction)
	{
	case North:
	{
		m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() - GAME_GRID);
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case South:
	{
		m_Owner->SetLocation(m_Owner->GetX(), m_Owner->GetY() + GAME_GRID);
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case West:
	{
		m_Owner->SetLocation(m_Owner->GetX() - GAME_GRID, m_Owner->GetY());
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	case East:
	{
		m_Owner->SetLocation(m_Owner->GetX() + GAME_GRID, m_Owner->GetY());
		std::cout << "Monster at " << m_Owner->GetX() << " " << m_Owner->GetY() << "\n";
		break;
	}
	default:
	{
		// Do not move
	}
	}
}

void cAttackAIState::Think()
{
	// If not under the influence of "Fear"/"Confusion"/etc.
	// Test code, need to modify cInventory to get the effect
	DebugMessage("Attacking!");
	Update(m_Owner, m_Player, m_Effect);
}

void cAttackAIState::Init(cEntityTest* owner, cEntityTest* player, cEffectFactory* factory)
{
	m_Owner = owner;
	m_Player = player;
	m_Effect = factory;
}

void cAttackAIState::Update(cEntityTest* owner, cEntityTest* target, cEffectFactory* effect_factory)
{
	if (target)
	{
		// Apply Damage effect on target
		std::cout << "Player health: " << target->GetAttributes().m_HP << "\n";
		/*effect_factory->CreateEffect("00_MODHP", 1,
			owner->GetAttributes().m_DmgDice * owner->GetAttributes().m_NumDmgDice,
			owner, target);*/
		effect_factory->CreateEffect("00_MODHP", 1, -5,	owner, target);
		std::cout << "Player health: " << target->GetAttributes().m_HP << "\n";
	}
}

cAIManager::cAIManager()
{
	m_IdleAI = new cIdleAIState;
	m_MoveAI = new cMoveAIState;
	m_AttackAI = new cAttackAIState;
	m_CurrentAI = m_IdleAI;
	m_Effect = NULL;
}

cAIManager::~cAIManager()
{
	m_IdleAI = NULL;
	m_MoveAI = NULL;
	m_AttackAI = NULL;
	m_CurrentAI = NULL;
}

void cAIManager::Init(cEffectFactory* factory)
{
	m_Effect = factory;
}

void cAIManager::Think(cEntityTest* owner, cEntityTest* player)
{
	DebugMessage("Thinking...");
	m_MoveAI->Init(m_Map, owner, player);
	m_IdleAI->Init(m_Map, owner, player);
	if (!owner || !player)
	{
		DebugMessage("Critical Error! No monster or player!");
	}
	// Attack if close
	if (abs(owner->GetX() - player->GetX()) <= GAME_GRID &&
		abs(owner->GetY() - player->GetY()) <= GAME_GRID)
	{
		m_AttackAI->Init(owner, player, m_Effect);
		m_CurrentAI = m_AttackAI;
	}
	else
	{
		// Move if can see player
		if (LOS(owner, player))
		{
			m_CurrentAI = m_MoveAI;
		}
		else
		{
			// Otherwise just move idly
			m_CurrentAI = m_IdleAI;
		}
	}
	// Execute
	m_CurrentAI->Think();
}

bool cAIManager::LineInRectangle(int start_x, int start_y, int end_x, int end_y,
	int tile_x, int tile_y)
{
	// Check if all corners are on the same side of the line
	// Line equation: F(x y) = (y2-y1)*x + (x1-x2)*y + (x2*y1-x1*y2)
	/* If F(x y) = 0, (x y) is ON the line. 
	If F(x y) > 0, (x y) is "above" the line. 
	If F(x y) < 0, (x y) is "below" the line.*/

	int counter_zero, counter_greater, counter_smaller;
	counter_zero = counter_greater = counter_smaller = 0;

	int delta_y = end_y - start_y;
	int delta_x = start_x - end_x;
	int c = end_x * start_y - start_x * end_y;

	// Four Corners
	int value_ul = delta_y * tile_x + delta_x * tile_y + c;
	int value_ur = delta_y * (tile_x + GAME_GRID) + delta_x * tile_y + c;
	int value_lr = delta_y * (tile_x + GAME_GRID) + delta_x * (tile_y + GAME_GRID) + c;
	int value_ll = delta_y * tile_x + delta_x * (tile_y + GAME_GRID) + c;

	//  Print for Debug
	std::cout << "UL: " << value_ul << " UR: " << value_ur <<
		" LR: " << value_lr << " LL: " << value_ll << "\n";

	// calculate counters
	if (value_ul == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ul > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_ur == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ur > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_lr == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_lr > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}
	if (value_ll == 0)
	{
		counter_zero += 1;
	}
	else
	{
		if (value_ll > 0)
		{
			counter_greater += 1;
		}
		else
		{
			counter_smaller += 1;
		}
	}

	// If counter_zero == 1, and counter_greater or smaller == 3, pass
	if ((counter_zero == 1 && counter_greater == 3) ||
		(counter_zero == 1 && counter_smaller == 3))
	{
		DebugMessage("Only one intersection, pass");
		return false;
	}

	// If counter_greater or smaller == 4, pass
	if (counter_greater == 4 || counter_smaller == 4)
	{
		DebugMessage("No intersection, pass");
		return false;
	}

	// All others cannot pass
	DebugMessage("More than one intersection, blocked");
	return true;
}

bool cAIManager::LOS(cEntityTest* owner, cEntityTest* player)
{
	// If player is out of MONSTER_FOV, ignore
	int monster_x = owner->GetX();
	int monster_y = owner->GetY();
	int player_x = player->GetX();
	int player_y = player->GetY();

	if (abs(monster_x - player_x) > MONSTER_FOV ||
		abs(monster_y - player_y) > MONSTER_FOV)
	{
		DebugMessage("Player too far from me!");
		return false;
	}
	else
	{
		std::cout << abs(monster_y - player_y) << "\n";
		DebugMessage("Player in range");
	}

	// Now if player is in FOV we check the LOS from MIDDLEPOINT
	int monster_middle_x = monster_x + GAME_GRID / 2;
	int monster_middle_y = monster_y + GAME_GRID / 2;
	int player_middle_x = player_x + GAME_GRID / 2;
	int player_middle_y = player_y + GAME_GRID / 2;
	std::vector<cTile>::iterator it;
	int counter_blocker = 0;
	// Check for no blockers
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() == 0 &&
			(*it).GetX() >= std::min(monster_x, player_x) &&
			(*it).GetX() <= std::max(monster_x, player_x) &&
			(*it).GetY() >= std::min(monster_y, player_y) &&
			(*it).GetY() <= std::max(monster_y, player_y))
		{
			counter_blocker += 1;
		}
	}
	if (counter_blocker == 0)
	{
		DebugMessage("No blocker found!");
		return true;
	}
	// Upper Left corner of player occupied tile
	DebugMessage("Upper Left");
	int counter = 0;
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
				player_x, player_y, (*it).GetX(), (*it).GetY()))
		{
			// Upper Left corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
	}	
	if (counter == 0)
	{
		DebugMessage("Upper Left PASSED!");
		return true;
	}
	counter = 0;	// Reset
	DebugMessage("Upper Left Blocked!");
	DebugMessage("Lower Right");
	// Lower Right corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x + GAME_GRID, player_y + GAME_GRID, (*it).GetX(), (*it).GetY()))
		{
			// Lower Right corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
		DebugMessage("Lower right PASSED!");
		return true;
	}
	if (counter == 0)
	{
		DebugMessage("Lower Right PASSED!");
		return true;
	}
	DebugMessage("Lower Right Blocked!");
	counter = 0;
	
	DebugMessage("Upper Right");
	// Upper Right corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			//DebugMessage("Block passed");
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x + GAME_GRID, player_y, (*it).GetX(), (*it).GetY()))
		{
			// Upper Right corner blocked by some blocker
			counter += 1;
			break;
		}
		else
		{
			continue;
		}
		// Not blocked by each blocker
		DebugMessage("Upper Right PASSED!");
		return true;
	}
	if (counter == 0)
	{
		DebugMessage("Upper Right PASSED!");
		return true;
	}
	DebugMessage("Upper Right Blocked!");
	counter = 0;

	DebugMessage("Lower Left");
	// Lower Left corner of player occupied tile
	for (it = m_Map.begin(); it != m_Map.end(); it++)
	{
		// Pass if not in the middle
		if ((*it).GetAccess() != 0 ||
			(*it).GetX() < std::min(monster_x, player_x) ||
			(*it).GetX() > std::max(monster_x, player_x) ||
			(*it).GetY() < std::min(monster_y, player_y) ||
			(*it).GetY() > std::max(monster_y, player_y))
		{
			//DebugMessage("Block passed");
			continue;
		}
		DebugMessage("One blocker");
		// Test for four vertices of player occupied tile
		// Once find one visible then check for other blocker tiles on this vertex
		if (LineInRectangle(monster_middle_x, monster_middle_y,
			player_x, player_y + GAME_GRID, (*it).GetX(), (*it).GetY()))
		{
			// Lower Left corner blocked by some blocker
			DebugMessage("Lower Left blocked! Player not in my LOS");
			return false;
		}
		else
		{
			continue;
		}
	}
	// Not blocked by each blocker
	DebugMessage("Lower left PASSED! ALL PASSED!");
	return true;
}