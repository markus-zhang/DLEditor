/*
The first of polymorph of cGameMoveObject:
No Animation + Possible Movements + No Interaction
Examples: Magic Missiles, Arrows;
Note that NPC is of another class
*/

#include "cSDL2GameObject.h"

class cGameMoveObject : public cSDL2GameObject {
public:
	cGameMoveObject(cSDL2GameObject* owner);
	~cGameMoveObject();

	void Update(int sourceX, int sourceY, int targetX, int targetY);
	void Render();
private:
	int m_XSpeed, m_YSpeed; //pixel per frame
	cSDL2GameObject* m_Owner;
};