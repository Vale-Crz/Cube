#include "Audio.hpp"

Audio::Audio() {}
Audio::~Audio() {}
bool Audio::loadMusic(const std::string& filename) 
{
    std::cout << "Trying to load: " << filename << std::endl; 
    if (!music.openFromFile(filename)) {
        std::cerr << "ERROR: Music file could not be loaded! Archivo: " << filename << std::endl;
        return false;
    }
    std::cout << "Music was loaded: " << filename << std::endl;
    return true;
}

void Audio::playMusic() 
{
    music.setLoop(true); 
    music.play();
}

void Audio::stopMusic() 
{
    music.stop();
}

