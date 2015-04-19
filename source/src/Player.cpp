#include "Player.h"

#include<SDL_image.h>
#include<iostream>
#include<time.h>
#include<windows.h>
using namespace std;

//Default constructor
Player::Player()
{


}

//Player constructor
Player::Player(SDL_Renderer *renderTarget, std::string filePath, int x, int y, int framesX, int framesY, float movespeed, float upspeed)
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

    // Destroying surface created
    SDL_FreeSurface(surface);

    // Taking inputs of the dimensions of the texture created
    SDL_QueryTexture(texture, NULL, NULL, &cropRect.w, &cropRect.h);

    // Initializing the x and y coordinates of player
    positionRect.x = x;
    positionRect.y = y;

    textureWidth = cropRect.w;

    //The original image is a 4 by 3 array of small sprite images, framesX is the number of horizontal sprites.
    cropRect.w /= framesX;
    cropRect.h /= framesY;

    frameWidth = positionRect.w = cropRect.w;
    frameHeight = positionRect.h = cropRect.h;

    isActive = false;

    //Number of players initialized
    static int playerNumber = 0;
    playerNumber++;

    //Taking keyboard inputs for player1 and player2
    if(playerNumber == 1)
    {
        keys[0] = SDL_SCANCODE_W;
        keys[1] = SDL_SCANCODE_A;
        keys[2] = SDL_SCANCODE_D;
    }
    else
    {
        keys[0] = SDL_SCANCODE_UP;
        keys[1] = SDL_SCANCODE_LEFT;
        keys[2] = SDL_SCANCODE_RIGHT;
    }


    //Initialize variables
    moveSpeed = movespeed;
    movesp = movespeed;
    upSpeed = upspeed;
    upsp = upspeed;
    cropRect.x=0;
    cropRect.y=0;
}

//Destructor
Player::~Player()
{
    SDL_DestroyTexture(texture);
}

//Function for jump
void Player :: jump()
{
    if(positionRect.y==300)
        upSpeed = 300.0f;
}

//Function to update position of player
void Player::Update(float delta, const Uint8 *keyState)
{
    isActive = true;

    //Simulating Gravity
    positionRect.y -= upSpeed * delta;
    upSpeed-=upsp*delta;

    //Making sure player does not go below ground after falling down
    if(positionRect.y>300)positionRect.y=300;

    if(keyState[keys[0]])jump();

    //Moving left and right + cropping
    if(keyState[keys[1]])
    {
        positionRect.x -= moveSpeed * delta;
        cropRect.y = frameHeight;
    }
    else if(keyState[keys[2]])
    {
        positionRect.x += moveSpeed * delta;
        cropRect.y = frameHeight * 2;
    }

    else
        isActive = false;

    //Cropping after 4 loops and animation
    if(isActive)
    {
        frameCounter += delta;

        if(frameCounter >= 0.25f)
        {
            frameCounter = 0;
            cropRect.x += frameWidth;
            if(cropRect.x >= textureWidth)
                cropRect.x = 0;
        }
    }
    else
    {
        frameCounter = 0;
        cropRect.x = frameWidth;

    }

    //Make sure that player does not go outside boundary
    if(positionRect.x <= 0)positionRect.x=0;
    if(positionRect.x>=610)positionRect.x=610;
}



void Player::Draw(SDL_Renderer *renderTarget)
{
    SDL_RenderCopy(renderTarget, texture, &cropRect, &positionRect);
}

//Function to check ball is NOT intersecting with player
bool Player::IntersectsWithBall(ball &b)
{
    if(positionRect.x + positionRect.w < b.positionRect.x || positionRect.x > b.positionRect.x + b.positionRect.w ||
            positionRect.y + positionRect.h < b.positionRect.y || positionRect.y > b.positionRect.y + b.positionRect.h)
    {
        moveSpeed=movesp;
        return false;
    }
    moveSpeed = 0;
    upSpeed = 0;
    return true;
}

//Storing last touch of player
int Player :: LastTouch(ball &b)
{
    if(positionRect.x + positionRect.w < b.positionRect.x || positionRect.x > b.positionRect.x + b.positionRect.w ||
            positionRect.y + positionRect.h < b.positionRect.y || positionRect.y > b.positionRect.y + b.positionRect.h)
    {
        return 0;
    }

    return 1;
}
