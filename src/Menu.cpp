#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("./assets/fonts/Daydream.ttf")) {
        std::cerr << "ERROR: Font could not be loaded!" << std::endl;
    }

    // Configurar las opciones del menú
    const std::string menuItems[] = {"Play", "Exit"};
    for (int i = 0; i < Max_main_menu; ++i) {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(Color::White);
        mainMenu[i].setString(menuItems[i]);
        mainMenu[i].setCharacterSize(70);
        mainMenu[i].setPosition(Vector2f(width / 2 - 100, height / 2 - 150 + i * 100));
    }

    mainMenu[0].setFillColor(Color::Blue); // Selección inicial
    menuSelected = 0;
}

Menu::~Menu() {}

void Menu::moveUp() {
    if (menuSelected - 1 >= 0) {
        mainMenu[menuSelected].setFillColor(Color::White);
        menuSelected--;
        mainMenu[menuSelected].setFillColor(Color::Blue);
    }
}

void Menu::moveDown() {
    if (menuSelected + 1 < Max_main_menu) {
        mainMenu[menuSelected].setFillColor(Color::White);
        menuSelected++;
        mainMenu[menuSelected].setFillColor(Color::Blue);
    }
}

void Menu::draw(RenderWindow& window) {
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }
}
