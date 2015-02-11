#include "SDL.h"
#include "Vector2f.h"
#include <math.h>
#include "TextureManager.h"
#include "KeyManager.h";
#include "Ship.h";

#pragma once

class Unit
{
public:
	Unit(float,float,float,float,Ship*);//x,y,w,h,r
	void Update(float timeElapsed);
	void Draw(SDL_Renderer*, SDL_RendererFlip);
	~Unit(void);
private:
	Vector2f velocity;
	Vector2f localPosition;
	Vector2f globalPosition;
	float width;
	float height;
	float speed;
	float rotation;
	int num;
	int data;
	float tElap;
	Ship* stationedAt;
	//LTexture texture;
	bool controlled;//whether attached as driver or not
};

