#pragma once
#include <stddef.h>
#include "SDL.h"
using namespace std;
class KeyManager
{
private:
	static KeyManager* me;
	KeyManager(void);
	Uint8* lastKeyStates;
	const Uint8* currentKeyStates;
	bool QUIT;
	int* keyLength;
	int MouseX,MouseY;
	bool LeftClick,RightClick;
public:
	bool keyDown(SDL_Scancode code);
	bool keyPressed(SDL_Scancode code);
	bool keyReleased(SDL_Scancode code);
	bool keyUp(SDL_Scancode code);
	static KeyManager* getKeyManager();
	void Update(SDL_Event eHandler);
	~KeyManager(void);
};
