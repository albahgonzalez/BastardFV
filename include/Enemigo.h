class Player;

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "Player.h"
#include "Collisions.h"
#include "Maps.h"

class Enemigo
{//PATH FIND
    public:
        Enemigo(int posx, int posy, int tipo);
        virtual ~Enemigo();
        void muerto();
        void dibujar(sf::RenderWindow &window);
        void movementEnemy(Collisions &colision, Maps &map, Player &player, bool modoDios);
        void atacar();
        bool calcular(Maps &map, Collisions &colision);
        void setVidas();
        void setSprites(int t);
        void revivir();
        void setPos(int x, int y);
        void setPosIniciales();
        int getVidas();
        sf::Sprite getEnemy(){return sprite;}

    private:
        bool muerte;
        int vidas;
        int direccion;
        int posx,posy;
        int inicialX, inicialY;
        int xanimation;
        bool hacolisionado = false, hacolisionadoY = false;

        float angle = 90.0f - sprite.getRotation();
        sf::Texture texture;
        sf::Sprite sprite;

};

#endif // ENEMIGO_H
