#include "KeyManager.h"

KeyManager* KeyManager::me;



KeyManager* KeyManager::getKeyManager()
{
	if(me==NULL)
	{
		me=new KeyManager();
	}
	return me;
}


KeyManager::KeyManager(void)
{
	QUIT=false;
}


KeyManager::~KeyManager(void)
{
}

void KeyManager::Update(SDL_Event eHandler)
{
	lastKeyStates=currentKeyStates;
	currentKeyStates = SDL_GetKeyboardState( NULL );
	SDL_GetMouseState( &MouseX, &MouseY );
	while(SDL_PollEvent(&eHandler) != 0)
	{
		if(eHandler.type == SDL_MOUSEBUTTONDOWN)
		{	
			if( eHandler.button.button == SDL_BUTTON_LEFT )
			{
				LeftClick = true;
			}
			if( eHandler.button.button == SDL_BUTTON_RIGHT )
			{
				RightClick = true;
			}
		}
		if( eHandler.type == SDL_MOUSEBUTTONUP )
		{
			if( eHandler.button.button == SDL_BUTTON_LEFT )
			{
				LeftClick = false;
			}
			if( eHandler.button.button == SDL_BUTTON_RIGHT )
			{
				RightClick = false;
			}
		}
	}
}


bool KeyManager::keyPressed(SDL_Scancode code)
{
	if(!lastKeyStates[code]&&currentKeyStates[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyDown(SDL_Scancode code)
{
	if(currentKeyStates[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyReleased(SDL_Scancode code)
{
	if(lastKeyStates[code]&&!currentKeyStates[code])
	{
		return true;
	}
	return false;
}

bool KeyManager::keyUp(SDL_Scancode code)
{
	if(currentKeyStates[code])
	{
		return true;
	}
	return false;
}