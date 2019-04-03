#ifndef COLLISIONS_H
#define COLLISIONS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Collisions
{
    public:
        Collisions();
        virtual ~Collisions();
        bool comprobar(sf::Sprite sp, sf::Sprite sp2);

};

#endif // COLLISIONS_H
