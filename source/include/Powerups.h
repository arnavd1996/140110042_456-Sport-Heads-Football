#ifndef POWERUPS_H
#define POWERUPS_H

#include<SDL.h>
#include<string>
#include "ball.h"
#include "Player.h"

class Powerups
{
private:
	SDL_Rect lengRect;
	SDL_Texture *texture;

public:
	Powerups(SDL_Renderer *renderTarget, std::string filePath, int x, int y);
	~Powerups();

	void Update(float delta);
	void Draw(SDL_Renderer *renderTarget);
    bool activatePowerups(ball &b);
	SDL_Rect positionRect;


};

#endif // POWERUPS_H
