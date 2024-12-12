#include "Music.h"

Musica::Musica()
{
}

Musica::~Musica()
{
}

bool Musica::loadBackgroundMusic(const std::string &filename)
{
    if (!bgmusic.openFromFile(filename)) {
        std::cerr << "ERROR: Music file could not be loaded!" << std::endl;
        return false;
    }
    return true;
}

void Musica::playBackgroundMusic()
{
    bgmusic.setLoop(true); // Configura la música para que se reproduzca en bucle
    bgmusic.play();
}

void Musica::stopBackgroundMusic()
{
    bgmusic.stop();
}
