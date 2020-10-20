#include "Camara.h"

Camara::Camara(sf::RenderWindow &window, Player &player)
{

    if(!font.loadFromFile("fonts/prstart.ttf")){
        std::cout << "Fuente no aplicada" <<std::endl;
    }

    text.setColor(sf::Color::White);
    text.setFont(font);

    //EXPERIENCIA
    text.setString("EXP: ");
    text.setPosition(500, 600);
    text.setScale(0.5, 0.5);

    experiencia.setSize(sf::Vector2f(200, 25));
    experiencia.setOrigin(0,25);
    experiencia.setFillColor(sf::Color::Black);
    experiencia.setPosition(575, 620);

    exp2.setSize(sf::Vector2f(0, 25));
    exp2.setOrigin(0,25);
    exp2.setFillColor(sf::Color::White);
    exp2.setPosition(575, 620);

    //VIDAS
    text2 = text;
    text2.setString("LIFES: ");
    text2.setPosition(20, 600);
    text2.setScale(0.5, 0.5);

    rectangle.setSize(sf::Vector2f(200, 25));
    rectangle.setOrigin(0,25);
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(110, 620);

    vidas2.setSize(sf::Vector2f(200, 25));
    vidas2.setOrigin(0,25);
    vidas2.setFillColor(sf::Color::White);
    vidas2.setPosition(110, 620);

    gameOver = text;
    gameOver.setString("GAME OVER");
    gameOver.setScale(1,1);

}

Camara::~Camara()
{
    //dtor
}

void Camara::update(Player &player){

    int tamvidas = player.getVidas() * 2;
    vidas2.setSize(sf::Vector2f(tamvidas, 25));

    int tamexp = player.getExp() * 2;
    exp2.setSize(sf::Vector2f(tamexp, 25));


}
