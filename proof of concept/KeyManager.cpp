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
	currentKeyStates = SDL_GetKeyboardState(&keyLength);
	lastKeyStates = new Uint8[keyLength];
	memcpy(lastKeyStates, currentKeyStates, keyLength);
	LeftClick=false;
	RightClick=false;
	currentScroll=0;
	lastScroll=0;
	QUIT=false;
}

KeyManager::~KeyManager(void)
{
}

void KeyManager::Update(SDL_Event eHandler)
{
	lastKeyStates = new Uint8[keyLength];
	memcpy(lastKeyStates, currentKeyStates, keyLength);
	currentKeyStates = SDL_GetKeyboardState(&keyLength);

	SDL_GetMouseState( &MouseX, &MouseY );
	lastScroll = currentScroll;
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
		if(eHandler.type == SDL_MOUSEWHEEL)
		{
			currentScroll+=eHandler.button.x;
		}
	}
}

bool KeyManager::keyPressed(SDL_Scancode code)
{
	bool pressed=false;
	if(lastKeyStates!=NULL)
	{
		if(lastKeyStates[code])
		{
			pressed=true;
		}
	}
	if(!pressed&&currentKeyStates[code])
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
	bool pressed=false;
	if(lastKeyStates!=NULL)
	{
		if(lastKeyStates[code]==1)
		{
			pressed=true;
		}
	}
	if(pressed&&!currentKeyStates[code])
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

float KeyManager::scrollChange()
{
	return currentScroll-lastScroll;
}

float KeyManager::scrollValue()
{
	return currentScroll;
}

Vector2f KeyManager::mousePosition()
{
	return Vector2f(MouseX,MouseY);
}