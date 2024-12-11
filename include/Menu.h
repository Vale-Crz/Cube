#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <sstream>
#include <windows.h>
#include <vector>


#define Max_main_menu 2

class Menu {
public:
    Menu(float width, float height);

    void moveUp();
    void moveDown();
    int getMenuPressed() const { return menuSelected; }
    void draw(sf::RenderWindow& window);

    virtual ~Menu();

private:
    int menuSelected;
    sf::Font font;
    sf::Text mainMenu[Max_main_menu];
    sf::Text titleText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 

    void initBackgroud();
    void initTitle(float width);
};
