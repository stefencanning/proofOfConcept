#pragma once
#include <stddef.h>
#include "SDL.h"
using namespace std;
class KeyManager
{
private:
	static KeyManager* me;
	KeyManager(void);
public:
	const Uint8* lastKeyStates;
	const Uint8* currentKeyStates;
	bool QUIT;
	int MouseX,MouseY;
	bool LeftClick,RightClick;
	static KeyManager* getKeyManager();
	void Update(SDL_Event eHandler);
	~KeyManager(void);
};

