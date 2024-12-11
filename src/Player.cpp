#include "Player.h"


void Player::initVariables()
{
    this->movementSpeed = 5.f;//Velocidad del jugador 
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
    this->sprite.setScale(0.5f, 0.5f); // Ajustar el tamaño del sprite (opcional)
    this->sprite.setPosition(100.f, 250.f); // Posición inicial
}

Player::Player(float x, float y)
{
    this->initVariables();
    this->initTexture();
    this->initSprite();
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
        this->sprite.move(-this->movementSpeed, 0.f);
    } 
    //Right
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->sprite.move(this->movementSpeed, 0.f);
    } 
    //Up
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->sprite.move(0.f , -this->movementSpeed);
    } 
    //Down
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->sprite.move(0.f , this->movementSpeed);
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


void Player::update(const sf::RenderTarget* target)
{
    this->updateInput();
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
