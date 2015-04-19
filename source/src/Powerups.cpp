#include "Powerups.h"
#include<SDL_image.h>
#include<iostream>


Powerups::Powerups(SDL_Renderer *renderTarget, std::string filePath, int x, int y)
{
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    if (surface == NULL)
        std::cout << "Error" << std::endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            std::cout << "Error" << std::endl;

    }


    SDL_FreeSurface(surface);

    SDL_QueryTexture(texture, NULL, NULL, &lengRect.w, &lengRect.h);
    positionRect.x = x;
    positionRect.y = y;
    positionRect.w = lengRect.w;
    positionRect.h = lengRect.h;

}


Powerups::~Powerups()
{
    SDL_DestroyTexture(texture);
}

void Powerups::Update(float delta)
{

}

void Powerups::Draw(SDL_Renderer *renderTarget)
{
    SDL_RenderCopy(renderTarget, texture, NULL, &positionRect);
}

bool Powerups::activatePowerups(ball &b)
{

    if(positionRect.x + positionRect.w < b.positionRect.x || positionRect.x > b.positionRect.x + b.positionRect.w ||
            positionRect.y + positionRect.h < b.positionRect.y || positionRect.y > b.positionRect.y + b.positionRect.h)
    {
        return false;
    }
    SDL_SetTextureColorMod(texture, 255, 0, 0);
    return true;




}


