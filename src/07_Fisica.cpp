#include "Game.h"
#include <cstdlib>
#include <ctime>


Game::Game() 
    : window(sf::VideoMode(800, 600), "Bounce Ball Game"), score(0), gameOver(false), player(100.f, 250.f)
{
    window.setFramerateLimit(144);
    std::srand(static_cast<unsigned>(std::time(nullptr)));// Semilla para la aleatoriedad

    // Inicializar la meta
    goal.setSize(sf::Vector2f(150.f, 25.f)); // Tamaño de la meta
    goal.setFillColor(sf::Color::Blue); // Color de la meta
    goal.setPosition(325.f, 0.f); // Posición de la meta

    // Crear coleccionables
    createCollectibles();
    this->score = 0;
    this->health = 5;

    // Inicializar gameOverText
    gameOverText.setFont(this->font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Game Over!");
    gameOverText.setPosition(200.f ,200.f);

    // Inicializar fuentes y texto
    initFonts();
    initText();
    initBackgroudd();
    initEnemies();
    
    if (gameMusic.loadBackgroundMusic("./assets/music/ParaJuego.MP3")) 
    {
        gameMusic.playBackgroundMusic();
    }

}

Game::~Game() 
{
    gameMusic.stopBackgroundMusic();
}

void Game::initGame() 
{
    gameOver = false;
    createCollectibles();
    // Reiniciar puntaje y salud
    score = 0;
    health = 5;
    // Actualizar texto inicial
    updateText();

    enemies.clear();
    enemySpawnTimer = 0.f;
}

void Game::resetGoalPosition() {
    float x = static_cast<float>(std::rand() % (window.getSize().x - static_cast<int>(goal.getSize().x)));
    float y = static_cast<float>(std::rand() % (window.getSize().y - static_cast<int>(goal.getSize().y)));
    goal.setPosition(x, y);
}
void Game::resetGameElements() {
    createCollectibles(); // Regenera las bonificaciones
    initEnemies();        // Regenera los obstáculos
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
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
                window.close(); 
            break;

        default:
            break;
        }
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

    // Actualización de enemigos
    updateEnemies();

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
    window.clear();

    if (gameOver) 
    {
        window.draw(backgroundSprite);
        window.draw(gameOverText); // Renderiza el texto de Game Over
        window.display();
        return; // Sal del método después de mostrar Game Over
    }

    // Dibujar elementos del juego
    window.draw(backgroundSprite);
    window.draw(goal);
    player.render(&window);

    for (const auto& collectible : collectibles) 
    {
        window.draw(collectible);
    }
    renderEnemies(window);

    // Dibujar texto de la interfaz
    renderText(window);

    window.display();
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

void Game::initEnemies() {
    
    enemy.setSize(sf::Vector2f(40.f, 40.f));
    enemySpawnTimerMax = 30.f;//Generador de enemigos
    enemySpawnTimer = enemySpawnTimerMax;
    maxEnemies = 15;//Cantidad en pantalla
}

void Game::spawnEnemy() {
    if (enemies.size() < maxEnemies) {
        sf::RectangleShape newEnemy(enemy);

        // Posicion aleatoria
        newEnemy.setPosition(
            static_cast<float>(rand() % static_cast<int>(window.getSize().x - newEnemy.getSize().x)),
            0.f
        );

        // Asignar un color aleatorio con un tamaño y puntaje distinto
        int type = rand() % 5;
        switch (type) {
        case 0:
            newEnemy.setSize(sf::Vector2f(15.f, 15.f));
            newEnemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            newEnemy.setSize(sf::Vector2f(20.f, 20.f));
            newEnemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            newEnemy.setSize(sf::Vector2f(25.f, 25.f));
            newEnemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            newEnemy.setSize(sf::Vector2f(30.f, 30.f));
            newEnemy.setFillColor(sf::Color::Red);
            break;
        case 4:
            newEnemy.setSize(sf::Vector2f(35.f, 35.f));
            newEnemy.setFillColor(sf::Color::Green);
            break;
        }

        enemies.push_back(newEnemy);
    }
}

void Game::updateEnemies() {
    // Temporizador para generar enemigos
    if (enemySpawnTimer >= enemySpawnTimerMax) {
        spawnEnemy();
        enemySpawnTimer = 0.f;
    } else {
        enemySpawnTimer += 1.f;
    }

    // Mover enemigos hacia abajo
    for (size_t i = 0; i < enemies.size(); i++) {
        enemies[i].move(0.f, 1.f);

        // Si un enemigo sale de la pantalla, reduce salud y elimínalo
        if (enemies[i].getPosition().y > window.getSize().y) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }
}

void Game::renderEnemies(sf::RenderTarget& target) {
    for (const auto& enemy : enemies) {
        target.draw(enemy);
    }
}

void Game::checkCollisions() {
    // Colisión con la meta
    if (player.getBounds().intersects(goal.getGlobalBounds())) {
        //std::cout << "¡Has alcanzado la meta! ¡Felicidades!" << std::endl;
        resetGoalPosition(); // Cambia la posición de la meta
        resetGameElements(); // Actualiza las bonificaciones y obstáculos
        score += 10; // Incrementa el puntaje como recompensa
    }

    // Colisiones con coleccionables
    for (size_t i = 0; i < collectibles.size(); ++i) {
        if (player.getBounds().intersects(collectibles[i].getGlobalBounds())) {
            collectibles.erase(collectibles.begin() + i);
            score += 2; // Incrementa el puntaje
            break;
        }
    }

    // Colisiones con enemigos
    for (size_t i = 0; i < enemies.size(); ++i) {
        if (player.getBounds().intersects(enemies[i].getGlobalBounds())) {
            // Eliminar enemigo, reducir salud 
            health -= 1;

            enemies.erase(enemies.begin() + i);
            break;
        }
    }
}

void Game::initFonts() {
    if (!font.loadFromFile("assets/fonts/Daydream.ttf")) {
        std::cerr << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
    }
}

void Game::initText() {
    uiText.setFont(this->font);
    uiText.setCharacterSize(24);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(10.f, 10.f); // Esquina superior izquierda
    uiText.setString("Score: 0\nHealth: 5");
}

void Game::initBackgroudd()
{
    if (!backgroundTexture.loadFromFile("./assets/images/Fondo.JPG")) { // Ruta de la imagen de fondo
        std::cerr << "ERROR: Background image could not be loaded!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}
