#include "Maps.h"

Maps::Maps(int num)
{
    //LLAVE
    id = num;

    //MAPAS
    pantalla(num);

    if(num==3)
        puertaDeLlave = true;
    else
        puertaDeLlave = false;

    TiXmlElement* map = doc.FirstChildElement("map");

    map->QueryIntAttribute("width",&width);
    map->QueryIntAttribute("height",&height);

    map->QueryIntAttribute("tilewidth", &tWidth);
	map->QueryIntAttribute("tileheight", &tHeight);

    if(!tilesetTexture.loadFromFile("maps/tile.png")){
        std::cout << "Error al cargar el tileset." << std::endl;
    }

    //CAPAS
    map->FirstChildElement("layer");
    TiXmlElement *capas = map->FirstChildElement("layer");
    numcapas=0;
    while(capas){
        numcapas += 1;
        capas= capas->NextSiblingElement("layer");
    }


    cout<<"id del mapa: "<<id<<", num de puertas: "<<numpuertas<<", num de capas: "<<numcapas<<endl;

    //MEMORIA
    tilemap=new int**[numcapas];
    for(int i=0; i<numcapas; i++){
        tilemap[i]=new int*[height];
    }

    for(int l=0; l<numcapas; l++){
        for(int y=0; y<height; y++){
            tilemap[l][y]=new int[width];
        }
    }



    capas = map->FirstChildElement("layer");
    string *name=new string[numcapas];
    int j=0;
    int l=0;

    //LEER TILES
    //CAPA 1: TILE
    for(int l = 0; l<numcapas; l++){
        TiXmlElement *data = capas->FirstChildElement("data")->FirstChildElement("tile");
        name[j]= (string)capas->Attribute("name");
        for(int y=0; y<height; y++){
            for(int x=0; x<width;x++){
                data->QueryIntAttribute("gid",&tilemap[l][y][x]);
                data=data->NextSiblingElement("tile");
            }
        }
        j++;
        capas= capas->NextSiblingElement("layer");

    }

    //MEMORIA SPRITES
    tilemapSprite=new sf::Sprite***[numcapas];

    for(int l=0; l<numcapas; l++){
        tilemapSprite[l]=new sf::Sprite**[height];
    }

    for(int l=0; l<numcapas; l++){
        for(int y=0; y<height; y++){
            tilemapSprite[l][y]= new sf::Sprite*[width];
            for(int x=0; x<width; x++){
                tilemapSprite[l][y][x]=new sf::Sprite();
            }
        }
    }

    int columnas = tilesetTexture.getSize().x / tWidth;
    int filas = tilesetTexture.getSize().y / tHeight;


    tilesetSprite = new sf::Sprite[columnas*filas];
    int ts=0;
    for(int y=0; y<filas; y++){
        for(int x=0; x<columnas;x++){
              tilesetSprite[ts].setTexture(tilesetTexture);
              tilesetSprite[ts].setTextureRect(sf::IntRect(x*tWidth,y*tHeight,tWidth,tHeight));
              ts++;
        }
    }

    //Carga
    for(int c=0; c<numcapas; c++){
        for(int y=0; y<height; y++){
            for(int x=0; x<width;x++){
                int gid=tilemap[c][y][x]-1;
                if(gid>=filas*columnas){
                    cout<<"Si entra, esta fallando"<<endl;
                }
                else if(gid>=1){
                    tilemapSprite[c][y][x]=new sf::Sprite(tilesetTexture,tilesetSprite[gid].getTextureRect());
                    tilemapSprite[c][y][x]->setPosition(x*tWidth,y*tHeight);
                }
                else{
                    tilemapSprite[c][y][x]=NULL;
                }
            }
        }
    }

}

Maps::~Maps()
{
    //dtor
}

void Maps::drawTile(sf::RenderWindow &window){
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(tilemapSprite[0][y][x]!=NULL){
                window.draw(*(tilemapSprite[0][y][x]));
            }
        }
    }

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(tilemapSprite[1][y][x]!=NULL){
                window.draw(*(tilemapSprite[1][y][x]));
            }
        }
    }

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(tilemapSprite[2][y][x]!=NULL){
                window.draw(*(tilemapSprite[2][y][x]));
            }
        }
    }
    if(puertaDeLlave){
        for(int y=0; y<height; y++){
            for(int x=0; x<width; x++){
                if(tilemapSprite[3][y][x]!=NULL){
                    window.draw(*(tilemapSprite[3][y][x]));
                }
            }
        }
    }
}

void Maps::dibujarPuerta(sf::RenderWindow &window){
    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            if(tilemapSprite[4][y][x]!=NULL){
                window.draw(*(tilemapSprite[4][y][x]));
            }
        }
    }
}

void Maps::dibujarLlave(sf::RenderWindow &window){
    if(!texture.loadFromFile("sprites/llave.png")){
        std::cout << "Error al cargar la textura." << std::endl;
        exit(-1);
    }
    llave.setTexture(texture);
    llave.setPosition(200,400);
    window.draw(llave);
}

void Maps::pantalla(int num){
    switch (num){
        case 1:
            if(!doc.LoadFile("maps/map.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 1;
            break;
        case 2:
            if(!doc.LoadFile("maps/map2.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 2;
            break;
        case 3:
            if(!doc.LoadFile("maps/map3.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 2;
            break;
        case 4:
            if(!doc.LoadFile("maps/map4.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 1;
            break;
        case 5:
            if(!doc.LoadFile("maps/map5.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 2;
            break;
        case 6:
            if(!doc.LoadFile("maps/map6.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 3;
            break;
        case 7:
            if(!doc.LoadFile("maps/map7.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 2;
            break;
        case 8:
            if(!doc.LoadFile("maps/map8.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 3;
            break;
        case 9:
            if(!doc.LoadFile("maps/map9.tmx")){
                std::cout << "Error al cargar el mapa." << std::endl;
            }
            numpuertas = 2;
            break;

    }

}

void Maps::setPuerta(int p){
    puerta = p;
}

void Maps::abrirPuerta(){
    puertaDeLlave = false;
    getAbrirPuerta();
}

bool Maps::getAbrirPuerta(){
    return !puertaDeLlave;
}

