#include "Game.h"


int main() 
{
    Game game; // Clase principal del juego

    // Bucle principal del juego
    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
