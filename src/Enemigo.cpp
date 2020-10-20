#include "Enemigo.h"


Enemigo::Enemigo(int x, int y, int tipo)
{
    //ctor
    if(tipo == 1){
        if(!texture.loadFromFile("sprites/enemy1M.png")){
            std::cout << "Error al cargar la textura." << std::endl;
            exit(-1);
        }
    } else {
        if(!texture.loadFromFile("sprites/enemy2M.png")){
            std::cout << "Error al cargar la textura." << std::endl;
            exit(-1);
        }
    }

    vidas = 3;
    posx = x;
    posy = y;
    muerte = false;
    sprite.setTexture(texture);
    sf::IntRect rect = sf::IntRect(0,0,64,64);
    sprite.setTextureRect(rect);
    sprite.setOrigin(sprite.getLocalBounds().width/2,sprite.getLocalBounds().height/2);
    sprite.setPosition(posx,posy);
    setPosIniciales();
    xanimation = 0;
}

Enemigo::~Enemigo()
{
    //dtor
}

void Enemigo::dibujar(sf::RenderWindow &window){
    window.draw(sprite);
}


void Enemigo::muerto(){
    muerte = true;
}

int Enemigo::getVidas(){
    return vidas;
}

void Enemigo::setVidas(){
    vidas -= 1;
    std::cout<<"Vidas del enemigo: "<<vidas<<std::endl;
    if(vidas==0){
        muerto();
    }

}

void Enemigo::setPosIniciales(){
    inicialX = posx;
    inicialY = posy;
}

void Enemigo::setSprites(int t){
    if(t == 1){
        if(!texture.loadFromFile("sprites/enemy1M.png")){
            std::cout << "Error al cargar la textura." << std::endl;
            exit(-1);
        }
    } else {
        if(!texture.loadFromFile("sprites/enemy2M.png")){
            std::cout << "Error al cargar la textura." << std::endl;
            exit(-1);
        }
    }
    sprite.setTexture(texture);
}

void Enemigo::movementEnemy(Collisions &colision, Maps &map, Player &player, bool modoDios){
    int aux_posx = posx;
    int aux_posy = posy;
    static int time = 0;
    static int time2 = 0;

    int posx_player = player.getX();
    int posy_player = player.getY();

    int id = map.getId();

    int hipotenusa = sqrt(pow((posx_player - posx),2) + pow((posy_player-posy),2));

    if(hipotenusa<100){
        //MOVIMIENTO DEL ENEMIGO HACIA EL JUGADOR SI LA HIPOTENUSA ENTRE ESTOS ES < 100
        //COMPRUEBA SI ESTÁ MAS CERCA DE Y O DE X PARA ACERCARSE EN ESA POSICION
        if(posx_player-posx<posy_player-posy || posy_player-posy == 0 ){
            if(posx_player < posx){
                posx -= 1;
                angle = 270.0f - sprite.getRotation();
            } else
            if(posx_player > posx) {
                posx += 1;
                angle = 90.0f - sprite.getRotation();
            }
        }
        if(posx_player-posx>posy_player-posy || posx_player-posx == 0) {
            if(posy_player < posy){
                posy -= 1;
                angle = 360.0f - sprite.getRotation();
            } else
            if(posy_player > posy) {
                posy += 1;
                angle = 180.0f - sprite.getRotation();
            }
        }
        if(id == 1 || id == 4 || id == 6 || id == 8){
            if(colision.comprobar(sprite, player.getPlayer())){
                //CALCULA LA COLISION DEL ENEMIGO CON EL JUGADOR Y SI TIME ES > 50
                //EL ENEMIGO ATACA AL JUGADOR. ESTO SE HACE ASI PARA QUE NO
                // ATAQUE CONTINUAMENTE PORQUE EL JUGADOR MORIRIA EN 100 UPDATES
                if(time>50 && !modoDios){
                    player.setVidas();
                    time = 0;
                }
            }
        }
        time++;
        inicialX = posx;
        inicialY = posy;
        //SE MODIFICAN LAS POSICIONES INICIALES DE LOS ENEMIGOS PARA QUE SI LA HIPOTENUSA ES > 100
        //SE SIGA EL MOVIMIENTO DEL IF SIGUIENTE

    } else {
        if(hacolisionado == false){
            //MOVIMIENTO EN CUADRADO
            if(posx<inicialX+100 && posy == inicialY){
                posx += 1;
                angle = 90.0f - sprite.getRotation();
            }
            if(posx == inicialX+100 && posy < inicialY+100){
                posy +=1;
                angle = 180.0f - sprite.getRotation();
            }

            if(posy==inicialY+100 && posx > inicialX){
                posx -= 1;
                angle = 270.0f - sprite.getRotation();
            }
            if(posx == inicialX && posy > inicialY){
                posy -= 1;
                angle = 360.0f - sprite.getRotation();
            }
        } else {
            if(!hacolisionadoY){
                posy -= 1;
                angle = 360.0f - sprite.getRotation();
            }
        }
    }

    if(calcular(map,colision)){
        //SI EL ENEMIGO COLISIONA CON EL MAPA SE MUEVE EN OTRA DIRECCION
        posx = aux_posx - 1;
        posy = aux_posy;
        angle = 270.0f - sprite.getRotation();
        hacolisionado = true;
        if(calcular(map,colision)){
            //SI VUELVE A COLISIONAR, SE MUEVE EN OTRA DIRECCION. (ESTO LO MAS PROBABLE ES QUE SERIA UNA ESQUINA)
            hacolisionado = false;
            posx += 5;
            posy += 5;
            inicialX = posx;
            inicialY = posy;
            angle = 180.0f - sprite.getRotation();
        }
    }

    //ANIMACION DEL SPRITE ENEMIGO
    if(posx != aux_posx || posy != aux_posy){
        if(time2 == 0){
            xanimation += 1;
            if (xanimation >= 4){
                xanimation = 0;
            }
        }
    }

    time2 ++;
    if(time2 > 10){
        time2 = 0;
    }

    sf::IntRect rect = sf::IntRect(64*xanimation,0,64,64);
    sprite.rotate(angle);
    sprite.setTextureRect(rect);
    sprite.setPosition(posx,posy);
}

bool Enemigo::calcular(Maps &map, Collisions &colision){
    //COMPRUEBA LA COLISION DEL ENEMIGO CON LA CAPA 1 DEL MAPA (MUROS)
    bool comprobar = false;

    int width = map.getWidth();
    int height = map.getHeight();
    sf::Sprite**** tilemapSprite =  map.getTileMap();

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(tilemapSprite[1][y][x]!=NULL){
                sprite.setPosition(posx, posy);
                if(colision.comprobar(sprite, *(tilemapSprite[1][y][x]))){
                    comprobar = true;
                }

            }
        }
    }

    return comprobar;

}

void Enemigo::revivir(){
    //REVIVE LOS ENEMIGOS
    vidas = 3;
}


void Enemigo::setPos(int x, int y){
    //MODIFICA LAS POSICIONES DE LOS ENEMIGOS CUANDO SE CAMBIA DE MAPA
    posx = x;
    posy = y;
    setPosIniciales();
    sprite.setPosition(posx,posy);
}
