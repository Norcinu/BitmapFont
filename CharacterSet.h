//
//  CharacterSet.h
//  B
//
//  Created by Steven Gleed on 13/04/2013.
//  Copyright (c) 2013 Steven Gleed. All rights reserved.
//

#ifndef CHARACTER_SET_H
#define CHARACTER_SET_H

#include <vector>
#include <list>
#include <string>
#include "maths.h"

struct BitmapCharacter;
struct Kerning;

class CharacterSet
{
public:
    CharacterSet();
    ~CharacterSet();
    
    int LineHeight;
    int Base;
    int RenderedSize;
    int Width;
    int Height;
    std::vector<BitmapCharacter*> Characters;
    
private:
    void Initialise();
};

struct BitmapCharacter {
    math::Vector2 position;
    int Height;
    int Width;
    int XOffset;
    int YOffset;
    int XAdvance;
    std::list<Kerning*> Kernings;
    
    BitmapCharacter();
    ~BitmapCharacter();
};

struct Kerning {
    int Second;
    int Amount;
};

struct StringBlock {
    std::string Text;
    math::Vector2 Rectangle;
    float Size;
    uint32_t Colour;
    enum Alignment {CENTRE, RIGHT, LEFT};
    Alignment TextAlign;
    bool HasKerning;
    
    StringBlock();
    ~StringBlock();
};

#endif
