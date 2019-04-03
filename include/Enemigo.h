#ifndef ENEMIGO_H
#define ENEMIGO_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        void muerto();
        void dibujar(sf::RenderWindow &window);

    private:

        bool vida;
        int id;
        int direccion;

        sf::Texture texture;
        sf::Sprite sprite;


};

#endif // ENEMIGO_H
