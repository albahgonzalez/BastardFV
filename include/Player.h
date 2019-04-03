#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "Collisions.h"
#include "Player.h"
#include <SFML/Graphics.hpp>


class Player
{
    public:
        Player();
        virtual ~Player();

        void dibujar(sf::RenderWindow &window); //dibuja al bastardo
        void mover(bool space, Collisions &colision, char pressed);


        int getVidas () { return vidas; }


    private:

        int id, exp, vidas, direction;
        float x = 0, y = 0;

        sf::Texture texture;
        sf::Sprite sprite;

};

#endif // PLAYER_H
