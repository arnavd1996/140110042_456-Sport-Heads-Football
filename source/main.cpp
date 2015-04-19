#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include"ball.h"
#include"Player.h"
#include"background.h"
#include"post.h"
#include"Powerups.h"
#include"mainMenu.h"
#include<cstdlib>
#include<time.h>
#include<simplecpp>
#include<math.h>
using namespace std;


int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    // Initializing and loading variables
    mainMenu Menu; /* The Menu object of class mainMenu contains all the initializations of SDL window and the renderer, renderTarget
                   and all loading, rendering and input of Main menu of game.*/

   // The following variables initialize the player characteristics
    float movespeed1 = 150.0f; //speed of player 1
    float movespeed2 = 150.0f; //speed of player2
    float upspeed1 = 1000.0f; //negative jump speed of player1, i.e. lesser the value, higher the jump
    float upspeed2 = 1000.0f;
    string image1 = "imageme.png"; // image file path of player 1
    string image2 = "imageme.png";

    //The following is used to assign player characteristics with different abilities where PlayerType1 is the input given by user in main menu
    //2 corresponds to Messi and 1 corresponds to Ronaldo
    switch(Menu.playerType1)
    {
    case 1:
        movespeed1 = 150.0f;
        upspeed1 = 600.0f;
        image1 = "image2.png";
        break;
    case 2:
        movespeed1 = 300.0f;
        upspeed1 = 1000.0f;
        image1 = "image1.png";
        break;
    }
    switch(Menu.playerType2)
    {
    case 2:
        upspeed2 = 1000.0f;
        movespeed2 = 300.0f;
        image2 = "image1.png";
        break;
    case 1:
        movespeed2 = 150.0f;
        upspeed2 = 600.0f;
        image2 = "image2.png";
        break;
    }

     // The following variables are initialized to implement powerups
    int temp = 0;
    int touch =3;
    int a=0;
    int i=0;
    int x1,y1;
    int x2,y2;

    //To randomize appearance of powerups
    std::srand(time(0));

    y1 = rand()%200 + 1;
    x1 = rand()%250 + 3;

    x2 = rand()%200 + 5;
    y2 = rand()%250 + 10;

    //Each class constructor is called here renderTarget is the renderer which makes the program use
    Player player1(Menu.renderTarget, image1, 16, 300, 3, 4,movespeed1,upspeed1);
    Player player2(Menu.renderTarget, image2, 592, 300, 3, 4, movespeed2, upspeed2);
    ball b(Menu.renderTarget, "ball1.png", 320,100 );
    background bg(Menu.renderTarget, "anfieldpng.png",100 ,200);
    Powerups P(Menu.renderTarget,"powerup2.png",x1,y1);
    Powerups P1(Menu.renderTarget,"powerup2.png",x2,y2);
    post poleL(Menu.renderTarget,"pole.png",0,250);
    post poleR(Menu.renderTarget,"pole.png",624,250);

    //The initialization of time related variables required in main game loop
    int currentTime = 0;
	int prevTime = 0;
	float delta = 0.0f;
	//initialization of variable to store keyboard input
	const Uint8 *keyState;

    while(Menu.isRunning)
    {

        prevTime = currentTime;
        currentTime = SDL_GetTicks(); // Gets the total time for which program has run

        delta = (currentTime - prevTime) / 1000.0f; //delta is the time interval between 2 loops

        //Event loop to handle any keyboard or mouse events or rather any event as such.
        while(SDL_PollEvent(&Menu.ev) != 0)
        {
            // Getting the events
            if(Menu.ev.type == SDL_QUIT)		Menu.isRunning = false; //if the function SDL_QUIT is called then stop the game loop

        }

        //storing keyboard input in keyState
        keyState = SDL_GetKeyboardState(NULL);

        //Calls to various functions in the classes
        player1.Update(delta,keyState);
        player2.Update(delta,keyState);
        b.Update(delta,player1,player2);
        b.IntersectsWith(player1);
        b.IntersectsWith(player2);
        b.scoreUpdate(currentTime,a, poleR, poleL, player1, player2);

        SDL_RenderClear(Menu.renderTarget); // To erase the rendered objects in previous iteration

        // To render updated objects in the new iteration
        bg.Draw(Menu.renderTarget);
        b.Draw(Menu.renderTarget);
        player1.Draw(Menu.renderTarget);
        player2.Draw(Menu.renderTarget);
        poleL.Draw(Menu.renderTarget);
        poleR.Draw(Menu.renderTarget);

        //This part of the code is to implement powerups

        if(currentTime>=5000 && currentTime<=40000)
            P.Draw(Menu.renderTarget);

            if (player1.LastTouch(b))
        {
            touch = 1;
        }

        if (player2.LastTouch(b))
        {
            touch = 0;
        }

        if(P.activatePowerups(b))
        {
            i=1;
            temp = touch;
        }
        if(currentTime >= 5000  && currentTime < 40000 && i==1 )
        {
            if(temp == 0)
            {

                player1.moveSpeed = 0.0f;
                player2.movesp = movespeed2;
            }
            else
            {
                player2.moveSpeed = 0.0f;
                player1.moveSpeed = movespeed1;
            }
        }
        else
        {
            player1.moveSpeed = movespeed1;
            player2.moveSpeed = movespeed2;
        }


        SDL_RenderPresent(Menu.renderTarget);

    }

    // Destroying the window and Renderer created and setting them to null pointer although not necessary but a good practice
    SDL_DestroyWindow(Menu.window);
    SDL_DestroyRenderer(Menu.renderTarget);

    Menu.window = nullptr;
    Menu.renderTarget = nullptr;

    IMG_Quit();
    SDL_Quit();

    return 0;

}
