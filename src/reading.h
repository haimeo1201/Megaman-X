#ifndef READING_H
#define READING_H
#include<iostream>
#include<fstream>
#include<string.h>
#include<SDL2/SDL.h>
#include<sstream>
using namespace std;
void read(string path, SDL_Rect* arr){
    fstream file;
    file.open(path, ios::in);
        int n;
        file>>n;
        for(int i=1;i<=n;i++){
            file>>arr[i].y;
            file>>arr[i].h;
            file>>arr[i].x;
            int _x;
            file>>_x;
            arr[i].w=_x-arr[i].x;
        }
        file.close();
}
#endif