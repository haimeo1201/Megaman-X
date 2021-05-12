#include<iostream>
#include "Game.h"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL_Utils.h"
using namespace std;
int main(int argc, char* argv[]){
    srand(0);
    Game game;
    game.init();
    game.loop();
    game.clear();
    return 0;
}