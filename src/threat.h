#ifndef THREAT_H
#define THREAT_H
#include "reading.h"
#include <iostream>
#include "SDL_Utils.h"
#include<SDL2/SDL.h>
class threat{
public:
    SDL_Rect bullet1[7], bullet2[5];
    pair<int,int> velo[3] = {make_pair(5,5),make_pair(0,5),make_pair(-5,5)};
    SDL_Texture* bul;
    SDL_Rect list[1000],origin[1000];
    int type[1000], order[1000], orient[1000]; 
    void init(SDL_Renderer *rend);
    void render(SDL_Renderer *rend,int index);
    void update(int index);
    bool inside(int x,int y);
    bool outside(int SCREEN_WIDTH, int SCREEN_HEIGHT,int i) {
        return list[i].x < 0 || list[i].y < 0 || list[i].x > SCREEN_WIDTH || list[i].y > SCREEN_HEIGHT;
    }
};

bool threat::inside(int x,int y){
    for(int i = 1; i <= 1000 ; i++){
        if(list[i].x<=x&&(list[i].x+list[i].w>=x)&& list[i].y<=y&&(list[i].y+list[i].h>=y)) return true;
    }
    return false;
}

void threat::update(int index){
    for(int  i = 1;i < index; i++){
        list[i].x+=velo[orient[i]].first;
        list[i].y+=velo[orient[i]].second;
        list[i].w=40;
        list[i].h=40;
    }
}
void threat::render(SDL_Renderer *rend, int index){
    for(int  i = 1;i <= index; i ++){
        if(outside(600,800,i)){
            list[i].x = origin[i].x;
            list[i].y = origin[i].y;
        }
        if(type[i]==1){
            if(orient[i]==0) SDL_RenderCopyEx(rend, bul, &bullet1[order[i]], &list[i],40,NULL,SDL_FLIP_VERTICAL);
            if(orient[i]==1) SDL_RenderCopyEx(rend, bul, &bullet1[order[i]], &list[i],90,NULL,SDL_FLIP_VERTICAL);
            if(orient[i]==2) SDL_RenderCopyEx(rend, bul, &bullet1[order[i]], &list[i],140,NULL,SDL_FLIP_VERTICAL);
        }
        else {
            if(orient[i]==0) SDL_RenderCopyEx(rend, bul, &bullet2[order[i]], &list[i],40,NULL,SDL_FLIP_VERTICAL);
            if(orient[i]==1) SDL_RenderCopyEx(rend, bul, &bullet2[order[i]], &list[i],90,NULL,SDL_FLIP_VERTICAL);
            if(orient[i]==2) SDL_RenderCopyEx(rend, bul, &bullet2[order[i]], &list[i],140,NULL,SDL_FLIP_VERTICAL);
        }
    }
}
void threat::init(SDL_Renderer *rend){
    read("./Image/bullet2.txt",bullet1);
    read("./Image/bullet3.txt",bullet2);
    bul = loadTexture("/Image/bullets.png", rend);
    for(int index = 1; index <= 1000; index ++){
        if(index%3==0){
            list[index].y = origin[index].y = rand()%100;
            list[index].x = origin[index].x = 50 + rand()%400;
            orient[index] = 1;
        }
        if(index%3==1){
            list[index].x = origin[index].x = rand()%100;
            list[index].y = origin[index].y = 50 + rand()%400;
            orient[index] = 0;
        }
        if(index%3==2){
            list[index].x = origin[index].x = (rand()%(600-500+1))+500;
            list[index].y = origin[index].y = 50 + rand()%400;
            orient[index] = 2;
        }
        type[index]=rand() % 2;
        if(type[index]==1) order[index] = 1 + rand()%6;
        else  order[index] = 1+ rand()%4;
    }
}
#endif