#ifndef CANIMATIONMANAGER_H_
#define CANIMATIONMANAGER_H_

#include <unordered_map>
#include "cAnimation.h"
#include "cFile.h"

class cAnimationManager
{
public:
	cAnimationManager();
	~cAnimationManager();

	void Load(std::string filename, cFile& filemanager);
	void Register(cAnimation& animation);

	void SetAnimation(std::string id);	//Which to play?

	void Render(int x, int y);
private:
	std::unordered_map<std::string, cAnimation> m_AniManager;
	int m_AnimationNum;		// Number of animations
	std::string m_CurrentAnimation;
};

#endif
