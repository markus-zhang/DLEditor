#include "cSDL2Graphics.h"

//SDL_Window Wrapper
cSDL2Window::cSDL2Window()
{
	m_Window = NULL;
}


cSDL2Window::~cSDL2Window()
{
	SDL_DestroyWindow(m_Window);
}

void cSDL2Window::InitWindow(std::string title, int height, int width)
{
	m_Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_RESIZABLE);
}


SDL_Window* cSDL2Window::GetWindow()
{
	return m_Window;
}

//SDL_Texture Wrapper
cSDL2Texture::cSDL2Texture()
{
	m_Texture = NULL;
}

cSDL2Texture::~cSDL2Texture()
{
	SDL_DestroyTexture(m_Texture);
}

SDL_Texture* cSDL2Texture::GetTexture()
{
	return m_Texture;
}

void cSDL2Texture::SetTexture(SDL_Texture* texture)
{
	m_Texture = texture;
}

//SDL_Renderer Wrapper
cSDL2Renderer::cSDL2Renderer()
{
	m_Renderer = NULL;
}
cSDL2Renderer::~cSDL2Renderer()
{
	SDL_DestroyRenderer(m_Renderer);
}

void cSDL2Renderer::InitRenderer(std::unique_ptr<cSDL2Window>& windowPtr,
	Uint32 red, Uint32 green, Uint32 blue)
{
	m_Renderer = SDL_CreateRenderer(windowPtr->GetWindow(), -1, 0);
	SDL_SetRenderDrawColor(m_Renderer, red, green, blue, 0xFF);
}

SDL_Renderer* cSDL2Renderer::GetRenderer()
{
	return m_Renderer;
}