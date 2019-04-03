#include "Enemigo.h"

Enemigo::Enemigo()
{
    //ctor
    if(!texture.loadFromFile("sprites/enemy1M.png")){
        std::cout << "Error al cargar la textura." << std::endl;
        exit(-1);
    }

    sprite.setTexture(texture);
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::muerto(){
    vida = false;
}
