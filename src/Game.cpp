#include "Game.h"

//Private functions
void Game::initVariables()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Ball Bounce Animation", sf::Style::Titlebar | sf::Style::Close );
    
    this->window->setFramerateLimit(144);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f); 
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));  
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Green);
    this->enemy.setOutlineThickness(1.f);



}

//Constructor & Destructor
Game:: Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game ::~Game()
{
    delete this->window;
}

//Accesors
const bool Game::running() const
{
    return this->window->isOpen();
}


// Funtions
void Game::pollEvents()
{
                while (this->window->pollEvent(this->event))
        {

            switch (this->event.type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;
            
            case sf::Event::KeyPressed:
                if(this->event.key.code == sf::Keyboard::Escape)
                this->window->close();
                break;

            default:
            break;


            }

        }
}

void Game::update()
{
    this->pollEvents();

    this->updateMousePositions();

}
void Game::render()
{
    //Render objects
    this->window->clear();

//Draw game object
    this->window->draw(this->enemy);

    this->window->display();
}

void Game::updateMousePositions()
{
    //Update mouse positions

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

}

void Game::spawnEnemy()
{
    
}