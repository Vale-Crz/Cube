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

class Audio {
private:
    sf::Music music;

public:
    Audio();
    virtual ~Audio();
    bool loadMusic(const std::string& filename);
    void playMusic();
    void stopMusic();
};
