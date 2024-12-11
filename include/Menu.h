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

using namespace sf;

#define Max_main_menu 2

class Menu {
public:
    Menu(float width, float height);

    void moveUp();
    void moveDown();

    int getMenuPressed() const { return menuSelected; }

    void draw(RenderWindow& window);

    virtual ~Menu();

private:
    int menuSelected;
    Font font;
    Text mainMenu[Max_main_menu];
};
