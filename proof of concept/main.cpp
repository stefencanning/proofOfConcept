#include "SDL.h"
#include <stdio.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <iostream>
#include <ctime>
#include "SDL_ttf.h"
#include "SDL_timer.h"
#include "KeyManager.h"

//Screen dimension constants 
//The window we'll be rendering to 
SDL_Window* window = NULL; 
//Event handler 
SDL_Event eHandler;
//The window renderer 
SDL_Renderer* renderer = NULL; 
//Current displayed texture 
SDL_Rect stretchRect; 
//The dimensions of the level
const int LEVEL_WIDTH = 6000;
const int LEVEL_HEIGHT = 3000;
//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
//Starts up SDL and creates window 
bool init(); 
//Loads media 
bool loadMedia(); 
//Frees media and shuts down SDL 
void close();
SDL_Texture* loadTexture( std::string path );
SDL_Texture* testTexture = NULL; 
//Ship
SDL_Texture* ship = NULL;
SDL_Rect shipRec = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 200, 100 };
float scale = 3000; 
//Camera 
float screenOffSetX = shipRec.x;
float screenOffSetY = shipRec.y;
SDL_Rect renderQuad = {0, 0, LEVEL_WIDTH, LEVEL_HEIGHT };

using namespace std;


float camX = SCREEN_WIDTH/2, camY = SCREEN_HEIGHT/2;

bool init() 
{ 
	//Initialization flag 
	bool success = true; 
	int screenWidth= SCREEN_WIDTH;
	int screenHeight= SCREEN_HEIGHT;
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
		//Load media 
		if( !loadMedia() )	
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool run = true;
			//The camera area
            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

			while(run)
			{

			//Center the camera over the dot
			camera.x = camX;
			camera.y = camY;

            //Keep the camera in bounds
            if( camera.x < 0 )
            { 
                camera.x = 0;
            }
            if( camera.y < 0 )
            {
                camera.y = 0;
            }
            if( camera.x > LEVEL_WIDTH - camera.w )
            {
                camera.x = LEVEL_WIDTH - camera.w;
            }
            if( camera.y > LEVEL_HEIGHT - camera.h )
            {
                camera.y = LEVEL_HEIGHT - camera.h;
            }

			KeyManager::getKeyManager()->Update(eHandler);

			if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_A) && scale < 5000)
			{
				//renderQuad.x = -SCREEN_WIDTH/2;
				scale += 0.1;
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_D) && scale > 1800)
			{
				//renderQuad.y = -SCREEN_HEIGHT/2;
				scale -=0.1; 
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_LEFT))
			{
				camX -= 0.1;
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_RIGHT))
			{
				camX += 0.1;
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_UP))
			{
				camY -= 0.1;
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_DOWN))
			{
				camY += 0.1;
			}
			else if(KeyManager::getKeyManager()->keyPressed(SDL_SCANCODE_DOWN))
			{
				camY += 0.1;
			}
			
				//Clear screen
            SDL_RenderClear( renderer );
             
			SDL_RenderCopy( renderer, testTexture, &camera, &renderQuad );

			SDL_RenderCopy( renderer, ship, &camera, &shipRec );
				
			SDL_RenderSetScale(renderer, scale/6000, scale/3000);

            //Update screen
            SDL_RenderPresent( renderer );
		}
	}


	}
	close();
	return 0;
}

bool loadMedia() 
{ 
	//Loading success flag 
	bool success = true; 
	
	 //Load PNG texture
    testTexture = loadTexture( "pirateMap.png" );
    if( testTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }


	 //Load PNG texture
	ship = loadTexture( "ship.png" );
    if( testTexture == NULL )
    {
        printf( "Failed to load texture image!\n" );
        success = false;
    }

	return success; 
}