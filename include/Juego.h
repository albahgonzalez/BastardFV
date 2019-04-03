#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collisions.h"
#include "Player.h"

using namespace std;


class Juego
{
    public:
        Juego();
        virtual ~Juego();
        void iniciar();

    private:

        Player* player;
        Collisions* collisions;

        sf::RenderWindow window;
        sf::Event evento;
        sf::Clock reloj;

        void crear();
        void eventos();
        void limpiar();
        void update();
        void render(float tiempo);

    private:

        bool play = true;
        bool presionado = true;
        bool space = false;
        char pressed = 0;

};

#endif // JUEGO_H
