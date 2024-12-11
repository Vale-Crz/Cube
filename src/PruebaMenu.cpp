#include <SFML/Graphics.hpp>
#include "Menu.h"

using namespace sf;

int main() {
    RenderWindow menuWindow(VideoMode(960, 720), "Main Menu", Style::Default);
    Menu mainMenu(menuWindow.getSize().x, menuWindow.getSize().y);

    while (menuWindow.isOpen()) {
        Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                menuWindow.close();
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Up) {
                    mainMenu.moveUp();
                } else if (event.key.code == Keyboard::Down) {
                    mainMenu.moveDown();
                } else if (event.key.code == Keyboard::Enter) {
                    int menuOption = mainMenu.getMenuPressed();

                    if (menuOption == 0) {
                        // Play
                        RenderWindow playWindow(VideoMode(960, 720), "Play");
                        while (playWindow.isOpen()) {
                            Event playEvent;
                            while (playWindow.pollEvent(playEvent)) {
                                if (playEvent.type == Event::Closed || 
                                    (playEvent.type == Event::KeyPressed && playEvent.key.code == Keyboard::Escape)) {
                                    playWindow.close();
                                }
                            }
                            playWindow.clear();
                            playWindow.display();
                        }
                    } else if (menuOption == 1) {
                        // Options
                        RenderWindow optionsWindow(VideoMode(960, 720), "Options");
                        while (optionsWindow.isOpen()) {
                            Event optionsEvent;
                            while (optionsWindow.pollEvent(optionsEvent)) {
                                if (optionsEvent.type == Event::Closed || 
                                    (optionsEvent.type == Event::KeyPressed && optionsEvent.key.code == Keyboard::Escape)) {
                                    optionsWindow.close();
                                }
                            }
                            optionsWindow.clear();
                            optionsWindow.display();
                        }
                    } else if (menuOption == 2) {
                        // About
                        RenderWindow aboutWindow(VideoMode(960, 720), "About");
                        while (aboutWindow.isOpen()) {
                            Event aboutEvent;
                            while (aboutWindow.pollEvent(aboutEvent)) {
                                if (aboutEvent.type == Event::Closed || 
                                    (aboutEvent.type == Event::KeyPressed && aboutEvent.key.code == Keyboard::Escape)) {
                                    aboutWindow.close();
                                }
                            }
                            aboutWindow.clear();
                            aboutWindow.display();
                        }
                    } else if (menuOption == 3) {
                        // Exit
                        menuWindow.close();
                    }
                }
            }
        }

        menuWindow.clear();
        mainMenu.draw(menuWindow);
        menuWindow.display();
    }

    return 0;
}
