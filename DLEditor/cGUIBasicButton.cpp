#include "cGUIBasicButton.h"
#include "DebugTool.h"

bool cGUIBasicButton::Load(
	cGraphics* graphics, SDL_Texture* bitmap,
	int x, int y, int img_x, int img_y,
	int width, int height, std::string id, std::string caption,
	ActionType action) {
	if (!graphics || !bitmap) {
		DebugMessage("Critical Error in Graphics System!");
		return false;
	}
	m_Graphics = graphics;
	m_Bitmap = bitmap;
	m_RenderStatus = 0;

	if (id.length() > 0)	
		m_ID = id;
	else
		m_ID = "Default";

	if (caption.length() > 0)
		m_Caption = caption;
	else
		m_Caption = "Default";

	m_TextRed = m_TextGreen = m_TextBlue = 255;

	m_X = x;
	m_Y = y;

	m_ImageX = m_ImageXDefault = img_x;
	m_ImageY = m_ImageYDefault = img_y;

	m_Width = width;
	m_Height = height;

	switch (action)
	{
	case Save:
		m_Action = new cSaveMapAction;
		break;
	default:
		DebugMessage("Invalid action type");
		break;
	}
	return true;
}

bool cGUIBasicButton::Load(
	cGraphics* graphics, SDL_Texture* bitmap,
	int x, int y, int img_x, int img_y,
	int width, int height, std::string id, std::string caption)
{
	if (!graphics || !bitmap) {
		DebugMessage("Critical Error in Graphics System!");
		return false;
	}
	m_Graphics = graphics;
	m_Bitmap = bitmap;
	m_RenderStatus = 0;

	if (id.length() > 0)
		m_ID = id;
	else
		m_ID = "Default";

	if (caption.length() > 0)
		m_Caption = caption;
	else
		m_Caption = "Default";

	m_TextRed = m_TextGreen = m_TextBlue = 255;

	m_X = x;
	m_Y = y;

	m_ImageX = m_ImageXDefault = img_x;
	m_ImageY = m_ImageYDefault = img_y;

	m_Width = width;
	m_Height = height;

	return true;
}

void cGUIBasicButton::Draw(int xbias, int ybias) {
	m_Graphics->RenderTexture(m_Bitmap, m_ImageX,
		m_ImageY, m_X - xbias, m_Y - ybias, m_Width, m_Height);
	m_Graphics->RenderText(m_Caption, 10, m_TextRed, m_TextGreen, m_TextBlue, m_X, m_Y);
}

bool cGUIBasicButton::IsOnFloat(int mousex, int mousey) {
	if (mousex > m_X && mousex < m_X + m_Width) {
		if (mousey > m_Y && mousey < m_Y + m_Height)
			return true;
	}
	return false;
}

void cGUIBasicButton::OnFloat() {
	m_TextRed = m_TextGreen = m_TextBlue = 0;
	m_ImageX += m_Width;

	// Test, Delete after
	/*if (m_Action)
	{
		m_Action->Execute();
	}*/
}

void cGUIBasicButton::Reset() {
	m_TextRed = m_TextGreen = m_TextBlue = 255;
	m_ImageX = m_ImageXDefault;
	m_ImageY = m_ImageYDefault;
}

void cGUIBasicButton::OnClick()
{
	if (m_Action)
	{
		m_Action->Execute();
	}
}

void cGUIBasicButton::OnClick11()
{
	//std::function<void()> callback = std::bind(cFile::LoadMap, this);
}