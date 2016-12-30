#include "cGameMoveObject.h"

cGameMoveObject::cGameMoveObject(cSDL2GameObject* owner) {
	m_XSpeed = m_YSpeed = 0;
	m_Owner = owner;
}

cGameMoveObject::~cGameMoveObject() {

}

void cGameMoveObject::Update(int sourceX, int sourceY, int targetX, int targetY) {
	// Note that speed is pixel per frame, but life is in miliseconds
	// So we need to convert life to frames
	int lifeFrame = m_Life / 30;	// 3,000 ms = 100 frames
	m_XSpeed = (targetX - sourceX) / lifeFrame;
	m_YSpeed = (targetY - sourceY) / lifeFrame;
}

void cGameMoveObject::Render() {
	if (m_Life >= -1) {
		m_Graphics->RenderTexture(m_Texture, 0, 0, m_Dimension);
	}
}