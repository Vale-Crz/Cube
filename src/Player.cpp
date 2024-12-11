#include "Player.h"

void Player::initVariables()
{
    this->movementSpeed = 10.f;
}

void Player::initShape()
{
    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::Red);
}

Player::Player(float x, float y)
{
    ball.setPosition(100.f, 250.f);//Specific position

    this->initVariables();
    this->initShape();
}

Player::~Player()
{
}



void Player::updateInput()
{
    //Keybord input 
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->ball.move(-this->movementSpeed, 0.f);
    } 

    //Right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->ball.move(this->movementSpeed, 0.f);
    } 
    
    //Up
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->ball.move(0.f , -this->movementSpeed);
    } 

    //Down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->ball.move(0.f , this->movementSpeed);
    } 
}

void Player::updateWindowBoundCollision(const sf::RenderTarget * target)
{
    //Left 
    sf::FloatRect playerBounds = this->ball.getGlobalBounds();
    if (playerBounds.left <= 0.f)
        this->ball.setPosition(0.f, playerBounds.top);
    //Right
    if(playerBounds.left + playerBounds.width >= target->getSize().x)
        this->ball.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
    //Top
    if (playerBounds.top <= 0.f)
        this->ball.setPosition(playerBounds.left , 0.f);
    //Bottom
    if(playerBounds.top + playerBounds.height >= target->getSize().y)
        this->ball.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);


}

void Player::update(const sf::RenderTarget* target)
{
    this->updateInput();

    //Window bounds collision
    this->updateWindowBoundCollision(target);

}

void Player::render(sf::RenderTarget *target)
{
    target->draw(this->ball);
}

sf::FloatRect Player::getBounds() const {
    return this->ball.getGlobalBounds();
}