#include "Player.h"
#include <math.h>
#include <stdio.h>
#include <iostream>

using namespace std;

Player::Player()
{
    exp = 0;
    vidas = 100;
    if(!texture.loadFromFile("sprites/personajeM.png")){
        std::cout << "Error al cargar la textura." << std::endl;
        exit(-1);
    }
    sprite.setTexture(texture);
    sf::IntRect rect = sf::IntRect(0,0,64,64);
    sprite.setTextureRect(rect);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(posx,posy);

    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::dibujar(sf::RenderWindow &window){
    window.draw(sprite);
}

void Player::mover(bool space, Collisions &colision, Maps &map){
    const float speed = 5;
    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;
    float angle;
    int aux_posx = posx;
    int aux_posy = posy;


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            posy -= speed;
            if(calcular(map, colision))
                posy = aux_posy;
            up = true;

    }
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            posy += speed;
            if(calcular(map, colision))
                posy = aux_posy;
            down = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            posx -= speed;
            if(calcular(map, colision))
                posx = aux_posx;
            left = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            posx += speed;
            if(calcular(map, colision))
                posx = aux_posx;
            right = true;
    }
    yanimation = 0;
    xanimation += 1;

    if (xanimation >= 4){
        xanimation = 0;
        yanimation += 1;
        if(yanimation>=4){
            yanimation = 0;
        }
    }
    sf::IntRect rect = sf::IntRect(64*xanimation,yanimation*64,64,64);
    if(left){
        if(up){
            angle = 315.0f - sprite.getRotation();
        } else
        if(down){
            angle = 225.0f - sprite.getRotation();
        } else {
            angle = 270.0f - sprite.getRotation();
        }
    } else
    if(right){
        if(up){
            angle = 45.0f - sprite.getRotation();
        } else
        if(down){
            angle = 135.0f - sprite.getRotation();
        } else {
            angle = 90.0f - sprite.getRotation();
        }
    } else
    if(up){
        angle = 360.0f - sprite.getRotation();
    } else
    if(down){
        angle = 180.0f - sprite.getRotation();
    }
    sprite.rotate(angle);
    sprite.setTextureRect(rect);
    sprite.setPosition(posx,posy);
    salida(map, colision);
}

bool Player::salida(Maps &map, Collisions &colision){
    bool cambiar = false;
    int ancho = map.getWidth();
    int alto = map.getHeight();
    sf::Sprite**** tilemapSprite =  map.getTileMap();

    for(int y=0; y<alto; y++){
        for(int x=0; x<ancho; x++){
            if(tilemapSprite[2][y][x]!=NULL){
                sprite.setPosition(posx, posy);
                if(colision.comprobar(sprite, *(tilemapSprite[2][y][x]))){
                    map.pantalla(2);
                    cambiar = true;
                }
            }
        }
    }

    return cambiar;
}

bool Player::calcular(Maps &map, Collisions &colision){
    bool comprobar = false;

    int _width = map.getWidth();
    int _height = map.getHeight();
    sf::Sprite**** _tilemapSprite =  map.getTileMap();

    for(int y=0; y<_height; y++){
        for(int x=0; x<_width; x++){
            if(_tilemapSprite[1][y][x]!=NULL){
                sprite.setPosition(posx, posy);
                if(colision.comprobar(sprite, *(_tilemapSprite[1][y][x]))){
                    comprobar = true;
                }

            }
            if(map.getNumCapas()==4 && map.getAbrirPuerta()==false){
                if(_tilemapSprite[3][y][x]!=NULL){
                    sprite.setPosition(posx, posy);
                    if(colision.comprobar(sprite, *(_tilemapSprite[3][y][x]))){
                        comprobar = true;
                    }

                }
            }
        }
    }

    return comprobar;

}

bool Player::atacar(Collisions &colision, Enemigo &enemy, bool modoDios){
    bool atacao = false;
    if(enemy.getVidas()>0){
        if(colision.comprobar(sprite, enemy.getEnemy())) {
            enemy.setVidas();
            setExp(3);
            atacao = true;
            if(enemy.getVidas()==0){
                setExp(7);
            }
            cout<<"Experiencia del jugador: "<<exp<<endl;
            if(!modoDios){
                setVidas();
            }
        }
    }
    return atacao;
}

void Player::setExp(int valor){
    if(exp<100){
        exp += valor;
    }
    if(exp>100){
        exp = 100;
    }
}
void Player::setLlave(){
    if(!llave){
        llave = true;
        cout<<"El jugador ha cogido la llave"<<endl;
    } else
        llave = false;
}

void Player::setVidas(){
    vidas -= 1;
}

