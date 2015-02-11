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
	SDL_Texture* skeletonTexture;
	SDL_Texture* shipTexture;
	SDL_Texture* circleTexture;
};

