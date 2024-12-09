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
    
}



//Constructor & Destructor
Game:: Game()
{
    this->initVariables();
    this->initWindow();
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


//Funtions
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
}
void Game::render()
{
    //Render objects
    this->window->clear(sf::Color(255, 0, 0, 255) );

//Draw game object

    this->window->display();
}


