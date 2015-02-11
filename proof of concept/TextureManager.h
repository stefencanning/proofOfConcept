#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
class TextureManager
{
private:
	static TextureManager* me;
	
public:
	static TextureManager* getManager();
	TextureManager(void);
	~TextureManager(void);
	SDL_Texture* texture;
	SDL_Texture*  mMenuTexture;
	SDL_Texture* particle;
	SDL_Texture* glacier;
	SDL_Texture* skeletonTexture;
	SDL_Texture* shipTexture;
	SDL_Texture* islandTexture;
	SDL_Texture* bg1;
	SDL_Texture* bg2;
	SDL_Texture* bg3;
	SDL_Texture* splashTex;
	SDL_Texture* menuTexture; 
	TTF_Font* font;
};

