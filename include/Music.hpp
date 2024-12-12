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

class Musica {
private:
    sf::Music bgmusic;

public:
    Musica();
    virtual ~Musica();
    bool loadBackgroundMusic(const std::string& filename);
    void playBackgroundMusic();
    void stopBackgroundMusic();
};
