#include "cGraphics.h"
#include "DebugTool.h"

cGraphics::cGraphics(int wndWidth, int wndHeight, std::string wndCaption)
{
	// Tell SDL to intialize its video component 
	SDL_Init(SDL_INIT_VIDEO);

	// Initialize the True Type Font library
	TTF_Init();

	//SDL 2.0 code to create a window
	m_Window = SDL_CreateWindow(wndCaption.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		wndWidth, wndHeight,
		SDL_WINDOW_RESIZABLE);
	//SDL 2.0 code to create renderer for window
	m_Renderer = SDL_CreateRenderer(m_Window, -1,
		0);
	//SDL 2.0 code to initiate renderer color
	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL 2.0 code to initiate PNG loading
	IMG_Init(IMG_INIT_PNG);
	m_Texture = NULL;
}

cGraphics::~cGraphics()
{
	SDL_DestroyWindow(m_Window);
	SDL_DestroyTexture(m_Texture);
	SDL_DestroyRenderer(m_Renderer);

	// Shutdown the True Type Font library
	TTF_Quit();

	//SDL 2.0 code to shutdown PNG loading facility
	IMG_Quit();

	// Tell SDL to shutdown and free any resources it was using. 
	SDL_Quit();
}

//SDL 2.0 code to prepare a texture
SDL_Texture* cGraphics::LoadTexture(std::string filename, int r, int g, int b)
{
	//Remove preexsiting texture
	//SDL_DestroyTexture(m_Texture);
	//m_Texture = NULL;

	SDL_Surface* m_Temp = IMG_Load(filename.c_str());
	//Set color key
	SDL_SetColorKey(m_Temp, SDL_TRUE,
		SDL_MapRGB(m_Temp->format, r, g, b));

	SDL_Texture* texture = SDL_CreateTextureFromSurface(
		m_Renderer, m_Temp);

	SDL_FreeSurface(m_Temp);
	return texture;
}

void cGraphics::RenderTexture(SDL_Texture* texture, int srcX, int srcY, cDim& dim)
{
	SDL_Rect g_SrcRect = { srcX, srcY, dim.m_Width, dim.m_Height };
	SDL_Rect g_DesRect = { dim.m_X, dim.m_Y, dim.m_Width, dim.m_Height };
	SDL_RenderCopy(m_Renderer, texture, &g_SrcRect,
		&g_DesRect);
}

void cGraphics::RenderTextureModulate(SDL_Texture* texture,
	int srcX, int srcY, int desX, int desY,
	int width, int height,
	Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
	SDL_Rect g_SrcRect = { srcX, srcY, width, height };
	SDL_Rect g_DesRect = { desX, desY, width, height };
	SDL_RenderCopy(m_Renderer, texture, &g_SrcRect,
		&g_DesRect);
}

void cGraphics::RenderTileSet(SDL_Texture* texture, int srcX, int srcY, int desX, int desY,
	int srcWidth, int srcHeight,
	int desWidth, int desHeight)
{
	SDL_Rect g_SrcRect = { srcX, srcY, srcWidth, srcHeight };
	SDL_Rect g_DesRect = { desX, desY, desWidth, desHeight };
	SDL_RenderCopy(m_Renderer, texture, &g_SrcRect,
		&g_DesRect);
}

void cGraphics::RenderTileSetModulate(SDL_Texture* texture,
	int srcX, int srcY, int desX, int desY,
	int srcWidth, int srcHeight,
	int desWidth, int desHeight,
	Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetTextureColorMod(texture, red, green, blue);
	SDL_Rect g_SrcRect = { srcX, srcY, srcWidth, srcHeight };
	SDL_Rect g_DesRect = { desX, desY, desWidth, desHeight };
	SDL_RenderCopy(m_Renderer, texture, &g_SrcRect,
		&g_DesRect);
}

void cGraphics::RenderTest()
{
	SDL_RenderCopy(m_Renderer, m_Texture, NULL, NULL);
}

void cGraphics::RenderRect(int x, int y, int width, int height,
	int red, int green, int blue, int alpha) {
	rect = { x, y, width, height };
	SDL_SetRenderDrawColor(m_Renderer, red, green, blue, alpha);
	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
	//SDL_RenderDrawRect(m_Renderer, &rect);
	SDL_RenderFillRect(m_Renderer, &rect);
	SDL_RenderPresent(m_Renderer);
	SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
}

void cGraphics::SetBlendMode(SDL_BlendMode blendmode)
{
	SDL_SetTextureBlendMode(m_Texture, blendmode);
}

void cGraphics::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(m_Texture, alpha);
}

void cGraphics::ClearScreen()
{
	SDL_RenderClear(m_Renderer);
}

void cGraphics::Show()
{
	SDL_RenderPresent(m_Renderer);
}

void cGraphics::CloseImage(SDL_Texture* texture)
{
	m_Texture = NULL;
}

void cGraphics::LoadText(std::string text, int size, int r, int g, int b)
{
	//Load text into a surface
	TTF_Font* m_Font = TTF_OpenFont("ARIAL.ttf", size);
	SDL_Color m_Color = { r, g, b };
	SDL_Surface* m_Temp = TTF_RenderText_Solid(m_Font,
		text.c_str(), m_Color);
	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Temp);

	SDL_FreeSurface(m_Temp);
}

//void cGraphics::RenderText(SDL_Texture* texture, int srcX, int srcY, int desX, int desY,
//								int width, int height
//	SDL_Rect g_SrcRect = {srcX, srcY, width, height};
//	SDL_Rect g_DesRect = {desX, desY, width, height};
//	SDL_RenderCopy(m_Renderer, m_Texture, &g_SrcRect,
//					&g_DesRect);
//}

void cGraphics::RenderText(std::string text, int size, int r, int g, int b,
	int srcX, int srcY)
{
	//Load text into a surface
	TTF_Font* m_Font = TTF_OpenFont("ARIAL.ttf", size);
	SDL_Color m_Color = { r, g, b };
	SDL_Surface* m_Temp = TTF_RenderText_Solid(m_Font,
		text.c_str(), m_Color);
	int width = m_Temp->w;
	int height = m_Temp->h;
	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Temp);
	SDL_Rect g_DesRect = { srcX, srcY, width, height };
	SDL_RenderCopy(m_Renderer, m_Texture, NULL, &g_DesRect);
	SDL_FreeSurface(m_Temp);
	TTF_CloseFont(m_Font);
}

// Aaron Cox, 2005 
// Markus Zhang, 2016