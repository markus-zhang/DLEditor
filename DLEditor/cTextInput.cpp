#include "cTextInput.h"

cTextInput::cTextInput()	{
	m_InputText = "Map ID";
	m_ID = "Blah";
	m_MaximumLength = 10;
	m_X = m_Y = 400;		//Just for testing
	m_Size = 16;
	m_R = m_G = m_B = 0;
	m_EnableEditing = 1;
	m_Height = m_Width = 0;
	m_Text = NULL;
}

cTextInput::~cTextInput()	{
}

int cTextInput::GetWidth()	{
	SDL_QueryTexture(m_Graphics->GetTexture(), NULL, NULL, &m_Width, &m_Height);
	return m_Width;
}

int cTextInput::GetHeight()	{
	SDL_QueryTexture(m_Graphics->GetTexture(), NULL, NULL, &m_Width, &m_Height);
	return m_Height;
}

std::string cTextInput::GetText()	{
	if (m_InputText.size() < 1) return "DEFAULT";
	return m_InputText;
}

void cTextInput::SetGraphics(cGraphics* graphics)	{
	m_Graphics = graphics;
}

void cTextInput::Delete()	{
	if (m_InputText.size() > 0)	m_InputText.pop_back();	
}

void cTextInput::Append(std::string input)	{
	m_InputText.append(input);
}

void cTextInput::Draw()	{
	if (m_InputText.size() == 0)	{
		return; 
	}

	m_Graphics->RenderText(m_InputText, m_Size, m_R, m_G, m_B,
							420, 0); 
}