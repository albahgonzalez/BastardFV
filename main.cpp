#include <SFML/Graphics.hpp>
#include <iostream>
#include "Juego.h"

using namespace std;

int main()
{
    Juego *j = new Juego();

    j->iniciar();

    delete j;
    return 0;
}
