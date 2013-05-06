#include <iostream>
#include <SDL.h>
#include "Visualisation.h"
#include <memory>
#include "BitmapFont.h"
// Maybe Create a class that intiailises and deletes SDL
#include <boost/tokenizer.hpp>

class SDL_Wrapper {
    static bool Initialise() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
            return -1;
        }
        else
            return true;
    }
    
    static void CleanUp() {
        SDL_Quit();
    }
};

int main(int argc, char *argv[]) {
    SDL_Event event;
    bool running = true;
    math::Vector2 pos(0,0);
    std::shared_ptr<Visualisation> vis(new Visualisation);
    if (!vis->Initialise(480, 640)) {
        return -1;
    }
    int id = 0;
    if (!vis->AddSprite(&id, std::string("Data//monaco_0.png")))
        return -2;
    
    Uint8 *keys = SDL_GetKeyState(NULL);
    BitmapFont bitmap;
    //bitmap.ReadAndParseFont(std::string("Data//monaco.fnt"));
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                if (keys[SDLK_RIGHT]) {
                    if (pos.x+32 < 640-32)
                        pos.x += 20;
                    else
                        pos.x = 640-32;
                }
                else if (keys[SDLK_LEFT]){
                    if (pos.x >= 20)
                        pos.x -= 20;
                    else
                        pos.x = 0;
                }
            }
        
            if (event.type==SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
            //running=false;
        }
        vis->BeginScene();
        vis->DrawSprite(0, math::Vector2(0,0), pos);
        vis->EndScene();
    }
    std::cout << "Hello World!\n";
    return 0;
}

