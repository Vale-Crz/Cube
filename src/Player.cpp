#include "Player.h"


void Player::initVariables()
{
    this->moving = false; 
}


void Player::initTexture()
{
    if (!this->textureSheet.loadFromFile("assets/images/BlueBallSpriteTest.png")) { // Ruta a tu imagen
        std::cerr << "ERROR::PLAYER::Could not load the player sheet" << std::endl;
    }
}

void Player::initSprite()
{
    //Set the exture to the sprite
    this->sprite.setTexture(this->textureSheet);

    this->currentFrame = sf::IntRect(0, 0, 30, 30);

    this->sprite.setTextureRect((this->currentFrame));
    this->sprite.setScale(1.f, 1.f); // Ajustar el tamaño del sprite (opcional)
    this->sprite.setPosition(100.f, 250.f); // Posición inicial
}

void Player::initAnimations()
{
    this->animationTimer.restart();
}

Player::Player(float x, float y)
{
    this->initVariables();
    this->initVariables();
    this->initTexture();
    this->initSprite();
    this->initAnimations();
}

Player::~Player()
{}

void Player::updateInput()
{
    this->moving = false;
    //Left
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->sprite.move(-this->movementSpeed, 0.f);
        this->moving = true;
    } 
    //Right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite.move(this->movementSpeed, 0.f);
        this->moving = true;
    } 
    //Up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f , -this->movementSpeed);
        this->moving = true;
    } 
    //Down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite.move(0.f , this->movementSpeed);
        this->moving = true;
    } 
}

void Player::updateWindowBoundCollision(const sf::RenderTarget * target)
{
    //Left 
    sf::FloatRect playerBounds = this->sprite.getGlobalBounds();
    if (playerBounds.left <= 0.f)
        this->sprite.setPosition(0.f, playerBounds.top);
    //Right
    if(playerBounds.left + playerBounds.width >= target->getSize().x)
        this->sprite.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
    //Top
    if (playerBounds.top <= 0.f)
        this->sprite.setPosition(playerBounds.left , 0.f);
    //Bottom
    if(playerBounds.top + playerBounds.height >= target->getSize().y)
        this->sprite.setPosition(playerBounds.left, target->getSize().y - playerBounds.height);
}

void Player::updateAnimatios()
{
    if(this->animationTimer.getElapsedTime().asSeconds() >= 0.5f)
    {
            if(this->moving == false)//IDLE animation
        {
                this->currentFrame.left +=  32.f;
                if(this->currentFrame.left >= 96.f)
                    this->currentFrame.left = 0;
        }

        this->animationTimer.restart();
        this->sprite.setTextureRect(this->currentFrame);
    }
}


void Player::update(const sf::RenderTarget* target)
{
    this->updateInput();
    this->updateAnimatios();
    //Window bounds collision
    this->updateWindowBoundCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}


sf::FloatRect Player::getBounds() const
{
    return this->sprite.getGlobalBounds();
}
