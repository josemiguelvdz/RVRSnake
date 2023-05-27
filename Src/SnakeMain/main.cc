// TODO: INCLUDE MEMORY LEAKS

#include "Game.h"

int main()
{
    Game* game = new Game();

    if (!game->setup()) {
        delete game;
        return -1;
    }

    /*
    * The main loop of the game
    * It is responsible of calculating the time between frames and when the game
    * does one iteration
    */
    game->loop();

    /*
    * Delete all the memory created
    */
    game->exit();
    delete game;

    return 0;
}