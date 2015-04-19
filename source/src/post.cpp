#include "post.h"
#include<SDL_image.h>
#include<iostream>


post::post(SDL_Renderer *renderTarget, std::string filePath, int x, int y)
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


post::~post()
{
	SDL_DestroyTexture(texture);
}

void post::Update(float delta)
{

}

void post::Draw(SDL_Renderer *renderTarget)
{
	SDL_RenderCopy(renderTarget, texture, NULL, &positionRect);
}




