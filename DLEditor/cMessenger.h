/*	
	Experimental Messenger System for two sub systems
*/

#ifndef CMESSENGER_H_
#define CMESSENGER_H_

#include "cGUIBasicButton.h"
#include "cFile.h"

struct cMessage
{
	std::string m_Value;
};

template<class T, class Q>
class cMessenger
{
public:
	void Register(T& t, Q& q)
	{
		m_SystemOne = t;
		m_SystemTwo = q;
	}
private:
	T& m_SystemOne;
	Q& m_SystemTwo;
};

#endif
