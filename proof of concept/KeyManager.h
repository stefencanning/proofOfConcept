#pragma once
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "SDL.h"
#include "Vector2f.h"
using namespace std;
class KeyManager
{
private:
	static KeyManager* me;
	KeyManager(void);
	Uint8* lastKeyStates;
	const Uint8* currentKeyStates;
	bool QUIT;
	int keyLength;
	int MouseX,MouseY;
	float currentScroll;
	float lastScroll;
public:
	bool keyDown(SDL_Scancode code);
	bool keyPressed(SDL_Scancode code);
	bool keyReleased(SDL_Scancode code);
	bool keyUp(SDL_Scancode code);
	bool LeftClick,RightClick;
	float scrollChange();
	float scrollValue();
	Vector2f mousePosition();
	static KeyManager* getKeyManager();
	void Update(SDL_Event eHandler);
	~KeyManager(void);
};

