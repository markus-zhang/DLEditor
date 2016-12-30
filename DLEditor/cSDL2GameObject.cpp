#include "cSDL2GameObject.h"

cSDL2GameObject::cSDL2GameObject() {
	m_Life = -1; // Permanent
	m_Timer.Reset();
}

cSDL2GameObject::~cSDL2GameObject() {

}

void cSDL2GameObject::Init(cGraphics* graphics, SDL_Texture* texture,
	int x, int y, int w, int h, int life) {
	m_Graphics = graphics;
	m_Texture = texture;
	m_Dimension.Set(x, y, w, h);
	m_Life = life;
}

void cSDL2GameObject::Update() {
	if (m_Life > -1) {
		m_Life -= m_Timer.GetMilliseconds();
	}
}

void cSDL2GameObject::Render() {
	if (m_Life >= -1) {
		m_Graphics->RenderTexture(m_Texture, 0, 0, m_Dimension);
	}
}
