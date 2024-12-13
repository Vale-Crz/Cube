#include "Music.hpp"

Musica::Musica()
{
}
Musica::~Musica()
{
}
bool Musica::loadBackgroundMusic(const std::string &filename)
{
    std::cout << "Trying to load music: " << filename << std::endl; 
    if (!bgmusic.openFromFile(filename)) {
        std::cerr << "ERROR: Music file could not be loaded! File: " << filename << std::endl;
        return false;
    }
    std::cout << "Music file was loaded: " << filename << std::endl;
    return true;
}
void Musica::playBackgroundMusic()
{
    bgmusic.setLoop(true); 
    bgmusic.play();
}
void Musica::stopBackgroundMusic()
{
    bgmusic.stop();
}
