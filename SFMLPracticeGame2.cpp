// SFMLPracticeGame2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Game.h"

using namespace std;
int main()
{
    //Initialize random seed
    srand(static_cast<unsigned>(time(0)));

    //Initialze game object
    Game game;
    
    //Game loop
    while (game.running()) //&& !game.getEndGame())
    {
        game.update();
        game.render();
    }



    //End application
    return 0;
}


