#include "Collisions.h"

Collisions::Collisions()
{
    //ctor
}

Collisions::~Collisions()
{
    //dtor
}

bool Collisions::comprobar(sf::Sprite sprite1, sf::Sprite sprite2){
    bool colision;
    sf::Rect<float> rect1 = sprite1.getGlobalBounds();
    sf::Rect<float> rect2 = sprite2.getGlobalBounds();

    if(rect1.intersects(rect2)){
        colision = true;
    }else{
        colision = false;
    }
    return colision;
}
