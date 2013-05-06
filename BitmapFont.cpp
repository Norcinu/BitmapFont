//
//  BitmapFont.cpp
//  B
//
//  Created by Steven Gleed on 14/04/2013.
//  Copyright (c) 2013 Steven Gleed. All rights reserved.
//

#include "BitmapFont.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/tokenizer.hpp>
#include "CharacterSet.h"
#include "StringUtils.h"

const int NumberOfTokens = 4;
const std::string LineStartTokens[NumberOfTokens] = {
    "info", "common", "chars", "chars"
};

const int LineTokenLength[4] = {13, 11, 2, 11};
const std::string LineOneTokens[13] = {
    "info", "face", "size", "bold", "italic", "charset", "unicode", "stretchH", "smooth", "aa", "padding", "spacing", "outline"
};
const std::string LineTwoTokens[11] = {
    "common", "lineHeight", "base", "scaleW", "scaleH", "pages", "packed",
    "alphaChnl", "redChnl", "greenChnl", "blueChnl"
};
const std::string LineThreeTokens[2] = {"Chars", "count"};
const std::string LineFourTokens[11] = {
    "char", "id", "x", "y", "width", "height", "xoffset", "yoffset",
    "xadvance", "page", "chnl"
};

BitmapFont::BitmapFont() : Alphabet(nullptr){
    
}

BitmapFont::~BitmapFont() {
    
}

bool BitmapFont::ReadAndParseFont(const std::string &filename) {
    using namespace std;
    using namespace boost;
    using namespace seg;
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    
    if (filename == "") {
        cerr << "Empty Font file name " << endl;
        return false;
    }
    
    ifstream FontFile(filename);
    if (!FontFile.is_open()) {
        cerr << "Could not open font file.\n";
        return false;
    }
    
    Alphabet = new CharacterSet;
    string line = "";
    while (getline(FontFile, line))
    {
        char_separator<char> sep(" =,");
        tokenizer tokens(line, sep);
        auto FirstToken = tokens.begin();
        if (*FirstToken == LineStartTokens[0])
        {
            int value = 0; // use counter and loop for current line token.
            //int counter = 0;
            //int lineCounter = 0;
            while (FirstToken != tokens.end()) {
            
                FromString<int>(value,*FirstToken, std::dec);
                Alphabet->RenderedSize = value;
                cout << "FirstToken = info\n";
            }
        }
        else if (*FirstToken == LineStartTokens[1])
        {
            cout << "FirstToken = common\n";
        }
        else if (*FirstToken == LineStartTokens[2])
        {
            cout << "FirstToken = chars\n";
        }
        else
        {
            cout << "FirstToken = char\n";
        }
        std::cout << "\n";
    }
    
    FontFile.close();
    return true;
}

