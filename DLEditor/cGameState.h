#ifndef CGAMESTATE_H_
#define CGAMESTATE_H_

#include "cState.h"
#include "cGameLevel.h"
#include "cFile.h"
#include "cInput.h"
#include <string>
#include <vector>
#include "cEntityFactory.h"
#include "cEffect.h"
#include "cAI.h"

class cGameState : public cState
{
public:
	cGameState(cGraphics* graphics, cInput* input);
	~cGameState();

	virtual bool Run(cStateManager* state_manager);
	virtual void HandleInput(cStateManager* state_manager);

	void LoadLevel(std::string filename);

	void SetBias(int xbias, int ybias);

private:
	std::vector<cGameLevel> m_World;
	int m_CurrentLevel;
	cFile m_FileManager;

	SDL_Texture* m_Tilemap;
	SDL_Texture* m_PlayerSprite;
	int m_XBias, m_YBias;
	//int m_PlayerX, m_PlayerY;
	
	// Entities
	cEntityTest m_Player;
	cEntityTestFactory m_EntityFactory;
	std::vector<cEntityTest*> m_Monsters;
	cAIManager m_AIManager;

	// Effects
	cEffectFactory* m_EffectFactory;
};

#endif
