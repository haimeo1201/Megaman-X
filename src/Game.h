#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "SDL_Utils.h"
#include "Megaman.h"
#include <math.h>
#include "threat.h"
#include<vector>
#include "reading.h"
using namespace std;
class Game{
    public:
        bool flag = 1;
        bool running = 1;
        int frameCount, fps, lastFrame, lastTime = 0, count, reset;
        int index; 
        SDL_Window* win;
        SDL_Renderer* rend;
        SDL_Texture* background;
        threat T;
        Megaman X;
        void init();
        void render();
        void clear();
        void loop();
        void addBullet();
};
void Game::init(){
    index=0;
    initSDL(win, rend, "Megaman X", 700, 800);
    X.init(rend);
    X.state = "idle";
    T.init(rend);
    count = 0;
    background = loadTexture("/Image/star.png",rend);
}
void Game::loop(){
    while(running){
        lastFrame = SDL_GetTicks();
        if(lastFrame >= (lastTime + 1000)){
            lastTime = lastFrame;
            //cout<<frameCount<<"\n";
            frameCount = 0;
            count++;
            reset++;
            if(reset == 2 && X.state != "fatal") flag = 1;
            if(index<10000){
                index++;               
            }
            X.ultimate++;
        }
        SDL_RenderClear(rend);
            SDL_Event e;
            while(SDL_PollEvent(&e)){
                if(e.type == SDL_QUIT){
                    running = 0;
                }
                if(e.type == SDL_KEYDOWN){
                    if(e.key.keysym.sym == SDLK_RIGHT){
                        X.direc = 1;
                        X.velo_x = 10;
                    }
                    if(e.key.keysym.sym == SDLK_LEFT){
                        X.direc = -1;
                        X.velo_x = -10;
                    }
                    if(e.key.keysym.sym == SDLK_z && X.stopdash <= 5){
                        X.velo_dash = 15*X.direc;
                        X.middash = 1;
                    }
                    if(e.key.keysym.sym == SDLK_c && X.ultimate==15){
                        T.init(rend);
                        flag = 0;
                        reset = 0;
                        X.ultimate = 0;
                    }
                }
                if(e.type == SDL_KEYUP){
                    if(e.key.keysym.sym == SDLK_z){
                        X.middash = 0;
                        X.stopdash = 0;
                        X.velo_dash = 0;
                    }
                    else{
                        X.velo_x = 0;
                    }
                }
            }
            for(int i = 1; i <= min(index,1000); i++){
                if(T.inside(X.pos_x,X.pos_y)||T.inside(X.pos_x+50,X.pos_y)||T.inside(X.pos_x,X.pos_y+50)||T.inside(X.pos_x+50,X.pos_y+50)){
                    X.state = "fatal";
                    flag = 0;
                }
            }
            if(flag) T.update(index);
            X.update();
        render();
    }
}
void Game::render(){
    SDL_RenderCopy(rend,background,NULL,NULL);
    if(X.state=="idle") X.idle(rend);
    if(X.state=="walk") X.walk(rend);
    if(X.state=="dash") X.slide(rend);
    if(X.state=="fatal"){
       if(X.cur_frame<=8) X.fatal(rend);
       else running = 0;
    }
    if(flag) T.render(rend,index);
    frameCount++;
    fps = SDL_GetTicks() - lastFrame;
    if(fps<1000/15){
        SDL_Delay(1000/15-fps);
    } 
    SDL_RenderPresent(rend);
}
void Game::clear(){
    quitSDL(win,rend);
}
#endif