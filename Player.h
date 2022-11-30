//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_PLAYER_H
#define PRUEBAISAAC_PLAYER_H

#include <iostream>
#include "Colour.h"
#include "Move.h"

using namespace std;

class Player {
private:
    string nombre;
    Colour color;
    int fichasComidas;
public:
    Player(Colour, string);
    Colour DevolverColor();
    string DevolverNombre();
    int DevolverFichasComidas();
    void IncrementarFichasComidas();

    virtual bool IsHuman() = 0;
    virtual Move GetMove() = 0;
};

#endif //PRUEBAISAAC_PLAYER_H
