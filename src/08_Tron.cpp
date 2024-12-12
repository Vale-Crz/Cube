#include "Menu.h"
#include "Game.h"
#include "Audio.h"

using namespace sf;

int main() {
    // Ventana principal
    RenderWindow window(VideoMode(960, 720), "Main Menu and Game");

    // Crear el menú
    Menu mainMenu(window.getSize().x, window.getSize().y);

    //Reproducir musica
    Audio audio;
    if (!audio.loadMusic("./assets/music/ParaMenu.MP3")) {
        return -1; // Salir si no se puede cargar el audio
    }
    audio.playMusic(); // Reproducir música al inicio

    // Bandera para controlar el estado del juego
    bool inGame = false;

    // Crear una instancia del juego (pero no inicializarlo hasta que sea necesario)
    Game* game = nullptr;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (!inGame) {
                // Controles del menú
                if (event.type == Event::KeyReleased) {
                    if (event.key.code == Keyboard::Up) {
                        mainMenu.moveUp();
                    } else if (event.key.code == Keyboard::Down) {
                        mainMenu.moveDown();
                    } else if (event.key.code == Keyboard::Enter) {
                        int selectedOption = mainMenu.getMenuPressed();
                        if (selectedOption == 0) {
                            // Opción "Play" seleccionada
                            inGame = true;
                            game = new Game(); // Inicializa el juego
                            audio.stopMusic();
                        } else if (selectedOption == 1) {
                            // Opción "Exit" seleccionada
                            window.close();
                        }
                    }
                }
            } else {
                // Controles del juego
                if (game->isRunning()) {
                    game->handleEvents();
                } else {
                    // Si el juego termina, volvemos al menú
                    inGame = false;
                    delete game;
                    game = nullptr;
                    audio.playMusic();
                }
            }
        }

        // Renderizar
        window.clear();
        if (!inGame) {
            // Mostrar menú
            mainMenu.draw(window);
        } else {
            // Ejecutar el bucle del juego
            if (game) {
                game->update();
                game->render();
            }
        }
        window.display();
    }

    // Limpieza de memoria
    if (game) {
        delete game;
    }

    return 0;
}