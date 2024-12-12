#include "Audio.h"

Audio::Audio() {}

Audio::~Audio() {}

bool Audio::loadMusic(const std::string& filename) 
{
    if (!music.openFromFile(filename)) {
        std::cerr << "ERROR: Music file could not be loaded!" << std::endl;
        return false;
    }
    return true;
}

void Audio::playMusic() 
{
    music.setLoop(true); // Configura la música para que se reproduzca en bucle
    music.play();
}

void Audio::stopMusic() 
{
    music.stop();
}

