#pragma once
#include "Music.h"

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
