#pragma once
#include "Player.h"


class Game {
private:
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Jugador 
    Player player;

    sf::CircleShape ball;
    sf::Vector2f ballVelocity;

    sf::RectangleShape goal;

    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::CircleShape> collectibles;
    std::vector<sf::RectangleShape> obstacles;

    sf::Font font;
    sf::Text uiText;

    int health;
    unsigned points;
    int score;
    bool gameOver;

    void initGame();
    void resetGame();
    void checkCollisions();
    void createPlatforms();
    void createCollectibles();
    void createObstacles();
    void initFonts();
    void initText();

public:
    Game();
    virtual ~Game();

    bool isRunning() const;
    void handleEvents();
    void updateText();
    void renderText(sf::RenderTarget& target);
    void update();
    void render();
};
