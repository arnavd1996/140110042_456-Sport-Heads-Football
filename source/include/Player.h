#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include"ball.h"
class ball;
#include<SDL.h>
#include<string>

class Player
{
public:
	SDL_Rect cropRect;
	SDL_Texture *texture;
	float moveSpeed; //speed of player
	float upSpeed; //jump speed of player
	float upsp; // temporary variable to store upSpeed
	float movesp; // temporary variable to store upSpeed
	float frameCounter; // Used for animation purpose, counts time
	int frameWidth, frameHeight; // Width and height of cropped out sprite image
	int textureWidth; //Width of cropped sprite image
	bool isActive; //Flag to check if to do animation or not
	SDL_Scancode keys[3]; //Array of key inputs created

	Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY, float movespeed, float upspeed);
	~Player();
	Player();

	void Update(float delta, const Uint8 *keyState); //Function to update position of player
	void Draw(SDL_Renderer *renderTarget); //Rendering the player image
	bool IntersectsWithBall(ball &b); //Detecting collision with ball
	void jump(); //Jumping of player
	int LastTouch(ball &b); //Flagging last touch of player for power up

	SDL_Rect positionRect; //Rectangle of sprite
};




#endif // PLAYER_H
