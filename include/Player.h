#pragma once
#include "Menu.h"


class Player
{
    private:
        sf::Sprite sprite;
        sf::Texture textureSheet;
        sf::IntRect currentFrame;
        float movementSpeed = 3.f;

        void initVariables();
        void initTexture();
        void initSprite(); 

        

    public:
        Player(float x = 0.f, float y = 0.f);
        virtual ~Player();

        void updateInput();
        void updateWindowBoundCollision(const sf::RenderTarget* target);
        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        sf::FloatRect getBounds() const;

};

