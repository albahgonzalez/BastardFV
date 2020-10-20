#include "Juego.h"

Juego::Juego(): window(sf::VideoMode(800,640),"Bastard"){
    //ctor
}

Juego::~Juego()
{
    //dtor
}

void Juego::eventos(){

    while(window.pollEvent(evento)){
        switch(evento.type){
                    case sf::Event::Closed:
                        play = false;
                        break;
                    case sf::Event::KeyPressed:
                        if(evento.key.code==sf::Keyboard::A){
                            presionado = true;
                        }

                        if(evento.key.code==sf::Keyboard::S){
                            presionado = true;
                        }

                        if(evento.key.code==sf::Keyboard::W){
                            presionado = true;
                        }

                        if(evento.key.code==sf::Keyboard::D){
                            presionado = true;
                        }

                        if(evento.key.code==sf::Keyboard::Space){
                            space = true;
                        }

                        if(evento.key.code==sf::Keyboard::Escape || evento.key.code==sf::Keyboard::Q){
                            play = false;
                        }

                        if(evento.key.code==sf::Keyboard::G){
                            modoDios = !modoDios;
                            if(modoDios)
                                cout<<"Modo dios activado, los enemigos no atacaran"<<endl;
                            else
                                cout<<"Modo dios desactivado"<<endl;
                        }
                        break;
                }
    }
}
void Juego::modificarPuerta(){
    int x, y;
    switch(map->getId()){
        case 1:
            player->setPos(735,player->getY());
            map->setPuerta(2);
            break;
        case 2:
            if(player->getX()>700){
                x = 300;
                y = 200;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(65,player->getY());
                map->setPuerta(1);
            } else if(player->getX()<100){
                player->setPos(735,player->getY());
                map->setPuerta(3);
            }
            break;
        case 3:
            if(player->getY()<500){
                player->setPos(65,player->getY());
                map->setPuerta(2);
            } else {
                x = 150;
                y = 300;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(player->getX(),65);
                map->setPuerta(6);
            }

            break;
        case 4:
            player->setPos(player->getX(),65);
            map->setPuerta(7);
            break;
        case 5:
            if(player->getX()<100){
                x = 150;
                y = 300;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(735,player->getY());
                map->setPuerta(6);
            } else {
                x = 150;
                y = 325;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(player->getX(),65);
                map->setPuerta(8);
            }
            break;
        case 6:
            if(player->getX()>730){
                player->setPos(65,player->getY());
                map->setPuerta(5);
            } else {
                if(player->getY()<500){
                    player->setPos(player->getX(),575);
                    map->setPuerta(3);
                } else if(player->getY()>500) {
                    player->setPos(player->getX(),65);
                    map->setPuerta(9);
                }
            }
            break;
        case 7:
            if(player->getX()<100){
                x = 150;
                y = 325;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(735,player->getY());
                map->setPuerta(8);
            } else {
                x = 400;
                y = 150;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(player->getX(),575);
                map->setPuerta(4);
            }
            break;
        case 8:
            if(player->getY()<100){
                player->setPos(player->getX(),575);
                map->setPuerta(5);
            } else {
                if(player->getX()<500){
                    player->setPos(735,player->getY());
                    map->setPuerta(9);
                } else if(player->getX()>500) {
                    player->setPos(65,player->getY());
                    map->setPuerta(7);
                }
            }
            break;
        case 9:
            if(player->getX()>730){
                x = 150;
                y = 325;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(65,player->getY());
                map->setPuerta(8);
            } else {
                x = 150;
                y = 300;
                enemy[0]->setPos(x,     y);
                enemy[1]->setPos(x+100, y);
                enemy[2]->setPos(x+100, y+100);
                enemy[3]->setPos(x,     y+100);
                player->setPos(player->getX(),575);
                map->setPuerta(6);
            }
            break;

    }

    for(int i = 0 ; i < 4 ; i++){
        enemy[i]->revivir();
    }
    map = new Maps(map->getPuerta());

}

void Juego::update(){
    if(presionado){
        player->mover(space, *collisions, *map);
        if(player->salida(*map, *collisions) == true){
            modificarPuerta();
        }
    }

    if(space){
        int id = map->getId();
        bool atacao = false;
        static bool nohayllave = false;

        if(id == 1 || id == 4 || id == 6 || id == 8){
            for(int i = 0; i<4; i++){
                atacao = player->atacar(*collisions, *enemy[i], modoDios);

            }
        }

        if(!atacao){
            if(player->getLlave() && id == 3){
                map->abrirPuerta();
            } else
            if(!nohayllave && collisions->comprobar(player->getPlayer(), map->getLlave())){
                player->setLlave();
                nohayllave = true;
            }
        }
    }

    if(player->getVidas()>0){
        camara->update(*player);
    }
}

void Juego::render(float tiempo){
    window.clear(sf::Color::Black);
    if(player->getVidas()>0){
        map->drawTile(window);
        if(player->getLlave() == false){
            if(map->getId()==5)
            map->dibujarLlave(window);
        }
        player->dibujar(window);
        if(map->getId()==1 || map->getId()==8){
            for(int i = 0 ; i<(sizeof(enemy)/sizeof(*enemy)); i++){
                enemy[i]->setSprites(1);
                if(enemy[i]->getVidas()>0)
                    enemy[i]->dibujar(window);
            }
        }
        if(map->getId()==6 || map->getId()==4){
            for(int i = 0 ; i<(sizeof(enemy)/sizeof(*enemy)); i++){
                enemy[i]->setSprites(2);
                if(enemy[i]->getVidas()>0)
                    enemy[i]->dibujar(window);
            }
        }
        window.draw(camara->getVidas());
        window.draw(camara->getText());
        window.draw(camara->getText2());

        window.draw(camara->getExp());
        window.draw(camara->getVidasVerde());
        window.draw(camara->getExpVerde());

    } else {
        window.draw(camara->getGameOver());
    }
    window.display();
}

void Juego::crearEnemigos(int x, int y, int tipo){

    enemy[0] = new Enemigo(x, y,          tipo);
    enemy[1] = new Enemigo(x+100, y,      tipo);
    enemy[2] = new Enemigo(x+100, y+100,  tipo);
    enemy[3] = new Enemigo(x,     y+100,  tipo);

}

void Juego::crear(){
    map = new Maps(1);
    player = new Player();
    camara = new Camara(window, *player);
    collisions = new Collisions();
    crearEnemigos(300, 200, 1);
}

void Juego:: limpiar(){
    window.close();
}

void Juego::iniciar(){
    float s = 0.f;
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    crear();
    while(play==true){

        if(s >= 1.f/60.f){
            s = 0.f;
            eventos();
            update();
            for(int i = 0; i < (sizeof(enemy)/sizeof(*enemy)); i++){
            enemy[i]->movementEnemy(*collisions, *map, *player, modoDios);
            }
            presionado = false;
            space = false;
        }
        render(1.f/160.f);
        s = s + 1.f/60.f;
    }
    limpiar();

}
