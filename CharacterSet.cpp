//
//  CharacterSet.cpp
//  B
//
//  Created by Steven Gleed on 13/04/2013.
//  Copyright (c) 2013 Steven Gleed. All rights reserved.
//

#include "CharacterSet.h"

// Character Set ***************

CharacterSet::CharacterSet() {
    Initialise();
}

CharacterSet::~CharacterSet() {
    for (auto it = Characters.begin(); it != Characters.end(); it++) {
        delete *it;
    }
}

void CharacterSet::Initialise() {
    LineHeight = 0;
    Base = 0;
    RenderedSize = 0;
    Width = 0;
    Height = 0;
    for (auto i = 0; i < 256; i++) {
        BitmapCharacter * b = new BitmapCharacter;
        Characters.push_back(b);
    }
}

// End of Character Set ********

// BitmapCharacter ***************
BitmapCharacter::BitmapCharacter() {
    
}

BitmapCharacter::~BitmapCharacter() {
}

// End of BitmapCharacter *******
StringBlock::StringBlock() {
    
}

StringBlock::~StringBlock() {
    
}
