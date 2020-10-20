#ifndef JUEGO_H
#define JUEGO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collisions.h"
#include "Player.h"
#include "Enemigo.h"
#include "Camara.h"
#include "Maps.h"

using namespace std;


class Juego
{
    public:
        Juego();
        virtual ~Juego();
        void iniciar();

    private:

        Player* player;
        Camara* camara;
        Maps* map;
        Collisions* collisions;
        Enemigo* enemy[4];

        sf::RenderWindow window;
        sf::Event evento;

        void modificarPuerta();
        void crear();
        void crearEnemigos(int x, int y, int t);
        void eventos();
        void limpiar();
        void update();
        void render(float tiempo);

        bool play = true;
        bool presionado = true;
        bool space = false;
        bool modoDios = false;

};

#endif // JUEGO_H
