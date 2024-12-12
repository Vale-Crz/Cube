#pragma once
#include "Menu.hpp"


class Player
{
    private:
        sf::Sprite sprite;
        sf::Texture textureSheet;
        sf::IntRect currentFrame;
        bool moving;
        float movementSpeed = 3.f;

        void initVariables();
        void initTexture();
        void initSprite(); 
        void initAnimations();
        sf::Clock animationTimer;

        

    public:
        Player(float x = 0.f, float y = 0.f);
        virtual ~Player();

        void updateAnimatios();
        void updateInput();
        void updateWindowBoundCollision(const sf::RenderTarget* target);
        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        sf::FloatRect getBounds() const;

};

