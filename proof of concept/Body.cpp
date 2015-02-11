#include "Body.h"

Body::Body(float x,float y,float w,float h,float r) {
	position.x = x;
	position.y = y;
	width = h;
	height = w;
	rotation = r;
	//CreateShape(5,r,0);
	speed=40.0f;
	//texture.loadFromFile( "player.png", gRenderer );
	//m_animation = new Animation(6,185.5,187,"Mr.O_MO_.png",gRenderer);
}

void Body::Draw(SDL_Renderer* gRenderer, SDL_RendererFlip flipType) {
	//m_animation->Draw(gRenderer,flipType,dynamicBody->GetPosition().x - (texture.getWidth() / 2), -dynamicBody->GetPosition().y - (texture.getWidth() / 2),8);
	SDL_Rect posRec;
	posRec.x = position.x-width/2;
	posRec.y = position.y-height/2;
	posRec.w = width;
	posRec.h = height;
	float angle =  rotation*M_PI/180;
	SDL_RenderCopyEx(gRenderer,TextureManager::getManager()->shipTexture,NULL,new SDL_Rect(posRec),rotation,NULL,SDL_FLIP_NONE);
}


void Body::Update(float timeElapsed){
	timeElapsed/=1000;
	if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_A)) {
			rotation-=20*timeElapsed;
        }
		else if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_D)) {
			rotation+=20*timeElapsed;
        }
		accel.x =0;
		accel.y = 0;
		if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_W))
		{
			Vector2f dir;
			dir.x = cos(rotation*M_PI/180);
			dir.y = sin(rotation*M_PI/180);
			accel.x = dir.x*timeElapsed*speed;
			accel.y = dir.y*timeElapsed*speed;
        }
		else if (KeyManager::getKeyManager()->keyDown(SDL_SCANCODE_S))
		{
			Vector2f dir;
			dir.x = cos(rotation*M_PI/180);
			dir.y = sin(rotation*M_PI/180);
			accel.x = -dir.x*timeElapsed*speed;
			accel.y = -dir.y*timeElapsed*speed;
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

		velocity.x+=accel.x;
		velocity.y+=accel.y;

		velocity.x*=1.0f-(0.2f*timeElapsed);
		velocity.y*=1.0f-(0.2f*timeElapsed);
		
	position.x+=velocity.x*timeElapsed;
	position.y+=velocity.y*timeElapsed;

}
	bool Body::IsAlive(){
		return alive;
	}
	void Body::Reset(SDL_Renderer* gRenderer){
		alive = true;
	}