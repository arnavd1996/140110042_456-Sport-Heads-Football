#include "background.h"
#include<SDL_image.h>
#include<iostream>


background::background(SDL_Renderer *renderTarget, std::string filePath, int x, int y)
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
	positionRect.x = x;
	positionRect.y = y;

}


background::~background()
{
	SDL_DestroyTexture(texture);
}

void background::Update(float delta)
{

}

void background::Draw(SDL_Renderer *renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, NULL, NULL);
}


