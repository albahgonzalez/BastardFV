#include "Juego.h"

Juego::Juego(): window(sf::VideoMode(800,600),"Bastard"){
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
                            pressed = 'A';
                            presionado = true;
                        }else

                        if(evento.key.code==sf::Keyboard::S){
                            pressed = 'S';
                            presionado = true;
                        }else

                        if(evento.key.code==sf::Keyboard::W){
                            pressed = 'W';
                            presionado = true;
                        }else

                        if(evento.key.code==sf::Keyboard::D){
                            pressed = 'D';
                            presionado = true;
                        }else

                        if(evento.key.code==sf::Keyboard::Space){
                            pressed = 'P';
                            space = true;
                        }else

                        if(evento.key.code==sf::Keyboard::Escape){
                            play = false;
                        }

                }
    }
}

void Juego::update(){
    if(presionado){
        player->mover(space, *collisions, pressed);
        presionado = false;
    //mover
    }
    if(player->getVidas()>0){

    }
}

void Juego::render(float tiempo){
    window.clear(sf::Color::Black);

    if(player->getVidas()>0){
        player->dibujar(window);
    } else {

    }
    window.display();
}

void Juego::crear(){
    player = new Player();
    collisions = new Collisions();
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
        }

        render(1.f/160.f);
        s = s + 1.f/60.f;
    }
    limpiar();

}
