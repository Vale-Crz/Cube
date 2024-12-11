#pragma once
#include "Menu.h"


class Player
{
    private:
        sf::CircleShape ball;
        float movementSpeed = 5.f;

        void initVariables();
        void initShape();

    public:
        Player(float x = 0.f, float y = 0.f);
        virtual ~Player();

        void updateInput();
        void updateWindowBoundCollision(const sf::RenderTarget* target);
        void update(const sf::RenderTarget* target);
        void render(sf::RenderTarget* target);

        sf::FloatRect getBounds() const;

};