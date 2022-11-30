//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_CONTROLLER_H
#define PRUEBAISAAC_CONTROLLER_H


#include <iostream>
#include <memory>     // shared_ptr, make_shared, dynamic_pointer_cast
#include <algorithm>  // transform
#include <map>        // map
#include <utility>

#include "GameBoard.h"
#include "GameError.h"
#include "GameMode.h"
#include "GameUI.h"
#include "Player.h"
#include "PlayerAI.h"
#include "PlayerHuman.h"
#include "Colour.h"

using namespace std;

class Controller {
private:
    shared_ptr<GameBoard> tablero;
    shared_ptr<GameUI> interfazDeUsuario;
    shared_ptr<Player> jugador1;
    shared_ptr<Player> jugador2;
    shared_ptr<Player> turnoActual;

    GameMode DevolverModoDeJuego();
    void GetValidInput();
    string GetInput();

    bool IsLegalMove(Move play);
    void ExecuteMove(Move play);

    bool JugadorTieneMasTurnos();
    bool VolverAJuagar();
public:
    Controller();
    void IniciarJuego();
    void Jugar(bool);

    bool DevolverOpcionForzarSalto(bool);
};


#endif //PRUEBAISAAC_CONTROLLER_H
