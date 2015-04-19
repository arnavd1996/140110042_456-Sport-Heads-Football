#ifndef POST_H
#define POST_H
#include<SDL.h>
#include"ball.h"
#include<string>


class post
{
public:
	SDL_Rect lengRect;
	SDL_Texture *texture;

public:
	post(SDL_Renderer *renderTarget, std::string filePath, int x, int y);
	~post();


	void Update(float delta);
	void Draw(SDL_Renderer *renderTarget);

	SDL_Rect positionRect;
};

#endif
