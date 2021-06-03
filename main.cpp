// How to set up project
//
// Setting up c++ and VSCode
// https://www.youtube.com/watch?v=ttYspMwzV8w
//


#include<iostream>
#include "Game.hpp"

using namespace std;


int main()
{
    Game game;
    
    // run the program as long as the window is open
    while (game.isRunning())
    {
        game.update();
        
        game.render();
    }

    return 0;
}