#include "ball.h"
#include"Player.h"
#include "post.h"
#include <cmath>
#include<SDL_image.h>
#include<iostream>
#include<simplecpp>
using namespace std;



ball::ball()
{

}

//Ball constructor
ball::ball(SDL_Renderer *renderTarget, std::string filePath, int x, int y)
{
     //Creating surface and making texture from it
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    if (surface == NULL)
        std::cout << "Error" << std::endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == NULL)
            std::cout << "Error" << std::endl;
    }

    //Destroying the surface created
    SDL_FreeSurface(surface);

    // Taking inputs of the dimensions of the texture created
    SDL_QueryTexture(texture, NULL, NULL, &lengRect.w, &lengRect.h);

    positionRect.x = x;
    positionRect.y = y;
    currentTime = 1005;
    prevTime = 0;
    currentTimeG = 1005;
    prevTimeG = 0;
    positionRect.w = lengRect.w;
    positionRect.h = lengRect.h;
    moveSpeedx = 150.0f;
    moveSpeedy = 0.0f;

}


ball::~ball()
{
    SDL_DestroyTexture(texture);
}

void ball::Update(float delta,Player &p1,Player &p2)   // Applying Boundary condition of the ball, bouncing and gravity
{
    currentTimeG =SDL_GetTicks();
    if (positionRect.y >= 300)
    {
        if(currentTimeG - prevTimeG > 100)
        {
            moveSpeedy = -moveSpeedy * 0.7;
            prevTimeG = currentTimeG;
        }


    }
    if (positionRect.x < 0 || positionRect.x > 640)
    {
        moveSpeedx *=-1;

    }
    if ( positionRect.y > 480||positionRect.y<0)
    {
        moveSpeedy *= -1;
    }
    if (positionRect.x < -10 || positionRect.x > 650 || positionRect.y > 400|| positionRect.y < -10)
    {
        positionRect.x = 320;
        positionRect.y = 0;
    }

    moveSpeedy += 400.0f * delta;
    positionRect.x += moveSpeedx * delta;
    positionRect.y += moveSpeedy * delta;

}

void ball::Draw(SDL_Renderer *renderTarget)
{
    SDL_RenderCopy(renderTarget, texture, NULL, &positionRect);

}

bool ball::IntersectsWith(Player &p)          // Checking Collision with the ball.
{
    currentTime = SDL_GetTicks();

    if(positionRect.x + positionRect.w <= p.positionRect.x || positionRect.x >= p.positionRect.x + p.positionRect.w ||
            positionRect.y + positionRect.h <= p.positionRect.y || positionRect.y >= p.positionRect.y + p.positionRect.h  )

    {
        return false;
    }
    if (currentTime - prevTime > 1000)    // Making sure that it detects only one collision.
    {


        moveSpeedy = -1*moveSpeedy;
        moveSpeedx = -1*moveSpeedx;
        prevTime = currentTime;
        return true;
    }
}




void ball :: scoreUpdate(int currentTime, int a, post &pole1, post &pole2, Player &p1, Player &p2)
{


    if((positionRect.y>pole2.positionRect.y) && (positionRect.x < pole2.positionRect.w))    // Maintaining Scores of player
    {
        score2 +=1;
        p1.positionRect.x = 16;
        p2.positionRect.x = 592;


        cout<<"score of player 2:"<<score2<<endl;
        if(score2==5 && a==1)
        {
            cout<<"PLAYER TWO WINS!!!!!!"<<endl;
            SDL_Quit();
            wait(10000);

        }

        positionRect.y= 100;
        positionRect.x= 320;
        moveSpeedx = 150.0f;
        moveSpeedy = 0.0f;


    }

    else if((positionRect.y>pole1.positionRect.y) && (positionRect.x > pole1.positionRect.x))
    {
        score1 += 1;
        p1.positionRect.x = 16;
        p2.positionRect.x = 592;
        cout<<"score of player 1:"<<score1<<endl;
        if(score1==5 && a==1)
        {
            cout<<"PLAYER ONE WINS!!!!!!"<<endl;
            SDL_Quit();
            wait(10000);
            return;
        }
        positionRect.y = 150;
        positionRect.x = 320;
        moveSpeedx = 150.0f;
        moveSpeedy = 0.0f;
        moveSpeedx *= -1;

    }


    if(currentTime>60000 && a==0)
    {

        if(score2>score1)
        {
            cout<<"PLAYER TWO WINS";
            SDL_Quit();
            wait(10000);
            return;
        }

        else if(score1> score2)
        {
            cout<<"PLAYER ONE WINS";
            wait(10000);
            SDL_Quit();
            return;
        }

        else
        {
            cout<<"MATCH DRAWN";
            wait(10000);
            SDL_Quit();
            return;
        }
    }

}
