#include "Unit.h"


Unit::Unit(float x,float y,float w,float h,Ship* S){
	globalPosition.x = x;
	globalPosition.y = y;
	localPosition.x = x;
	localPosition.y = y;
	width = h;
	height = w;
	speed = 50;
	stationedAt = S;
	controlled = false;
}


void Unit::Update(float timeElapsed){
	timeElapsed/=1000;
	velocity.x =0;
	velocity.y = 0;
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_J))
	{
		velocity.x += -cos((stationedAt->rotation)*M_PI/180)*speed;
		velocity.y += sin((stationedAt->rotation)*M_PI/180)*speed;
		//velocity.x -= speed;
    }
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_L))
	{
		velocity.x += cos((stationedAt->rotation)*M_PI/180)*speed;
		velocity.y += -sin((stationedAt->rotation)*M_PI/180)*speed;
		//velocity.x += speed;
    }
		
		
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_I))
	{
		velocity.x += -cos((stationedAt->rotation-90)*M_PI/180)*speed;
		velocity.y += sin((stationedAt->rotation-90)*M_PI/180)*speed;
		//velocity.y -=speed;
    }
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_K))
	{
		velocity.x += cos((stationedAt->rotation-90)*M_PI/180)*speed;
		velocity.y += -sin((stationedAt->rotation-90)*M_PI/180)*speed;
		//velocity.y +=speed;
    }
	/*
	if(position.x>SCREENW+10){
		position.x = -20;
	}
	else if(position.x<-30){
		position.x = SCREENW;
	}
	if(position.y>SCREENH+10){
		position.y = -20;
	}
	else if(position.y<-30){
		position.y = SCREENH;
	}*/

	localPosition.x+=velocity.x*timeElapsed;
	localPosition.y+=velocity.y*timeElapsed;
	globalPosition.x=stationedAt->position.x+(cos(stationedAt->rotation*M_PI/180)*localPosition.x)-(sin(stationedAt->rotation*M_PI/180)*localPosition.y);
	globalPosition.y=stationedAt->position.y+(sin(stationedAt->rotation*M_PI/180)*localPosition.x)+(cos(stationedAt->rotation*M_PI/180)*localPosition.y);
}

void Unit::Draw(SDL_Renderer* gRenderer, SDL_RendererFlip flipType){
	SDL_Rect posRec;
	posRec.x = globalPosition.x-width/2;
	posRec.y = globalPosition.y-height/2;
	posRec.w = width;
	posRec.h = height;
	SDL_RenderCopyEx(gRenderer,TextureManager::getManager()->skeletonTexture,NULL,new SDL_Rect(posRec),NULL,NULL,SDL_FLIP_NONE);
}
void Unit::setStationed(Ship* myShip)
{
	stationedAt = myShip;
}

Ship* Unit::getStationed()
{
	return stationedAt;
}
Unit::~Unit(void)
{
}
