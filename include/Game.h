#pragma once
#include "Player.h"


class Game {
private:
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;

    //Jugador 
    Player player;

    sf::RectangleShape goal;

    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::CircleShape> collectibles;


    sf::Font font;
    sf::Text uiText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 


    int health;
    unsigned points;
    int score;
    bool gameOver;

    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;

    void initGame();
    void resetGame();
    void checkCollisions();
    void createCollectibles();
    void initFonts();
    void initText();
    void initBackgroudd();
    void initEnemies();
    void spawnEnemy();
    void updateEnemies();
    void renderEnemies(sf::RenderTarget& target);




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
