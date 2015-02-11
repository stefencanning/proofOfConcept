#include "Unit.h"


Unit::Unit(float x,float y,float w,float h,Ship* S){
	globalPosition.x = x;
	globalPosition.y = y;
	localPosition.x = x;
	localPosition.y = y;
	width = w;
	height = h;
	speed = 50;
	stationedAt = S;
	controlled = false;
	myJob=Jobs::none;
}


void Unit::Update(float timeElapsed){
	timeElapsed/=1000;
	velocity.x =0;
	velocity.y = 0;
	if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_SPACE))
	{
		if( ((localPosition.x-stationedAt->driverPos.x)*(localPosition.x-stationedAt->driverPos.x)) + 
			((localPosition.y-stationedAt->driverPos.y)*(localPosition.y-stationedAt->driverPos.y)) < 
			((stationedAt->driverPos.z)*(stationedAt->driverPos.z)) )
		{
			if(stationedAt->driver==NULL)
			{
				stationedAt->driver=this;
				myJob = Jobs::driving;
			}
			else
			{
				if(stationedAt->driver==this)
				{
					stationedAt->driver=NULL;
					myJob = Jobs::none;
				}
			}
		}
	}
	if(myJob == Jobs::none)
	{
		movement(timeElapsed);
	}
	else if(myJob == Jobs::driving)
	{
		if(stationedAt->driver==this)
		{
			stationedAt->movement(timeElapsed);
		}
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
}

void Unit::Draw(SDL_Renderer* gRenderer, SDL_RendererFlip flipType){
	globalPosition.x=stationedAt->position.x+(cos(stationedAt->rotation*M_PI/180)*localPosition.x)-(sin(stationedAt->rotation*M_PI/180)*localPosition.y);
	globalPosition.y=stationedAt->position.y+(sin(stationedAt->rotation*M_PI/180)*localPosition.x)+(cos(stationedAt->rotation*M_PI/180)*localPosition.y);
	SDL_Rect posRec;
	posRec.x = globalPosition.x-width/2;
	posRec.y = globalPosition.y-height/2;
	posRec.w = width;
	posRec.h = height;
	SDL_RenderCopyEx(gRenderer,TextureManager::getManager()->skeletonTexture,NULL,new SDL_Rect(posRec),NULL,NULL,SDL_FLIP_NONE);
}


Unit::~Unit(void)
{
}

void Unit::movement(float timeElapsed)
{
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_W))
	{
		velocity.x += -cos((stationedAt->rotation-90)*M_PI/180)*speed;
		velocity.y += sin((stationedAt->rotation-90)*M_PI/180)*speed;
		//velocity.y -=speed;
    }
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_S))
	{
		velocity.x += cos((stationedAt->rotation-90)*M_PI/180)*speed;
		velocity.y += -sin((stationedAt->rotation-90)*M_PI/180)*speed;
		//velocity.y +=speed;
    }
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_A))
	{
		velocity.x += -cos((stationedAt->rotation)*M_PI/180)*speed;
		velocity.y += sin((stationedAt->rotation)*M_PI/180)*speed;
		//velocity.x -= speed;
    }
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_D))
	{
		velocity.x += cos((stationedAt->rotation)*M_PI/180)*speed;
		velocity.y += -sin((stationedAt->rotation)*M_PI/180)*speed;
		//velocity.x += speed;
    }
}