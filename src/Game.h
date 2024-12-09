#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*  
    Class that acts as the game engine
    Wrapper class.
*/



class Game
{
    private:
    //Variables 
    //Window
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    

    //Private funtions
    void initVariables();
    void initWindow();
    

    public:
    //Constructors / Desctructors
    Game();
    virtual ~Game();


    //Accesors
    const bool running() const;

    //Funtions 
    void pollEvents();
    void update();
    void render();
};