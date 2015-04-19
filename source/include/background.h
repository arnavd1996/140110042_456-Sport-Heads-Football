#ifndef BACKGROUND_H
#define BACKGROUND_H
#include<SDL.h>
#include<string>


class background
{
private:
	SDL_Rect lengRect;
	SDL_Texture *texture;

public:
	background(SDL_Renderer *renderTarget, std::string filePath, int x, int y);
	~background();

	void Update(float delta);
	void Draw(SDL_Renderer *renderTarget);

	SDL_Rect positionRect;
};




#endif
