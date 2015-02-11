#include <iostream>
#include "SDL.h"
#include "Vector2f.h"
#include <math.h>
#include "TextureManager.h"
#pragma once

class Ship
{
public:
	Ship(float,float,float,float,float);//x,y,w,h,r
	void Update(float timeElapsed,float,float);
	void Draw(SDL_Renderer*, SDL_RendererFlip);
	bool IsAlive();
	void UpdatePThread(int );
	static int threadFunction( void* data );
	void Kill();
	void Reset( SDL_Renderer*);
	void IncreaseScore();
	
private:
	Vector2f accel;
	Vector2f velocity;
	Vector2f position;
	float width;
	float height;
	float speed;
	float rotation;
	int num;
	int data;
	float tElap;
	SDL_sem* sem;
	SDL_Thread* threadID;
	
	~Ship();
	//LTexture texture;
	bool alive;
};
