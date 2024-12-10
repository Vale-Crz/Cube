#include "Ball.hpp"
#include <iostream>

#include <cstdlib>
#include <ctime>

Game::Game() : window(sf::VideoMode(800, 600), "Bounce Ball Game"), score(0), gameOver(false) {
    window.setFramerateLimit(60);

    // Inicializar la pelota
    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(500.f, 500.f);  // Ajustado para empezar más a la izquierda
    ballVelocity = sf::Vector2f(0.f, 0.f);  // Velocidad inicial de la pelota

    // Inicializar la meta
    goal.setSize(sf::Vector2f(150.f, 25.f));  // Tamaño de la meta
    goal.setFillColor(sf::Color::Blue);     // Color de la meta
    goal.setPosition(350.f, 0.f);         // Posición de la meta

    // Crear plataformas, coleccionables y obstáculos
    createPlatforms();
    createCollectibles();
    createObstacles();


}

Game::~Game() {}

void Game::initGame() {
    score = 0;
    gameOver = false;
    ball.setPosition(100.f, 250.f);  // Posición inicial de la pelota ajustada
    ballVelocity = sf::Vector2f(0.f, 0.f);  // Velocidad inicial
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
    // Controlar la dirección de la pelota con las flechas
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        ballVelocity.x = -2.f;  // Reducido a 2 para hacer el movimiento más lento
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        ballVelocity.x = 2.f;  // Reducido a 2 para hacer el movimiento más lento
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        ballVelocity.y = -2.f;  // Reducido a 2 para hacer el movimiento más lento
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        ballVelocity.y = 2.f;  // Reducido a 2 para hacer el movimiento más lento
    }

/*
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // Movimiento de la bola en todas las direcciones
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && ball.getPosition().x > 0) {
        ball.move(-5.f, 0.f);  // Mover hacia la izquierda
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && ball.getPosition().x + ball.getRadius() * 2 < window.getSize().x) {
        ball.move(5.f, 0.f);  // Mover hacia la derecha
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ball.getPosition().y > 0) {
        ball.move(0.f, -5.f);  // Mover hacia arriba
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ball.getPosition().y + ball.getRadius() * 2 < window.getSize().y) {
        ball.move(0.f, 5.f);  // Mover hacia abajo
    }
    */
}

void Game::update() {
    if (gameOver) return;

    // Mover la pelota según su velocidad
    ball.move(ballVelocity);

    // Comprobar si la pelota ha salido de la ventana (se acaba el juego)
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x ||
        ball.getPosition().y <= 0 || ball.getPosition().y + ball.getRadius() * 2 >= window.getSize().y) {
        gameOver = true;
    }

    // Comprobar colisiones con plataformas, coleccionables y obstáculos
    checkCollisions();
}

void Game::render() {

    window.clear(sf::Color::Black);  // Limpiar la ventana con un color negro

    if (gameOver) {
        std::cout << "Game Over! Score: " << score << std::endl;
        window.close();  // Cierra la ventana si el juego termina
        return;
    }

    // Dibujar la meta
    window.draw(goal);

    // Dibujar la pelota
    window.draw(ball);

    // Dibujar plataformas
    for (const auto& platform : platforms) {
        window.draw(platform);
    }

    // Dibujar coleccionables
    for (const auto& collectible : collectibles) {
        window.draw(collectible);
    }

    // Dibujar obstáculos
    for (const auto& obstacle : obstacles) {
        window.draw(obstacle);
    }

    // Mostrar todo en la ventana
    window.display();


}

void Game::createPlatforms() {
    platforms.clear();
    sf::RectangleShape platform(sf::Vector2f(100.f, 10.f));
    platform.setFillColor(sf::Color::Green);

    // Definimos plataformas en diferentes posiciones
    platform.setPosition(200.f, 400.f);
    platforms.push_back(platform);

    platform.setPosition(500.f, 300.f);
    platforms.push_back(platform);

    platform.setPosition(300.f, 200.f);
    platforms.push_back(platform);
}

void Game::createCollectibles() {
    collectibles.clear();
    sf::CircleShape collectible(5.f);  // Tamaño del coleccionable
    collectible.setFillColor(sf::Color::Yellow);

    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Semilla para números aleatorios

    int numberOfCollectibles = 20;  // Cambia este valor para aumentar la cantidad
    for (int i = 0; i < numberOfCollectibles; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 10));  // Evitar bordes
        float y = static_cast<float>(std::rand() % (window.getSize().y - 10));
        collectible.setPosition(x, y);
        collectibles.push_back(collectible);
    }
}

void Game::createObstacles() {

    obstacles.clear();  // Limpiar cualquier obstáculo existente
    sf::RectangleShape obstacle(sf::Vector2f(50.f, 10.f));  // Tamaño del obstáculo
    obstacle.setFillColor(sf::Color::Red);

    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Semilla para números aleatorios

    int numberOfObstacles = 10;  // Número de obstáculos que quieres
    for (int i = 0; i < numberOfObstacles; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(obstacle.getSize().x)));
        float y = static_cast<float>(std::rand() % (window.getSize().y - static_cast<int>(obstacle.getSize().y)));

        // Coloca el obstáculo en la posición generada
        obstacle.setPosition(x, y);

        // Opcional: Evitar que los obstáculos estén cerca de la posición inicial de la pelota o la meta
        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect goalBounds = goal.getGlobalBounds();
        sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();

        if (obstacleBounds.intersects(ballBounds) || obstacleBounds.intersects(goalBounds)) {
            --i;  // Si hay intersección, intenta otra posición
            continue;
        }

        // Agregar el obstáculo a la lista
        obstacles.push_back(obstacle);
    }
}

void Game::checkCollisions() {
    // Colisiones con plataformas
    for (const auto& platform : platforms) {
        if (ball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            ballVelocity.y = -10.f;  // Rebote con la plataforma
        }


    //Cambio
    // Colisión con la meta
    if (ball.getGlobalBounds().intersects(goal.getGlobalBounds())) {
    std::cout << "¡Has alcanzado la meta! ¡Felicidades!" << std::endl;
    resetGame();  // Reiniciar el juego
}
    }

    // Colisiones con coleccionables
    for (size_t i = 0; i < collectibles.size(); ++i) {
        if (ball.getGlobalBounds().intersects(collectibles[i].getGlobalBounds())) {
            collectibles.erase(collectibles.begin() + i);  // Eliminamos el coleccionable
            score += 10;  // Sumamos puntos
            break;
        }
    }

    // Colisiones con obstáculos
    for (const auto& obstacle : obstacles) {
        if (ball.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
            gameOver = true;  // Fin del juego si hay colisión con un obstáculo
            break;
        }
    }
}


/*#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

int main()
{
    int fuerza = 1;

    // Crear una ventana de SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Ejemplo de Fisica con Box2D y SFML");

    // Crear un mundo de Box2D
    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Crear un suelo estático
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(400, 500.0f); // Posición del centro del cuerpo
    b2Body* cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    // Crear una forma rectangular
    b2PolygonShape formaSuelo;
    int boxWidth = 600; // 600 pixeles de ancho
    int boxHeight = 10; // 10 pixeles de alto
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(400.0f, 300.0f);
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma circular
    b2CircleShape formaBola;
    formaBola.m_radius = 25.0f;

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    cuerpoBola->CreateFixture(&fixtureBolaDef);

    // Bucle principal del juego
    while (ventana.isOpen())
    {
        // Procesar eventos
        sf::Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == sf::Event::Closed)
                ventana.close();
        }

        // Controlar la bola con el teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(-fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(fuerza, 0), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, -fuerza), cuerpoBola->GetWorldCenter(), true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            cuerpoBola->ApplyLinearImpulse(b2Vec2(0, fuerza), cuerpoBola->GetWorldCenter(), true);

        // Actualizar el mundo de Box2D
        // Ajustar el valor de 1.0 / 60.0 para cambiar la velocidad de la simulación física
        mundo.Step(1.0f / 60.0f, 6, 2);
        cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;

        // Limpiar la ventana
        ventana.clear();

        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x, 
            cuerpoSuelo->GetPosition().y);
        ventana.draw(suelo);

        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x, 
            cuerpoBola->GetPosition().y);
        ventana.draw(bola);

        // Mostrar la ventana
        ventana.display();
    }

    return 0;
}*/



/*
#include "Ball.hpp"
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
}
*/










/*
#include "Ball.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 600), "Bounce Ball Game"), score(0), gameOver(false) {
    window.setFramerateLimit(60);
    
    // Inicializar la pelota
    ball.setRadius(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(400.f, 300.f);
    ballVelocity = sf::Vector2f(0.f, 0.f);  // Velocidad inicial de la pelota

    // Inicializar la paleta del jugador
    player.setSize(sf::Vector2f(100.f, 20.f));
    player.setFillColor(sf::Color::Blue);
    player.setPosition(350.f, 550.f);  // Posición inicial

    // Crear plataformas, coleccionables y obstáculos
    createPlatforms();
    createCollectibles();
    createObstacles();
}

Game::~Game() {}

void Game::initGame() {
    score = 0;
    gameOver = false;
    ball.setPosition(400.f, 300.f);  // Posición inicial de la pelota
    ballVelocity = sf::Vector2f(0.f, 0.f);  // Velocidad inicial
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

    // Movimiento del jugador (izquierda/derecha)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player.getPosition().x > 0)
        player.move(-8.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player.getPosition().x + player.getSize().x < window.getSize().x)
        player.move(8.f, 0.f);

    // Salto de la pelota (cuando está en el suelo)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ballVelocity.y == 0)
        ballVelocity.y = -12.f;  // Velocidad inicial hacia arriba para el salto
}

void Game::update() {
    if (gameOver) return;

    // Gravedad que afecta la pelota
    ballVelocity.y += 0.5f;  // Incremento en el eje Y para simular la gravedad

    // Mover la pelota según su velocidad
    ball.move(ballVelocity);

    // Colisiones con los bordes de la ventana (rebote de la pelota)
    if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x)
        ballVelocity.x = -ballVelocity.x;  // Rebote horizontal
    if (ball.getPosition().y <= 0)
        ballVelocity.y = -ballVelocity.y;  // Rebote vertical en el borde superior

    // Si la pelota cae fuera de la ventana, se acaba el juego
    if (ball.getPosition().y >= window.getSize().y) {
        gameOver = true;
    }

    // Comprobar colisiones con plataformas, coleccionables y obstáculos
    checkCollisions();
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (gameOver) {
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

    // Definimos plataformas en diferentes posiciones
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

    // Definimos coleccionables en las plataformas
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

    // Definimos obstáculos en la escena
    obstacle.setPosition(400.f, 500.f);
    obstacles.push_back(obstacle);
}

void Game::checkCollisions() {
    // Colisiones con plataformas
    for (const auto& platform : platforms) {
        if (ball.getGlobalBounds().intersects(platform.getGlobalBounds())) {
            ballVelocity.y = -10.f;  // Rebote con la plataforma
        }
    }

    // Colisiones con coleccionables
    for (size_t i = 0; i < collectibles.size(); ++i) {
        if (ball.getGlobalBounds().intersects(collectibles[i].getGlobalBounds())) {
            collectibles.erase(collectibles.begin() + i);  // Eliminamos el coleccionable
            score += 10;  // Sumamos puntos
            break;
        }
    }

    // Colisiones con obstáculos
    for (const auto& obstacle : obstacles) {
        if (ball.getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
            gameOver = true;  // Fin del juego si hay colisión con un obstáculo
            break;
        }
    }
}
*/