#ifndef BULLET_H
#define BULLET_H
#include<SDL2/SDL.h>
class bullet
{
public:
   SDL_Rect text;
   SDL_Rect size;
    int velo = 10, dam = 30;
     bool outside(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
        return size.x < 0 || size.y < 0 || size.x > SCREEN_WIDTH || size.y > SCREEN_HEIGHT;
    }
};

#endif