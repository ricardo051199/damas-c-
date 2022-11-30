//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_PLAYERHUMAN_H
#define PRUEBAISAAC_PLAYERHUMAN_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>

#include "Colour.h"
#include "Move.h"
#include "Player.h"

using namespace std;

class PlayerHuman : public Player {
private:
    string nombre;
    vector<std::string> Split(std::string line, char delim);

    string input;
public:
    PlayerHuman(Colour colour, string nombre);
    void SetInput();
    string GetInput();
    bool HasValidInput();
    void LlenarDatos(string);

    bool IsHuman();
    Move GetMove();
};

#endif //PRUEBAISAAC_PLAYERHUMAN_H
