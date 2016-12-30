#include "cGraphics2.h"

cGraphics2::cGraphics2(int wndWidth, int wndHeight, std::string wndCaption)
{
	// Tell SDL to intialize its video component 
	SDL_Init(SDL_INIT_VIDEO);

	// Initialize the True Type Font library
	TTF_Init();

	//SDL 2.0 code to create a window
	//m_Window.InitWindow(wndCaption.c_str(), wndWidth, wndHeight);

	//SDL 2.0 code to create renderer for window
	//m_Renderer.InitRenderer(m_Window, 0xFF, 0xFF, 0xFF);

	m_WindowPtr->InitWindow(wndCaption.c_str(), wndWidth, wndHeight);
	m_RendererPtr->InitRenderer(m_WindowPtr, 0xFF, 0xFF, 0xFF);
	//SDL 2.0 code to initiate PNG loading
	IMG_Init(IMG_INIT_PNG);
}

void cGraphics2::LoadTexture(std::string filename, int r, int g, int b)
{
	SDL_Surface* m_Temp = IMG_Load(filename.c_str());
	//Set color key
	SDL_SetColorKey(m_Temp, SDL_TRUE,
		SDL_MapRGB(m_Temp->format, r, g, b));

	//m_Texture.SetTexture(SDL_CreateTextureFromSurface(
	//	m_Renderer.GetRenderer(), m_Temp));
	m_TexturePtr->SetTexture(SDL_CreateTextureFromSurface(
		m_RendererPtr->GetRenderer(), m_Temp));

	SDL_FreeSurface(m_Temp);
}

void cGraphics2::RenderTexture(std::unique_ptr<cSDL2Texture> texturePtr,
	int srcX, int srcY, int desX, int desY, int width, int height)
{
	SDL_Rect g_SrcRect = { srcX, srcY, width, height };
	SDL_Rect g_DesRect = { desX, desY, width, height };
	//SDL_RenderCopy(m_Renderer.GetRenderer(), texture.GetTexture(), &g_SrcRect,
	//	&g_DesRect);
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), texturePtr->GetTexture(), &g_SrcRect,
		&g_DesRect);
}

void cGraphics2::RenderTextureModulate(std::unique_ptr<cSDL2Texture> texturePtr,
	int srcX, int srcY, int desX, int desY,
	int width, int height,
	Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texturePtr->GetTexture(), red, green, blue);
	SDL_Rect g_SrcRect = { srcX, srcY, width, height };
	SDL_Rect g_DesRect = { desX, desY, width, height };
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), texturePtr->GetTexture(), &g_SrcRect,
		&g_DesRect);
}

void cGraphics2::RenderTileSet(std::unique_ptr<cSDL2Texture> texturePtr,
	int srcX, int srcY, int desX, int desY,
	int srcWidth, int srcHeight,
	int desWidth, int desHeight)
{
	SDL_Rect g_SrcRect = { srcX, srcY, srcWidth, srcHeight };
	SDL_Rect g_DesRect = { desX, desY, desWidth, desHeight };
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), texturePtr->GetTexture(), &g_SrcRect,
		&g_DesRect);
}

void cGraphics2::RenderTileSetModulate(std::unique_ptr<cSDL2Texture> texturePtr,
	int srcX, int srcY, int desX, int desY,
	int srcWidth, int srcHeight,
	int desWidth, int desHeight,
	Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texturePtr->GetTexture(), red, green, blue);
	SDL_Rect g_SrcRect = { srcX, srcY, srcWidth, srcHeight };
	SDL_Rect g_DesRect = { desX, desY, desWidth, desHeight };
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), texturePtr->GetTexture(), &g_SrcRect,
		&g_DesRect);
}

void cGraphics2::RenderTest()
{
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), m_TexturePtr->GetTexture(), NULL, NULL);
}

void cGraphics2::RenderRect(int x, int y, int width, int height,
	int red, int green, int blue) {
	m_Rect = { x, y, width, height };
	SDL_SetRenderDrawColor(m_RendererPtr->GetRenderer(), red, green, blue, 255);
	SDL_RenderDrawRect(m_RendererPtr->GetRenderer(), &m_Rect);
	SDL_RenderPresent(m_RendererPtr->GetRenderer());
	SDL_SetRenderDrawColor(m_RendererPtr->GetRenderer(), 255, 255, 255, 255);
}

void cGraphics2::ClearScreen()
{
	SDL_RenderClear(m_RendererPtr->GetRenderer());
}

void cGraphics2::Show()
{
	SDL_RenderPresent(m_RendererPtr->GetRenderer());
}

void cGraphics2::CloseImage()
{
	m_TexturePtr->SetTexture(NULL);
}

void cGraphics2::LoadText(std::string text, int size, int r, int g, int b)
{
	//Load text into a surface
	TTF_Font* m_Font = TTF_OpenFont("ARIAL.ttf", size);
	SDL_Color m_Color = { r, g, b };
	SDL_Surface* m_Temp = TTF_RenderText_Solid(m_Font,
		text.c_str(), m_Color);
	m_TexturePtr->SetTexture(SDL_CreateTextureFromSurface(m_RendererPtr->GetRenderer(), m_Temp));

	SDL_FreeSurface(m_Temp);
}

void cGraphics2::RenderText(std::string text, int size, int r, int g, int b,
	int srcX, int srcY)
{
	//Load text into a surface
	TTF_Font* m_Font = TTF_OpenFont("ARIAL.ttf", size);
	SDL_Color m_Color = { r, g, b };
	SDL_Surface* m_Temp = TTF_RenderText_Solid(m_Font,
		text.c_str(), m_Color);
	int width = m_Temp->w;
	int height = m_Temp->h;
	m_TexturePtr->SetTexture(SDL_CreateTextureFromSurface(m_RendererPtr->GetRenderer(), m_Temp));
	SDL_Rect g_DesRect = { srcX, srcY, width, height };
	SDL_RenderCopy(m_RendererPtr->GetRenderer(), m_TexturePtr->GetTexture(), NULL, &g_DesRect);
	SDL_FreeSurface(m_Temp);
	TTF_CloseFont(m_Font);
}