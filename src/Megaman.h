#ifndef MEGAMAN_H
#define MEGAMAN_H
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL_Utils.h"
#include "reading.h"
class Megaman {
public:
    int ultimate = 0;
    bool middash = 0;int stopdash = 0;
    string state;
    SDL_Rect stand[6], run[6], dash[3], die[9];
    int pos_x , pos_y , velo_x = 0, velo_dash = 0; int direc;
    SDL_Texture* state_idle;
    SDL_Texture* state_running;
    SDL_Texture* state_dashing;
    SDL_Texture* state_die;
    int cur_frame = 1;
    void init(SDL_Renderer *rend);
    void render(SDL_Renderer *rend);
    void idle(SDL_Renderer *rend);
    void walk(SDL_Renderer *rend );
    void slide(SDL_Renderer *rend );
    void fatal(SDL_Renderer *rend );
    void update();
};

void Megaman::init(SDL_Renderer *rend){
    state = "idle";
    pos_x = 20; pos_y=600;
    direc = 1;
    state_idle = loadTexture("./Image/idle.png",rend);
    state_running = loadTexture("./Image/walk.png",rend);
    state_dashing = loadTexture("./Image/dash.png",rend);
    state_die = loadTexture("./Image/die.png",rend);
    read("./Image/walk.txt",run);
    read("./Image/idle.txt", stand);
    read("./Image/dash.txt", dash);
    read("./Image/die.txt", die);
    }

void Megaman::walk(SDL_Renderer *rend ){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    if(direc == -1){
        flip =  SDL_FLIP_VERTICAL;
        angle = 180;
    }
    SDL_Rect rect = {pos_x,  pos_y, 50, 50};
    SDL_RenderCopyEx(rend, state_running, &run[cur_frame], &rect,angle,NULL, flip);
    pos_x+=velo_x;
    cur_frame++;
    if(cur_frame > 6) cur_frame = 1;
}

void Megaman::idle(SDL_Renderer *rend){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    if(direc == -1){
        flip =  SDL_FLIP_VERTICAL;
        angle = 180;
    }
    SDL_Rect rect = {pos_x,  pos_y, 50, 50};
    SDL_RenderCopyEx(rend, state_idle, &stand[cur_frame], &rect,angle,NULL, flip);
    cur_frame++;
    if(cur_frame > 5) cur_frame = 1;
}

void Megaman::slide(SDL_Renderer *rend ){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    if(direc == -1){
        flip =  SDL_FLIP_VERTICAL;
        angle = 180;
    }
    SDL_Rect rect = {pos_x,  pos_y, 50, 50};
    SDL_RenderCopyEx(rend, state_dashing, &dash[cur_frame], &rect,angle,NULL, flip);
    pos_x+=velo_dash;
    stopdash++;
    cur_frame++;
    if(cur_frame > 2) cur_frame = 1;
}

void Megaman::fatal(SDL_Renderer *rend ){
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double angle = 0;
    if(direc == -1){
        flip =  SDL_FLIP_VERTICAL;
        angle = 180;
    }
    SDL_Rect rect = {pos_x,  pos_y, 50, 50};
    SDL_RenderCopyEx(rend, state_die, &die[cur_frame], &rect,angle,NULL, flip);
    cur_frame++;
    SDL_Delay(100);
}

void Megaman::update(){
    if(state == "fatal") return;
    if(middash){
        if(stopdash > 5){
            middash = 0;
            velo_dash = 0;
        }
        else{
            if(state != "dash"){
                cur_frame = 1;
                state = "dash";
            }
            else cur_frame = 2;
            return;
        }
    }
    if(velo_x != 0){
        if(state != "walk"){
            cur_frame = 1;
            state = "walk";
        }
    }
    if(!velo_x && !velo_dash){
        if(state != "idle"){
            cur_frame = 1;
            state = "idle";
        }
    }
}

#endif
