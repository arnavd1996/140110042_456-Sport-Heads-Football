#include "mainMenu.h"

SDL_Surface* mainMenu:: OptimizedSurface(string filepath, SDL_Surface *windowSurface)
{
    SDL_Surface *optimizedSurface = nullptr;
    SDL_Surface *surface = SDL_LoadBMP(filepath.c_str());

    optimizedSurface = SDL_ConvertSurface(surface,windowSurface->format,0);

    SDL_FreeSurface(surface);
    return optimizedSurface;
}


mainMenu::mainMenu()
{

    window = SDL_CreateWindow("Sports heads football", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    windowSurface = SDL_GetWindowSurface(window);


    drawingRect.x = 0;
    drawingRect.y = 0;
    drawingRect.w = 640;
    drawingRect.h = 480;



    menu = OptimizedSurface("image1.bmp",windowSurface);
    playerChoose = OptimizedSurface("image2.bmp",windowSurface);
    gameChoose = OptimizedSurface("image4.bmp",windowSurface);
    instructions = OptimizedSurface("image3.bmp",windowSurface);
    currentImage = menu;



    while(openingPage)
    {
        while(SDL_PollEvent(&op) !=0)
        {
            if(op.type == SDL_QUIT)
            {
                openingPage = false;
                isRunning = false;
            }
            else if(op.type == SDL_KEYDOWN)
            {
                switch(op.key.keysym.sym)
                {
                case SDLK_0:
                    currentImage = menu;
                    break;
                case SDLK_1:
                    openingPage = false;
                    break;
                case SDLK_2:
                    cout<<"Player1: ";
                    currentImage = playerChoose;
                    SDL_BlitScaled(currentImage,NULL,windowSurface,&drawingRect);
                    SDL_UpdateWindowSurface(window);
                    while(toChoose1)               //to choose player1
                    {
                        while(SDL_PollEvent(&tc1) !=0)
                        {
                            if(tc1.type == SDL_QUIT)
                            {
                                openingPage = false;
                                isRunning = false;
                            }
                            else if(tc1.type == SDL_KEYDOWN)
                            {
                                switch(tc1.key.keysym.sym)
                                {

                                case SDLK_1:
                                    //select a player
                                    cout<<"Ronaldo chosen" << endl;
                                    toChoose1 = false;
                                    playerType1=1;
                                    break;
                                case SDLK_2:
                                    //select another player
                                    cout<<"Messi chosen"<< endl;
                                    toChoose1 = false;
                                    playerType1=2;
                                    break;
                                case SDLK_3:
                                    //select another player
                                    cout<<"Rooney chosen"<< endl;
                                    toChoose1 = false;
                                    playerType1=3;
                                    break;
                                }
                            }
                        }
                    }
                    toChoose1 = true;                            //player1 chosen now
                    currentImage = menu;
                    break;
                case SDLK_3:
                    cout<<"Player2: ";
                    currentImage = playerChoose;
                    SDL_BlitScaled(currentImage,NULL,windowSurface,&drawingRect);
                    SDL_UpdateWindowSurface(window);
                    while(toChoose2)               //to choose player 2
                    {
                        while(SDL_PollEvent(&tc2) !=0)
                        {
                            if(tc2.type == SDL_QUIT)
                            {
                                openingPage = false;
                                isRunning = false;
                            }
                            else if(tc2.type == SDL_KEYDOWN)
                            {
                                switch(tc2.key.keysym.sym)
                                {

                                case SDLK_1:
                                    //select a player
                                    cout<<"Ronaldo chosen" << endl;
                                    toChoose2 = false;
                                    playerType2=1;
                                    break;
                                case SDLK_2:
                                    //select another player
                                    cout<<"Messi chosen" << endl;
                                    toChoose2 = false;
                                    playerType2=2;
                                    break;
                                case SDLK_3:
                                    //select another player
                                    cout<<"Rooney chosen" << endl;
                                    toChoose2 = false;
                                    playerType2=3;
                                    break;
                                }
                            }
                        }
                    }
                    toChoose2 = true;                            //player 2 chosen now
                    currentImage = menu;
                    break;
                case SDLK_4:
                    currentImage = gameChoose;
                    SDL_BlitScaled(currentImage,NULL,windowSurface,&drawingRect);
                    SDL_UpdateWindowSurface(window);
                    while(toChoose3)               //to choose player1
                    {
                        while(SDL_PollEvent(&tc3) !=0)
                        {
                            if(tc3.type == SDL_QUIT)
                            {
                                openingPage = false;
                                isRunning = false;
                            }
                            else if(tc3.type == SDL_KEYDOWN)
                            {
                                switch(tc3.key.keysym.sym)
                                {

                                case SDLK_1:
                                    //select timed game mode
                                    toChoose3 = false;
                                    gameMode = 1;
                                    break;
                                case SDLK_2:
                                    //select another game mode
                                    toChoose3 = false;
                                    gameMode = 2;
                                    break;
                                }
                            }
                        }
                    }
                    toChoose3 = true;                            //game mode chosen now
                    currentImage = menu;
                    break;
                case SDLK_5:
                    currentImage = instructions;
                    break;
                }
            }
        }
        SDL_BlitScaled(currentImage,NULL,windowSurface,&drawingRect);
        SDL_UpdateWindowSurface(window);
    }


}







