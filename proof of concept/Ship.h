#include <iostream>
#include "SDL.h"
#include "Vector2f.h"
#include <math.h>
#include "TextureManager.h"
#include "KeyManager.h"
#include "Body.h"
#pragma once

class Ship 
{
public:
	Ship(float,float,float,float,float);//x,y,w,h,r
	void Update(float timeElapsed);
	void Draw(SDL_Renderer*, SDL_RendererFlip);
	bool IsAlive();
	static int threadFunction( void* data );
	void Kill();
	void Reset( SDL_Renderer*);
	void IncreaseScore();
	Vector2f position;
	float rotation;
	
private:
	Vector2f accel;
	Vector2f velocity;
	float width;
	float height;
	float speed;
	int num;
	int data;
	float tElap;
	SDL_sem* sem;
	SDL_Thread* threadID;
	
	~Ship();
	//LTexture texture;
	bool alive;
};
