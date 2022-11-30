//
// Created by solangel quiroga on 23/11/22.
//

#include "Player.h"

Player::Player(Colour color, string nombre) {
    this->color = color;
    this->nombre = nombre;
    this->fichasComidas=0;
}
Colour Player::DevolverColor() {
    return color;
}
string Player::DevolverNombre(){
    return nombre;
}
int Player::DevolverFichasComidas(){
    return fichasComidas;
}
void Player::IncrementarFichasComidas(){
    fichasComidas++;
}
