#include "Sprite.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <SDL_image.h>
#include "Common.h"

#pragma warning(disable:4244)

inline int ConvertStringToInt(const std::string& s)
{
	return atoi(s.c_str());
}

Sprite::Sprite() : sprite(nullptr), frame_height(32), frame_width(32)
{
}

Sprite::Sprite(SDL_Surface * surface) : sprite(surface), frame_height(32), frame_width(32)
{
}

Sprite::Sprite(SDL_Surface * surface, int fwidth, int fheight) : sprite(surface), 
	frame_width(fwidth), frame_height(fheight)
{
}

Sprite::~Sprite() 
{
	printf("deleting sprite\n");
	if (sprite) 
	{
		SDL_FreeSurface(sprite);
		sprite = nullptr;
	}
}

bool Sprite::Load( const std::string& filename )
{
	std::fstream config(filename.c_str());
	if (!config)
	{
		std::cout << "Error opening sprite config file : " << filename << std::endl;
		//return false;
	}

	std::string line;
	std::vector<std::string> description;
	int start_frame;
	
	while(std::getline(config, line)) 
	{
		size_t pos = line.find(" ")+1;
        
        // check for comments
        if (line[0] == '#')
            continue;
        
        std::string temp = line.substr(pos);
		description.push_back(temp);
	}

	config.close();

	//sprite = SDL_LoadBMP("Data//brick.bmp");//SDL_LoadBMP(description[0].c_str());
    sprite = IMG_Load(filename.c_str());
	frame_width = 512;//ConvertStringToInt(description[1]);
	frame_height = 256;//ConvertStringToInt(description[2]);
	start_frame = 0;//ConvertStringToInt(description[3]);
    name = "Brick";//common::FStripPathAndExtension(description[0]);
    
	if (sprite == nullptr) 
		return false;

	Uint32 colourkey = SDL_MapRGB(sprite->format, 255, 0, 255);
	SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colourkey);

#ifdef _DEBUG
	printf ("sprite w = %d.\n", sprite->clip_rect.w);
	printf ("sprite h = %d.\n", sprite->clip_rect.h);
	printf ("sprite x = %d.\n", sprite->clip_rect.x);
	printf ("sprite y = %d.\n", sprite->clip_rect.y);
#endif

	source.h = frame_height;
	source.w = frame_width;

	return true;
}

void Sprite::Render( SDL_Surface * screen, const math::Vector2& frame, math::Vector2& position )
{
	assert(screen);

	if (position.x < 0)
		position.x = 0.f;

	if (position.x >  640-frame_width) 
		position.x = 640-frame_width;

	if (position.y < 0)
		position.y = 0.f;

	if (position.y >  480-frame_height)
		position.y =  480-frame_height;
	
	rec.x = static_cast<int>(position.x);
	rec.y = static_cast<int>(position.y);

	source.x = static_cast<int>(frame.x);
	source.y = static_cast<int>(frame.y);

	SDL_BlitSurface(sprite, &source, screen, &rec);


}

Uint32 Sprite::GetPixel32(int x, int y)
{
    Uint32 *pixels = (Uint32 *)sprite->pixels;
    return pixels[ (y * sprite->w)  + x ];
}