#ifndef CRESMANAGER_H_
#define	CRESMANAGER_H_

#include <unordered_map>
#include <vector>
#include "cGraphics.h"

class cResManager
{
public:
	//	Constructor and Destructor
	cResManager();
	~cResManager();

	void Clear();
	bool IsEmpty();

	void AddRes(std::pair<std::string, SDL_Texture*> res);
	void RemoveRes(std::string resid);
private:
	std::unordered_map <std::string, SDL_Texture*> m_Res;
};

#endif
