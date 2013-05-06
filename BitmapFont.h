//
//  BitmapFont.h
//  B
//
//  Created by Steven Gleed on 14/04/2013.
//  Copyright (c) 2013 Steven Gleed. All rights reserved.
//

#ifndef __B__BitmapFont__
#define __B__BitmapFont__

#include <string>

class CharacterSet;
struct StringBlock;

class BitmapFont
{
public:
    BitmapFont();
    ~BitmapFont();
    
    bool ReadAndParseFont(const std::string& filename);
    int AddString();
    void ClearStrings();
    void DrawStrings();
    std::string GetFontName() const { return FontFilename; }
    std::string GetTextureName() const { return TextureFilename; }
    
private:
    CharacterSet * Alphabet;
    int NextCharacter;
    std::string FontFilename;
    std::string TextureFilename;
};

#endif /* defined(__B__BitmapFont__) */
