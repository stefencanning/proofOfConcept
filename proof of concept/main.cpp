#include "SDL.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>
#include "SDL_ttf.h"
#include "SDL_timer.h"
#include "TextureManager.h"
#include "Ship.h";
#include "Unit.h";
#include "KeyManager.h"
#include <vector>

//Screen dimension constants 
//The window we'll be rendering to 
SDL_Window* window = NULL; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = NULL; 
//Current displayed texture 
SDL_Rect stretchRect; 


Ship *ship = new Ship(200,200,330,150,0);//x,y,w,h,r
vector<Unit*> units = vector<Unit*>();
Unit* controlling;
//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
void draw();
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );


using namespace std;

bool init() 
{ 
	//Initialization flag 
	bool success = true; 
	int screenWidth=1280;
	int screenHeight=720;
	stretchRect.x = 0; 
	stretchRect.y = 0; 
	stretchRect.w = screenWidth; 
	stretchRect.h = screenHeight;


	//Initialize SDL 
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
	{ 
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() ); 
		success = false; 
	} 
	else 
	{  
		if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) < 0 )
		{
			printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
			success = false;
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow( "Skeleton Pirates", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN ); 
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() ); 
			success = false; 
		} 
		else 
		{ 
			//Create renderer for window 
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED ); 
			if( renderer == NULL ) 
			{ 
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() ); 
				success = false;
			} 
			else 
			{ 
				//Initialize renderer color 
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); 
				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG; 
				if( !( IMG_Init( imgFlags ) & imgFlags  ) ) 
				{ 
					string a = IMG_GetError();
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false; 
				} 
			} 
		}
	} 
	return success; 
}



SDL_Texture* loadTexture( std::string path ) 
{ 
	//The final texture 
	SDL_Texture* newTexture = NULL; 
	//Load image at specified path 
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) 
	{ 
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	} 
	else 
	{
		//Create texture from surface pixels 
		//newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface ); 
		if( newTexture == NULL ) 
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() ); 
		} 
		//Get rid of old loaded surface 
		SDL_FreeSurface( loadedSurface ); 
	} 
	return newTexture; 
}





void close() 
{ 
	//Free loaded image 
	//Destroy window 
	SDL_DestroyRenderer( renderer ); 
	SDL_DestroyWindow( window ); 
	window = NULL; 
	renderer = NULL; 
	//Quit SDL subsystems 
	IMG_Quit(); 
	SDL_Quit();

}



int main( int argc, char* args[] ) 
{ 
	bool QUIT = false;
	if( !init() )
	{ 
		printf( "Failed to initialize!\n" ); 
	} 
	else 
	{ 
		std::clock_t mClock;
		mClock = std::clock();
		//Load media 
		if( !loadMedia() )	
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool run = true;
			units.push_back(new Unit(0,0,20,20,ship));
			units.push_back(new Unit(10,0,20,20,ship));
			units.push_back(new Unit(0,10,20,20,ship));
			controlling=units.at(0);
			while(run)
			{

				if(((std::clock()-mClock)/(double)CLOCKS_PER_SEC) >= 1.0/480.0)
				{
					KeyManager::getKeyManager()->Update(eHandler);
					std::clock_t num = std::clock()-mClock;
					ship->Update(num);
					if(KeyManager::getKeyManager()->LeftClick)
					{
						for(int i =0; i < units.size(); i++)
						{
							float xPos = KeyManager::getKeyManager()->mousePosition().x;
							float yPos = KeyManager::getKeyManager()->mousePosition().y;
							if( ((xPos-units.at(i)->globalPosition.x)*(xPos-units.at(i)->globalPosition.x)) + 
								((yPos-units.at(i)->globalPosition.y)*(yPos-units.at(i)->globalPosition.y)) < 
								((units.at(i)->width)*(units.at(i)->width)) )
							{
								controlling = units.at(i);
							}
						}
					}
					if(controlling!=NULL)
					{
						controlling->Update(num);
					}
					draw();
					mClock = std::clock();
					if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_ESCAPE))
					{
						run=false;
					}
				}
			}
		}
	}
	close();
	return 0;
}


void draw(){
	SDL_RenderClear(renderer);
	ship->Draw(renderer,SDL_RendererFlip::SDL_FLIP_NONE);
	for(int i = 0; i < units.size(); i ++)
	{
		units.at(i)->Draw(renderer,SDL_RendererFlip::SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 
	TextureManager::getManager()->shipTexture = loadTexture("images/ship.png");
	TextureManager::getManager()->skeletonTexture = loadTexture("images/person.png");
	TextureManager::getManager()->circleTexture = loadTexture("images/circle.png");
	return success; 
}