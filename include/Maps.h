#pragma once

#ifndef MAPS_H
#define MAPS_H

#include <iostream>
#include <string>
#include <sstream>

#include "../xml/tinystr.h"
#include "../xml/tinyxml.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


using namespace std;

class Maps
{
    public:
        Maps(int i);
        virtual ~Maps();
        void drawTile(sf::RenderWindow &window);
        void pantalla(int i);
        void dibujarLlave(sf::RenderWindow &window);
        void dibujarPuerta(sf::RenderWindow &window);
        void abrirPuerta();

        bool getAbrirPuerta();
        void setPuerta(int p);

        int getPuerta()                 { return puerta;            }
        int getId()                     { return id;                }
        int getWidth()                  { return width;             }
        int getHeight()                 { return height;            }
        int getNumCapas()               { return numcapas;          }
        sf::Sprite**** getTileMap()     { return tilemapSprite;     }
        sf::Sprite getLlave()           { return llave;             }

    private:

        int id;
        int numpuertas;

        int width, height;
        int tWidth, tHeight;
        int numcapas;
        int ***tilemap;
        int puerta = 2;
        bool puertaDeLlave;

        TiXmlDocument doc;
        sf::Texture texture;
        sf::Sprite llave;
        sf::Sprite ****tilemapSprite;
        sf::Sprite * tilesetSprite;
        sf::Texture* textura;
        sf::Texture tilesetTexture;

};

#endif // MAPS_H
