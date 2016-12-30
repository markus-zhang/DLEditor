#ifndef CGRAPHICS2_H_
#define CGRAPHICS2_H_

#include "cSDL2Graphics.h"

class cGraphics2
{
public:
	cGraphics2(int wndWidth, int wndHeight, std::string wndCaption);
	~cGraphics2();

	void LoadTexture(std::string filename, int r, int g, int b);

	//SDL 2.0 code to render a texture at (x, y)
	void RenderTexture(std::unique_ptr<cSDL2Texture> texturePtr, int srcX, int srcY, int desX, int desY,
		int width, int height);

	void RenderTextureModulate(std::unique_ptr<cSDL2Texture> texturePtr,
		int srcX, int srcY, int desX, int desY,
		int width, int height,
		Uint8 red, Uint8 green, Uint8 blue);

	void RenderTileSet(std::unique_ptr<cSDL2Texture> texturePtr,
		int srcX, int srcY, int desX, int desY,
		int srcWidth, int srcHeight,
		int desWidth, int desHeight);

	void RenderTileSetModulate(std::unique_ptr<cSDL2Texture> texturePtr,
		int srcX, int srcY, int desX, int desY,
		int srcWidth, int srcHeight,
		int desWidth, int desHeight,
		Uint8 red, Uint8 green, Uint8 blue);

	void RenderTest();

	void RenderRect(int x, int y, int width, int height,
		int red, int green, int blue);

	//SDL 2.0 code to clear screen
	void ClearScreen();

	//SDL 2.0 code to update screen for image and text
	//Step 1: LoadTexture or LoadText
	//Step 2: RenderTexture
	//Step 3: Show()
	void Show();

	void CloseImage();

	//SDL 2.0 code to load text
	void LoadText(std::string text, int size, int r, int g, int b);

	//SDL 2.0 code to render text in ONE function
	void RenderText(std::string text, int size, int r, int g, int b,
		int srcX, int srcY);

private:
	/*cSDL2Window m_Window;
	cSDL2Renderer m_Renderer;
	cSDL2Texture m_Texture;*/
	SDL_Rect m_Rect;

	//RAII Implementation
	std::unique_ptr<cSDL2Window> m_WindowPtr;
	std::unique_ptr<cSDL2Renderer> m_RendererPtr;
	std::unique_ptr<cSDL2Texture> m_TexturePtr;
};

#endif