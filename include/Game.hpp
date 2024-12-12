#pragma once
#include "Player.hpp"


class Game {
private:
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    sf::Event event;
    sf::Text gameOverText;

    //Externos
    Player player;
    Musica gameMusic;

    sf::RectangleShape goal;
    std::vector<sf::CircleShape> collectibles;
    sf::Font font;
    sf::Text uiText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 


    int health;
    unsigned points;
    int score;
    bool gameOver;


    sf::Texture enemyTexture;
    std::vector<sf::Sprite> enemies;
    //std::vector<sf::RectangleShape> enemies;
    //sf::RectangleShape enemy;
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
    void resetGoalPosition();
    void resetGameElements();

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
