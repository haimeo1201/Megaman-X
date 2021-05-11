#ifndef MEGAMAN_H
#define MEGAMAN_H
#include<iostream>
#include<vector>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "sprite.h"
class Megaman {
private:
   int x,y;
public:
    vector<sprite*> idle, walk;
    Megaman();
    void idle();
    void walk();
};
Megaman::Megaman(){
    
}

#endif
