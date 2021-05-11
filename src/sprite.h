#ifndef SPRITE_H
#define SPRITE_H
#include<SDL2/SDL_image.h>
#include<SDL2/SDL.h>
class sprite {
public:
    SDL_Texture* text;
    SDL_Rect rect;
    sprite(int x, int y,int w,int h, SDL_Texture* _text);
    void render(SDL_Renderer* rend);
    ~sprite();
};

void sprite::render(SDL_Renderer* rend){
    SDL_RenderCopy(rend, text, NULL, &rect);
}

sprite::sprite(int x,int y,int w,int h, SDL_Texture* _text)
{
    rect.x=x;
    rect.y=y;
    rect.w=w;
    rect.h=h;
    text = _text;
}

#endif