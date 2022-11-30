//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_GAMEUI_H
#define PRUEBAISAAC_GAMEUI_H

#include <iostream>
#include <memory>       // shared_ptr

#include "GameBoard.h"
#include "GameError.h"
#include "GameUI.h"
#include "Player.h"

using namespace std;

class GameUI {
public:
    GameUI();

    void InitUI(std::shared_ptr<GameBoard> newBoard,
                std::shared_ptr<Player> newPlayer1,
                std::shared_ptr<Player> newPlayer2);

    void MostrarMensajeDeBienvenida();
    void mostrarOpcionesDelJuego();
    void mostrarInstruccionesDelJuego();
    void MostrarIngresarDatos(int);
    void MostrarOpcionForzarSalto();
    void MostrarModoDeJuegoYTurnoActual(bool updateTurn, bool turnoActual);
    void MostrarMarcador();
    void MostrarTablero();
    void OutputGameOver(bool player1_wins);
    void MostrarMensajeDeDespedida();

    void OutputErrorMessage(GameError errorType);

private:
    std::shared_ptr<GameBoard> board;
    std::shared_ptr<Player> player1;
    std::shared_ptr<Player> player2;
    int turn_number;

};


#endif //PRUEBAISAAC_GAMEUI_H
