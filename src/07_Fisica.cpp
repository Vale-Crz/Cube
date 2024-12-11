#include "Game.h"
#include <cstdlib>
#include <ctime>


Game::Game() 
    : window(sf::VideoMode(800, 600), "Bounce Ball Game"), score(0), gameOver(false), player(100.f, 250.f)
{
    window.setFramerateLimit(144);
    


    // Inicializar la meta
    goal.setSize(sf::Vector2f(150.f, 25.f)); // Tamaño de la meta
    goal.setFillColor(sf::Color::Blue); // Color de la meta
    goal.setPosition(325.f, 0.f); // Posición de la meta

    // Crear plataformas, coleccionables y obstáculos
    createPlatforms();
    createCollectibles();
    createObstacles();

    this->score = 0;
    this->health = 3;

    // Inicializar fuentes y texto
    initFonts();
    initText();

}

Game::~Game() {}

void Game::initGame() 
{
    gameOver = false;
    
    createPlatforms();
    createCollectibles();
    createObstacles();

    // Reiniciar puntaje y salud
    score = 0;
    health = 3;

    // Actualizar texto inicial
    updateText();
}

void Game::resetGame() {
    initGame();
}

bool Game::isRunning() const {
    return window.isOpen();
}

void Game::handleEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::updateText() {
    std::stringstream ss;

    // Ajustar los valores mostrados en la interfaz gráfica
    ss << "Score: " << this->score << "\n"
       << "Health: " << this->health << "\n";

    // Actualizar el texto
    this->uiText.setString(ss.str());
}

void Game::renderText(sf::RenderTarget& target) {
    // Dibujar el texto actualizado en el objetivo de renderizado
    target.draw(this->uiText);
}

void Game::update() {
    if (gameOver) return;

    //Actualizacion jugador 
    player.update(&window);

    // Comprobar colisiones con plataformas, coleccionables y obstáculos
    checkCollisions();

    // Fin del juego si la salud se agota
    if (health <= 0) {
        gameOver = true;
    }

    // Actualizar texto dinámico
    updateText();
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (gameOver) {
        std::cout << "Game Over! Score: " << score << std::endl;
        window.close();
        return;
    }

    // Dibujar elementos del juego
    window.draw(goal);
    player.render(&window);
    for (const auto& platform : platforms) {
        window.draw(platform);
    }
    for (const auto& collectible : collectibles) {
        window.draw(collectible);
    }
    for (const auto& obstacle : obstacles) {
        window.draw(obstacle);
    }

    // Dibujar texto de la interfaz
    renderText(window);

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

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int numberOfCollectibles = 20;
    for (int i = 0; i < numberOfCollectibles; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - 10));
        float y = static_cast<float>(std::rand() % (window.getSize().y - 10));
        collectible.setPosition(x, y);
        collectibles.push_back(collectible);
    }
}

void Game::createObstacles() {
    obstacles.clear();
    sf::RectangleShape obstacle(sf::Vector2f(50.f, 10.f));
    obstacle.setFillColor(sf::Color::Red);

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    int numberOfObstacles = 10;
    for (int i = 0; i < numberOfObstacles; ++i) {
        float x = static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(obstacle.getSize().x)));
        float y = static_cast<float>(std::rand() % (window.getSize().y - static_cast<int>(obstacle.getSize().y)));

        obstacle.setPosition(x, y);
        obstacles.push_back(obstacle);
    }
}

void Game::checkCollisions() {
    // Colisiones con plataformas
    for (const auto& platform : platforms) {
        if (player.getBounds().intersects(platform.getGlobalBounds())) {
            // Puedes manejar el rebote o la lógica correspondiente aquí
            std::cout << "Rebote en plataforma" << std::endl;
        }
    }

    // Colisión con la meta
    if (player.getBounds().intersects(goal.getGlobalBounds())) {
        std::cout << "¡Has alcanzado la meta! ¡Felicidades!" << std::endl;
        resetGame();
    }

    // Colisiones con coleccionables
    for (size_t i = 0; i < collectibles.size(); ++i) {
        if (player.getBounds().intersects(collectibles[i].getGlobalBounds())) {
            collectibles.erase(collectibles.begin() + i);
            score += 10; // Incrementa el puntaje
            break;
        }
    }

    // Colisiones con obstáculos
    for (size_t i = 0; i < obstacles.size(); ++i) {
        if (player.getBounds().intersects(obstacles[i].getGlobalBounds())) {
            health -= 1; // Disminuir salud
            obstacles.erase(obstacles.begin() + i);
            break;
        }
    }
}

void Game::initFonts() {
    if (!font.loadFromFile("assets/fonts/Ring.ttf")) {
        std::cerr << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
    }
}

void Game::initText() {
    uiText.setFont(this->font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(10.f, 10.f); // Esquina superior izquierda
    uiText.setString("Score: 0\nHealth: 3");
}


