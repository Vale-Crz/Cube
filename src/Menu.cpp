#include "Menu.hpp"

Menu::Menu(float width, float height) 
{
    if (!font.loadFromFile("./assets/fonts/Daydream.ttf")) 
    {
        std::cerr << "ERROR: Font could not be loaded!" << std::endl;
    }
    
    initBackgroud();
    initTitle(width);

    // Configurar las opciones del menú
    const std::string menuItems[] = {"Play", "Exit"};
    for (int i = 0; i < Max_main_menu; ++i) {
        mainMenu[i].setFont(font);
        mainMenu[i].setFillColor(sf::Color::White);
        mainMenu[i].setString(menuItems[i]);
        mainMenu[i].setCharacterSize(50);
        mainMenu[i].setPosition(sf::Vector2f(width / 2 - 100, height / 2 - 150 + i * 100));
    }

    mainMenu[0].setFillColor(sf::Color::Blue); // Selección inicial
    menuSelected = 0;
}

Menu::~Menu() {}

void Menu::initTitle(float width)
{
    titleText.setFont(font);
    titleText.setFillColor(sf::Color::Red);
    titleText.setString("Bounce Ball");
    titleText.setCharacterSize(60);

    // Obtener los límites del texto
    sf::FloatRect titleBounds = titleText.getLocalBounds();

    // Establecer el origen en el centro del texto
    titleText.setOrigin(titleBounds.width / 2, titleBounds.height / 2);

    // Establecer la posición del texto centrado horizontalmente
    titleText.setPosition(sf::Vector2f(width / 2, 70));
}


void Menu::initBackgroud()
{
    if (!backgroundTexture.loadFromFile("./assets/images/Bounce_Ball.jpg")) { // Ruta de la imagen de fondo
        std::cerr << "ERROR: Background image could not be loaded!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::moveUp() {
    if (menuSelected - 1 >= 0) {
        mainMenu[menuSelected].setFillColor(sf::Color::White);
        menuSelected--;
        mainMenu[menuSelected].setFillColor(sf::Color::Blue);
    }
}

void Menu::moveDown() {
    if (menuSelected + 1 < Max_main_menu) 
    {
        mainMenu[menuSelected].setFillColor(sf::Color::White);
        menuSelected++;
        mainMenu[menuSelected].setFillColor(sf::Color::Blue);
    }
}

void Menu::draw(sf::RenderWindow& window) 
{
    window.draw(backgroundSprite);
    window.draw(titleText);

    for (int i = 0; i < Max_main_menu; ++i) 
    {
        window.draw(mainMenu[i]);
    }
}
