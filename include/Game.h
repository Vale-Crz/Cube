#pragma once

#include <iostream>
#include <vector>

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

    //Mouse position
    sf::Vector2i mousePosWindow;

    //Game objects
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;


    //Private funtions
    void initVariables();
    void initWindow();
    void initEnemies();
    

    public:
    //Constructors / Desctructors
    Game();
    virtual ~Game();


    //Accesors
    const bool running() const;

    //Funtions 
    void spawnEnemy();
    void pollEvents();
    void update();
    void render();
    void updateMousePositions();
};