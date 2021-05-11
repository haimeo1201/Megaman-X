#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL_Utils.h"
#include "Megaman.h"
#include <math.h>
using namespace std;
class Game{
    public:
        SDL_Window* win;
        SDL_Renderer* rend;
        Megaman X;
        void init();
        void render();
        void clear();
        void loop();
};
void Game::init(){
    initSDL(win, rend, "Megaman X", 700, 800);
}
void Game::loop(){
    bool running = 1;
    while(running){
        render();
        SDL_Event e;
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                running = 0;
            }
        }
    }
}
void Game::render(){
    X.idle();
}
void Game::clear(){
    quitSDL(win,rend);
}
#endif