#ifndef CACTION_H_
#define CACTION_H_

enum ActionType
{
	Save, Load, LoadButton, Quit, SaveXML
};

class cAction
{
public:
	virtual void Execute() = 0;
};

#endif
