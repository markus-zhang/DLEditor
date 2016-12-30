#ifndef CCAMERA_H_
#define CCAMERA_H_

class cCamera
{
public:
	cCamera() {}
	~cCamera() {}

	void Update(int x, int y) {
		m_X = x;
		m_Y = y;
	}
	int GetX() { return m_X; }
	int GetY() { return m_Y; }
private:
	int m_X, m_Y;
};

#endif
