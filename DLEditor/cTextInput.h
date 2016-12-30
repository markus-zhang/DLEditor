#ifndef CTEXTINPUT_H_
#define CTEXTINPUT_H_

#include "cGraphics.h"
#include "cStaticButton.h"
#include "DebugTool.h"

class cTextInput	{
	friend class cEditorState;
private:
	std::string m_InputText;
	std::string m_ID;
	cGraphics* m_Graphics;
	SDL_Texture* m_Text;
	int m_MaximumLength;
	int m_X, m_Y, m_Size, m_R, m_G, m_B;
	int m_Height, m_Width;
	bool m_EnableEditing;
public:
	cTextInput();
	/*cTextInput(cGraphics* graphics, SDL_Texture* bitmap,
				int x, int y, int size, int r, int g, int b,
				int img_x, int img_y, int width, int height);*/
	~cTextInput();
	int GetWidth();
	int GetHeight();
	std::string GetText();
	void SetGraphics(cGraphics* graphics);

	void Delete();
	void Append(std::string input);

	void Draw();
};

#endif