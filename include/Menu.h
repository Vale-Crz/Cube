#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

#define Max_main_menu 4

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
