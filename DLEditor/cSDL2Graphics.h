#ifndef CSDL2GRAPHICS_H_
#define CSDL2GRAPHICS_H_

#include <string>
#include <memory>
#include "SDL.h"     
#include "SDL_TTF.h" 
#include "SDL_image.h"

//SDL_Window Wrapper
class cSDL2Window 
{
public:
	cSDL2Window();
	~cSDL2Window();

	void InitWindow(std::string title, int height, int width);
	SDL_Window* GetWindow();
private:
	SDL_Window* m_Window;
};

//SDL_Texture Wrapper
class cSDL2Texture
{
public:
	cSDL2Texture();
	~cSDL2Texture();

	SDL_Texture* GetTexture();
	void SetTexture(SDL_Texture* texture);
private:
	SDL_Texture* m_Texture;
};

//SDL_Renderer Wrapper
class cSDL2Renderer
{
public:
	cSDL2Renderer();
	~cSDL2Renderer();

	void InitRenderer(std::unique_ptr<cSDL2Window>& windowPtr, Uint32 red, Uint32 green, Uint32 blue);
	SDL_Renderer* GetRenderer();
private:
	SDL_Renderer* m_Renderer;
};

#endif // !CSDL2GRAPHICS_H_

