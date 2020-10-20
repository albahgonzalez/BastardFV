#ifndef PLAYER_H
#define PLAYER_H

class Enemigo;

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Collisions.h"
#include "Enemigo.h"
#include "Maps.h"


class Player
{
    public:

        Player();
        virtual ~Player();
        void dibujar(sf::RenderWindow &window);
        void mover(bool space, Collisions &colision, Maps &map);
        bool atacar(Collisions &colision, Enemigo &enemy, bool modoDios);
        bool calcular(Maps &map, Collisions &colision);
        bool salida(Maps &map, Collisions &colision);

        void setVidas();
        void setLlave();
        void setExp(int valor);
        void setPos(int x, int y)   { posx = x; posy = y;   }
        int getVidas ()             { return vidas;         }
        int getX()                  { return posx;          }
        int getY()                  { return posy;          }
        int getExp ()               { return exp;           }
        bool getLlave()             { return llave;         }
        sf::Sprite getPlayer()      { return sprite;        }

    private:

        int id, exp, vidas, direction;
        int posx = 100;
        int posy = 150;
        bool llave = false;
        int xanimation = 0, yanimation =0 ;
        sf::Texture texture;
        sf::Sprite sprite;


};

#endif // PLAYER_H
