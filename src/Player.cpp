#include "Player.h"
using namespace std;
Player::Player()
{
    exp = 0;
    vidas = 100;
    x = 200;
    y = 220;

    if(!texture.loadFromFile("sprites/personajeM.png")){
    std::cout << "Error al cargar la textura." << std::endl;
    exit(-1);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setScale(1,1);
    sprite.setPosition(320, 240);

    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::dibujar(sf::RenderWindow &window){
   // if(onGround){
        //AnimationManager::Instance(1)->dibujarAnimacion(id,x,y,1,window);
    //}else{
    window.draw(sprite);
   //}
}

void Player::mover(bool space, Collisions &colision, char pressed){
    if(pressed == 'A'){ //izq
        x = x - 2.5;
        //sprite.setTextureRect(sf::IntRect(1*64, 0*64, 64, 64));
    } else
    if(pressed == 'D'){ //izq
        x = x + 2.5;
    } else
    if(pressed == 'W'){ //izq
        y = y - 2.5;
        //sprite.setScale(1,1);
    } else
    if(pressed == 'S'){ //izq
        y = y + 2.5;
        //sprite.setScale(1,-1);
    }
    sprite.setPosition(x,y);
}
