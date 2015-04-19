#ifndef BALL_H
#define BALL_H
#pragma once
#include"Player.h"
#include<SDL.h>
#include<string>
#include"post.h"
using namespace std;

class Player;
class post;
class ball
{
public:
	SDL_Rect lengRect;
	SDL_Texture *texture;
	float moveSpeedx;
	float moveSpeedy;
	int score1=0,score2=0;
    int currentTime;
    int prevTime;
    int currentTimeG;
    int prevTimeG;

public:
	ball(SDL_Renderer *renderTarget, std::string filePath, int x, int y);
	~ball();
    ball();
    bool IntersectsWith(Player &p);
	void Update(float delta,Player &p1,Player &p2);
	void Draw(SDL_Renderer *renderTarget);

	void handleEvent(SDL_Event&);
    bool checkInRange(float val,float min,float max);
    bool checkIfCollide(Player & p);
	SDL_Rect positionRect;
	void scoreUpdate(int currentTime, int a, post &pole1, post &pole2, Player &p1, Player &p2);
	void displayScore();




};




#endif
