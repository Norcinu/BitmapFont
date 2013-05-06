//
//  Visualisation.cpp
//  B
//
//  Created by Steven Gleed on 11/04/2013.
//  Copyright (c) 2013 Steven Gleed. All rights reserved.
//

#include "Visualisation.h"
#include "Sprite.h"

#include <cassert>
#include <iostream>
#include <SDL_image.h>
#include <cmath>
#include <algorithm>

#pragma warning(disable:4244)

Visualisation::Visualisation(void)
{
	screen = nullptr;
	screen_width  = 512;
	screen_height = 512;
	screen_depth  = 24;
	total_sprites = 0;
    
	full_screen = false;
    
	ui_rectangle.h = 32;
	ui_rectangle.w = screen_width;
	ui_rectangle.x = 0;
	ui_rectangle.y = screen_height - 32;
}

Visualisation::~Visualisation(void)
{
	SDL_FreeSurface(screen);
	Quit(0);
    IMG_Quit();
	SDL_Quit();
}

bool Visualisation::Initialise(const int height, const int width, bool fscreen)
{
	screen_height = height;
	screen_width = width;
	full_screen = fscreen;
    
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
		return false;

	if (!full_screen)
		screen = SDL_SetVideoMode(screen_width, screen_height, screen_depth,
                                  SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT);
	else
		screen = SDL_SetVideoMode(screen_width, screen_height, screen_depth,
                                  SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT | SDL_FULLSCREEN);
    
	int image_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int returned_flags = IMG_Init(image_flags);
    if ((returned_flags & image_flags) != image_flags) {
        std::cerr << "Error initialising image jpg an png support.\n";
        return false;
    }
    
    SDL_WM_SetCaption("Steven Gleed - Bitmap Font Demo", nullptr);
	
	return true;
}

bool Visualisation::AddSprite( int * id, const std::string& file )
{
    if (DoesSpriteExist(file)) {
        std::cout << "File already exists.\n";
        *id = -1;
        return false;
    }
    
	Sprite *spr = new Sprite;
	
	if (!spr->Load(file))
	{
		*id = -1;
        delete spr;
		return false;
	}
    
    ++total_sprites;
	sprites.push_back(spr);
	*id = static_cast<int>(sprites.size() - 1);
	
	int colour_key = SDL_MapRGB(screen->format, 255, 0, 255);
	SDL_SetColorKey(spr->RawSprite(), SDL_SRCCOLORKEY | SDL_RLEACCEL, colour_key);
    
	printf("sprite added ok. ID = %d\n", *id);
	return true;
}

int Visualisation::GetSpriteID(const std::string& sprite_name) const {
    if (DoesSpriteExist(sprite_name)) {
        for (auto i = 0; i < sprites.size()-1; i++) {
            if (sprites[i]->GetName() == sprite_name)
                return i;
        }
    }
    return -1;
}

void Visualisation::ClearScreen()
{
	SDL_FillRect(SDL_GetVideoSurface(), nullptr, SDL_MapRGB(SDL_GetVideoSurface()->format, 0,0,0));
}

bool Visualisation::DoesSpriteExist(const std::string& name) const {
    auto it = std::find_if(sprites.begin(), sprites.end(),
                           [&name](Sprite * s) -> bool {
                               if (name == s->GetName())
                                   return true;
                               else
                                   return false;
                           });
    
    if (it != sprites.end())
        return true;
    else
        return false;
}

void Visualisation::ClearScreen( Uint32 colour )
{
	SDL_FillRect(screen, nullptr, colour);
}

void Visualisation::CalculateFPS()
{
	static unsigned long lastTime = SDL_GetTicks();
	static long frames = 0;
    
	int newTime = SDL_GetTicks();
    
	if(newTime - lastTime > 1000)
	{
		auto newFPS = (frames * 1000 / (newTime - lastTime));
		printf("FPS : %ld\n", newFPS);
		lastTime = newTime;
		frames = 0;
	}
	frames++;
}

void Visualisation::FillRectangle( const SDL_Rect & rec, const std::string& col )
{
}

void Visualisation::Quit( const int exit_code ) const
{
	printf("Quitting with code : %d\n", exit_code);
}

void Visualisation::BeginScene()
{
    ClearScreen(SDL_MapRGB(screen->format, 0,0,0));
}

void Visualisation::EndScene()
{
	SDL_Flip(screen);
	CalculateFPS();
}

void Visualisation::DrawSprite( const int id, const math::Vector2& frame,math::Vector2& pos )
{
    sprites[id]->Render(screen, frame, pos);
}

void Visualisation::DrawLine( math::Vector2& p1, math::Vector2& p2, Uint32 colour )
{
	if (colour != 0)
		printf("colour is not 0\n");
    
	double slope = static_cast<double>((p2.y - p1.y)) / static_cast<double>((p2.x - p1.x));
	for (int x = p1.x; x <= p2.x; x++)
	{
		int y = static_cast<int>((slope * (x - p1.x)) + p1.y);
		SetPixel(x, y, colour);
	}
}

void Visualisation::SetPixel( int x, int y, const Uint32 colour )
{
	int bpp = screen->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
    
	switch(bpp) {
        case 1:
            *p = colour;
            break;
            
        case 2:
            *(Uint16 *)p = colour;
            break;
            
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (colour >> 16) & 0xff;
                p[1] = (colour >> 8) & 0xff;
                p[2] = colour & 0xff;
            }
            else
            {
                p[0] = colour & 0xff;
                p[1] = (colour >> 8) & 0xff;
                p[2] = (colour >> 16) & 0xff;
            }
            break;
            
        case 4:
            *(Uint32 *)p = colour;
            break;
	}
}

Uint32 Visualisation::GetPixel( SDL_Surface * surface, int x, int y )
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

void Visualisation::ClearGraphicSet()
{	
	while (!sprites.empty())
	{
        --total_sprites;
		sprites.pop_back();
	}
}

void Visualisation::FillRectangle( const rec::Rectangle& p )
{
	SDL_Rect r;
	r.x = p.left;
	r.y = p.top;
	r.h = p.bottom;
	r.w = p.right;
	SDL_FillRect(screen, &r, SDL_MapRGB(screen->format, 255, 0, 0));
}

