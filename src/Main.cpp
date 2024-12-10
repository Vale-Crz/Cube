#include "Game.h"

int main()
{
    //  Initialize Game engine
    Game game;
    

  //Gaame loop
    while (game.running())
    {

        //Update
        game.update();

        //Render
        game.render();



    



    }
//End of Game
    return 0;
}
