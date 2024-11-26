/*
#include <chipmunk/chipmunk.h>

class Ball {
public:
    Ball(cpSpace* space, float radius, float mass, const cpVect& position) {
        cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
        body = cpSpaceAddBody(space, cpBodyNew(mass, moment));
        cpBodySetPosition(body, position);
        shape = cpSpaceAddShape(space, cpCircleShapeNew(body, radius, cpvzero));
        cpShapeSetFriction(shape, 0.7);
    }

    sf::CircleShape GetShape() {
        sf::CircleShape ballShape(20.0);
        cpVect ballPosition = cpBodyGetPosition(body);
        ballShape.setPosition(ballPosition.x, ballPosition.y);
        ballShape.setFillColor(sf::Color::Red);
        return ballShape;
    }

    ~Ball() {
        cpShapeFree(shape);
        cpBodyFree(body);
    }

    cpBody* getBody() {
        return body;
    }

private:
    int radius;
    cpBody* body;
    cpShape* shape;
};*/

#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Game {
public:
    Game();
    ~Game();

    // Métodos principales
    void handleEvents();
    void update();
    void render();

    bool isRunning() const;

private:
    sf::RenderWindow window;
    sf::CircleShape ball;
    sf::Vector2f ballVelocity;

    sf::RectangleShape player;
    std::vector<sf::RectangleShape> platforms;
    std::vector<sf::CircleShape> collectibles;
    std::vector<sf::RectangleShape> obstacles;

    int score;
    bool gameOver;

    // Métodos auxiliares
    void initGame();
    void resetGame();
    void checkCollisions();
    void createPlatforms();
    void createCollectibles();
    void createObstacles();
};

#endif
