#ifndef MAINMENU_H
#define MAINMENU_H
#include<SDL.h>
#include<SDL_image.h>
#include<cstdlib>
#include<iostream>
using namespace std;




class mainMenu
{
    public:
    mainMenu();
    SDL_Surface *surface;
    SDL_Surface *OptimizedSurface(string filepath, SDL_Surface *windowSurface);
    SDL_Surface *optimizedSurface;
    SDL_Window *window = nullptr;
	SDL_Renderer *renderTarget = nullptr;
    SDL_Surface *windowSurface = nullptr;
    SDL_Surface *menu = nullptr;
    SDL_Surface *playerChoose = nullptr;
    SDL_Surface *gameChoose = nullptr;
    SDL_Surface *instructions = nullptr;
    SDL_Surface *currentImage = nullptr;
	SDL_Rect drawingRect;
	int playerType1;
    int playerType2;
    int gameMode;
	bool toChoose1 = true;
	bool toChoose2 = true;
	bool toChoose3 = true;
	bool isRunning = true;

    bool openingPage = true;
    SDL_Event ev;
	SDL_Event op;
    SDL_Event tc1;
    SDL_Event tc2;
    SDL_Event tc3;
};

#endif // MAINMENU_H
