/// Code written by Bordeanu Calin
/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <windows.h>

#define BLOCKS 90
#define blockSize 7

const int WIDTH = BLOCKS * blockSize;
const int HEIGHT = BLOCKS * blockSize;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake");

bool gameOver = false;

int redScore = 0;
int blueScore = 0;

class Player
{
public:
    std::vector<sf::RectangleShape> body;

    sf::Color defaultColor;
    sf::Vector2f dir = {0, -1};

    void Move()
    {
        sf::RectangleShape &head = body[0];

        int x = head.getPosition().x/blockSize;
        int y = head.getPosition().y/blockSize;

        if(dir.x==0 && dir.y==-1){
            head.setPosition({x*blockSize, (y-1)*blockSize});
        }
        if(dir.x==0 && dir.y==1){
            head.setPosition({x*blockSize, (y+1)*blockSize});
        }
        if(dir.x==1 && dir.y==0){
            head.setPosition({(x+1)*blockSize, y*blockSize});
        }
        if(dir.x==-1 && dir.y==0){
            head.setPosition({(x-1)*blockSize, y*blockSize});
        }
    }

    void AddTail()
    {
        sf::RectangleShape newPart;
        newPart.setFillColor(defaultColor);
        newPart.setSize({blockSize, blockSize});

        sf::RectangleShape head = body[0];

        int x = head.getPosition().x;
        int y = head.getPosition().y;

        newPart.setPosition({x, y});

        body.push_back(newPart);
    }

    void CheckBounds()
    {
        sf::RectangleShape &head = body[0];

        int x = head.getPosition().x/blockSize;
        int y = head.getPosition().y/blockSize;

        if(x>=BLOCKS) x = 0;
        if(x<0) x = BLOCKS;
        if(y>=BLOCKS) y = 0;
        if(y<0) y = BLOCKS;

        x*=blockSize;
        y*=blockSize;

        head.setPosition({x, y});
    }

    void CheckSelfCollision(int &enemyScore)
    {
        for(int i = 1; i<body.size(); ++i){
            int x1 = body[0].getPosition().x;
            int x2 = body[i].getPosition().x;

            int y1 = body[0].getPosition().y;
            int y2 = body[i].getPosition().y;

            if(x1==x2 && y1==y2){
                gameOver = true;
                ++enemyScore;
                std::cout << "Press 'R' to go to the next round";
            }
        }
    }

    void CheckPlayerCollision(Player p, int &enemyScore)
    {
        for(int i = 0; i<p.body.size(); ++i){
            int x1 = body[0].getPosition().x;
            int x2 = p.body[i].getPosition().x;

            int y1 = body[0].getPosition().y;
            int y2 = p.body[i].getPosition().y;

            if(x1==x2 && y1==y2){
                gameOver = true;
                ++enemyScore;
                std::cout << "Press 'R' to go to the next round";
            }
        }
    }

    void ChangeDir(bool useWASD)
    {
        if(!useWASD)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir.y!=1)     dir = {0, -1};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir.y!=-1)  dir = {0, 1};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir.x!=1)   dir = {-1, 0};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir.x!=-1) dir = {1, 0};
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && dir.y!=1)  dir = {0, -1};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && dir.y!=-1) dir = {0, 1};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dir.x!=1)  dir = {-1, 0};
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dir.x!=-1) dir = {1, 0};
        }
    }

    void Draw()
    {
        for(int i = 0; i<body.size(); ++i)
            window.draw(body[i]);
    }

    void Update(Player enemy, int &enemyScore)
    {
        Move();
        CheckSelfCollision(enemyScore);
        CheckPlayerCollision(enemy, enemyScore);
        AddTail();
        CheckBounds();
    }

    Player(sf::Color Color, sf::Vector2f Position)
    {
        sf::RectangleShape head;

        defaultColor = Color;
        head.setFillColor(Color);
        head.setSize({blockSize, blockSize});
        head.setPosition(Position);
        body.push_back(head);
    }
};

int main()
{
    gameOver = false;
    system("cls");

    Player p1(sf::Color::Red, {WIDTH/4, HEIGHT/2});
    Player p2(sf::Color::Blue, {WIDTH-WIDTH/4, HEIGHT/2});

    sf::Clock clock;
    float t = 0;

    std::cout << "Red:  " << redScore  << '\n';
    std::cout << "Blue: " << blueScore << '\n';

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed) window.close();
            if(gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::R)) main();
        }

        sf::Time time = clock.restart();
        t+=time.asSeconds();

        if(!gameOver)
        {
            p1.ChangeDir(true);
            p2.ChangeDir(false);
            if(t>0.03){
                t = 0;
                p1.Update(p2, blueScore);
                p2.Update(p1, redScore);
            }
        }

        window.clear(sf::Color(0, 0, 0));
        p1.Draw();
        p2.Draw();
        window.display();
    }
}*/



/* BOUNCE BALL
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

int main() {
    // Configuración de la ventana
    sf::RenderWindow window(sf::VideoMode(800, 600), "Bounce Ball Game");
    window.setFramerateLimit(60);

    // Configuración de la pelota
    sf::CircleShape ball(10.f); // Radio de 10 píxeles
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400.f, 300.f);

    // Velocidad de la pelota
    sf::Vector2f ballVelocity(5.f, 4.f);

    // Configuración de la paleta
    sf::RectangleShape paddle(sf::Vector2f(100.f, 20.f));
    paddle.setFillColor(sf::Color::Blue);
    paddle.setPosition(350.f, 550.f);

    // Velocidad de la paleta
    float paddleSpeed = 8.f;

    while (window.isOpen()) {
        // Manejo de eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento de la paleta
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0)
            paddle.move(-paddleSpeed, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x + paddle.getSize().x < window.getSize().x)
            paddle.move(paddleSpeed, 0.f);

        // Movimiento de la pelota
        ball.move(ballVelocity);

        // Rebotar en los bordes de la ventana
        if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x)
            ballVelocity.x = -ballVelocity.x;
        if (ball.getPosition().y <= 0)
            ballVelocity.y = -ballVelocity.y;

        // Rebotar en la paleta
        if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
            ballVelocity.y = -ballVelocity.y;

        // Reiniciar la pelota si toca la parte inferior
        if (ball.getPosition().y + ball.getRadius() * 2 >= window.getSize().y) {
            ball.setPosition(400.f, 300.f);
            ballVelocity = sf::Vector2f(5.f, 4.f);
        }

        // Renderizado
        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(paddle);
        window.display();
    }

    return 0;
}*/

/*
#include "Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Bounce Ball Game"), score(0), gameOver(false) {
    window.setFramerateLimit(60);
    
    // Inicializar la pelota
    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400.f, 300.f);
    ballVelocity = sf::Vector2f(0.f, 0.f);

    // Inicializar la paleta del jugador
    player.setSize(sf::Vector2f(100.f, 20.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(350.f, 550.f);

    // Crear plataformas, coleccionables y obstáculos
    createPlatforms();
    createCollectibles();
    createObstacles();
}

Game::~Game() {}

void Game::initGame() {
    score = 0;
    gameOver = false;
    ball.setPosition(400.f, 300.f);
    ballVelocity = sf::Vector2f(0.f, 0.f);
    createPlatforms();
    createCollectibles();
    createObstacles();
}

void Game::resetGame() {
    initGame();
}

bool Game::isRunning() const {
    return window.isOpen();
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // Movimiento del jugador
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
        player.move(-8.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x + player.getSize().x < window.getSize().x)
        player.move(8.f, 0.f);

    // Salto de la pelota
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ballVelocity.y == 0)
        ballVelocity.y = -12.f;
}

void Game::update() {
    if (gameOver) return;

    // Actualizar posición de la pelota
    ballVelocity.y += 0.5f; // Gravedad
    ball.move(ballVelocity);

    // Colisiones con los bordes de la ventana
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x)
        ballVelocity.x = -ballVelocity.x;
    if (ball.getPosition().y <= 0)
        ballVelocity.y = -ballVelocity.y;

    // Si la pelota cae
    if (ball.getPosition().y >= window.getSize().y) {
        gameOver = true;
    }

    // Comprobar colisiones
    checkCollisions();
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (gameOver) {
        // Mensaje de Game Over (texto opcional)
        std::cout << "Game Over! Score: " << score << std::endl;
        window.close();
        return;
    }

    window.draw(ball);
    window.draw(player);

    for (const auto& platform : platforms)
        window.draw(platform);

    for (const auto& collectible : collectibles)
        window.draw(collectible);

    for (const auto& obstacle : obstacles)
        window.draw(obstacle);

    window.display();
}

void Game::createPlatforms() {
    platforms.clear();
    sf::RectangleShape platform(sf::Vector2f(100.f, 10.f));
    platform.setFillColor(sf::Color::Green);

    platform.setPosition(200.f, 400.f);
    platforms.push_back(platform);

    platform.setPosition(500.f, 300.f);
    platforms.push_back(platform);

    platform.setPosition(300.f, 200.f);
    platforms.push_back(platform);
}

void Game::createCollectibles() {
    collectibles.clear();
    sf::CircleShape collectible(5.f);
    collectible.setFillColor(sf::Color::Yellow);

    collectible.setPosition(210.f, 390.f);
    collectibles.push_back(collectible);

    collectible.setPosition(510.f, 290.f);
    collectibles.push_back(collectible);

    collectible.setPosition(310.f, 190.f);
    collectibles.push_back(collectible);
}

void Game::createObstacles() {
    obstacles.clear();
    sf::RectangleShape obstacle(sf::Vector2f(50.f, 10.f));
    obstacle.setFillColor(sf::Color::Red);

    obstacle.setPosition(400.f, 500.f);
    obstacles.push_back(obstacle);
}

void Game::checkCollisions() {
    // Colisión con plataformas
    for (const auto& platform : platforms) {
        if (ball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            ballVelocity.y = -10.f;
        }
    }

    // Colisión con coleccionables
    for (size_t i = 0; i < collectibles.size(); ++i) {
        if (ball.getGlobalBounds().intersects(collectibles[i].getGlobalBounds())) {
            collectibles.erase(collectibles.begin() + i);
            score += 10;
            break;
        }
    }

    // Colisión con obstáculos
    for (const auto& obstacle : obstacles) {
        if (ball.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
            gameOver = true;
            break;
        }
    }
}*/

#include "Ball.hpp"

int main() {
    Game game; // Clase principal del juego

    // Bucle principal del juego
    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    return 0;
}
