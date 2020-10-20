#ifndef CAMARA_H
#define CAMARA_H

#include "Player.h"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

class Camara
{
    public:
        Camara(sf::RenderWindow &window, Player &player);
        virtual ~Camara();
        void update(Player &player);
        void move(sf::RenderWindow &window, Player &player);
        sf::Text getText()              { return text;          }
        sf::Text getText2()             { return text2;         }

        sf::Text getGameOver()  {
                                    gameOver.setPosition(200, 250);
                                    return gameOver;
                                }

        sf::RectangleShape getExp()          { return experiencia;  }
        sf::RectangleShape getVidas()        { return rectangle;    }
        sf::RectangleShape getVidasVerde()   { return vidas2;       }
        sf::RectangleShape getExpVerde()     { return exp2;         }


    protected:

    private:
        sf::View camara;
        sf::Font font;
        sf::Text text;
        sf::Text text2;
        sf::Text gameOver;

        sf::RectangleShape rectangle;
        sf::RectangleShape experiencia;
        sf::RectangleShape vidas2;
        sf::RectangleShape exp2;
};

#endif // CAMARA_H
