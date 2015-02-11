#include "TextureManager.h"

TextureManager* TextureManager::me;

TextureManager* TextureManager::getManager()
{
	if(me==NULL)
	{
		
		me=new TextureManager();
	}
	return me;
}

TextureManager::TextureManager(void)
{
}


TextureManager::~TextureManager(void)
{
}
