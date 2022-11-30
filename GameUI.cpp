//
// Created by solangel quiroga on 23/11/22.
//

#include <iostream>   // cout, endl, ostream
#include <memory>     // shared_ptr, make_shared
#include <sstream>    // ostringstream
#include <string>     // string
#include <typeinfo>   // typeid

#include "GameBoard.h"
#include "GameUI.h"
#include "GameError.h"
#include "Player.h"

// Constructor
GameUI::GameUI() {
    board = nullptr;
    player1 = nullptr;
    player2 = nullptr;
    turn_number = 0;
}

// User Interface Initialization
void GameUI::InitUI(std::shared_ptr<GameBoard> newBoard,
                    std::shared_ptr<Player> newPlayer1,
                    std::shared_ptr<Player> newPlayer2) {

    board = newBoard;
    player1 = newPlayer1;
    player2 = newPlayer2;
}

// Outputs the game header and game menu options
void GameUI::MostrarMensajeDeBienvenida() {
    cout << " ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗ \n"
            " ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝ \n"
            " ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗   \n"
            " ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝   \n"
            " ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗ \n"
            "  ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝ \n"
            "                      ████████╗ ██████╗                         \n"
            "                      ╚══██╔══╝██╔═══██╗                        \n"
            "                         ██║   ██║   ██║                        \n"
            "                         ██║   ██║   ██║                        \n"
            "                         ██║   ╚██████╔╝                        \n"
            "                         ╚═╝    ╚═════╝                         \n"
            " ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ ███████╗\n"
            "██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗██╔════╝\n"
            "██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝███████╗\n"
            "██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗╚════██║\n"
            "╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║███████║\n"
            " ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n";
}
void GameUI::mostrarOpcionesDelJuego() {
    cout<<"----------OPCIONES----------"<<endl;
    cout<<"  1. Mostrar instrucciones."<<endl;
    cout<<"  2. Un jugador."<<endl;
    cout<<"  3. Dos jugadores."<<endl;
    cout<<"  0. Salir."<<endl;
    cout<<"Escoja una opcion  :  ";
}
void GameUI::mostrarInstruccionesDelJuego() {
    cout << "Indicaciones\n"
            "Cada jugador cuenta con doce fichas que se pueden observar en\n"
            "pantalla, lado superior e inferior.                          \n"
            "Las fichas se colocan sobre las casillas oscuras, otorgando  \n"
            "por teclado la fila y la columna en la que se encuentra, des-\n"
            "pues se procede a otorgar mediante la tecla la fila y columna\n"
            " donde se quiere mover la ficha.                             \n"
            "Tener en cuenta que cuando la ficha llega a la fila inferior \n"
            "o superior(dependiento al lado del contricante), la ficha se \n"
            "convertira en una ficha reina, que puede ir de manera diago- \n"
            "al por mas de una casilla.                                   \n"
            "NOTA : Observar si forzar salto esta activado o desactivado. \n"
            "La funcion forzar salto se encarga de que el jugador tenga   \n"
            "que mover forzosamente una ficha con la condicion que pueda  \n"
            "'comer'\n"<<endl;
}
void GameUI::MostrarIngresarDatos(int numero){
    cout << "JUGADOR "<< numero << "\n"
            "Nombre : ";
}
void GameUI::MostrarOpcionForzarSalto(){
    cout << "CONFIGURACIONES\n"
            "Forzar salto esta desactivado. Desea activarlo? s/n : ";
}
void GameUI::MostrarModoDeJuegoYTurnoActual(bool updateTurn, bool turnoActual) {
    std::ostringstream output;
    if (updateTurn) turn_number += 1;

    if (typeid(player1) == typeid(player2)) {
        output << "CHECKERS: Two-Player Mode       Turn # : " << turn_number << "\n\n";
    } else {
        output << "CHECKERS: One-Player Mode       Turn # : " << turn_number << "\n\n";
    }
    std::cout << "\n\n" << output.str();
}
void GameUI::MostrarMarcador() {
    cout << "--->   \033[1;40m \u25CF \033[0m   " << player1->DevolverNombre() << "     " << player1->DevolverFichasComidas() << " - " << player2->DevolverFichasComidas() << "     " << player2->DevolverNombre() << "   \033[1;31;40m \u25CF \033[1;31;0m   <---";
}
void GameUI::MostrarTablero(){
    std::ostringstream output;
    bool isLightBoardTile = true;
    std::string darkBoardTile = "\033[40m   \033[0m";
    std::string lightBoardTile = "\033[47m   \033[0m";
    output << "    1  2  3  4  5  6  7  8 \n\n";
    for (auto row = 0; row < 8; ++row) {
        output << static_cast<char>('A' + row) << "  ";
        for (auto column = 0; column < 8; ++column) {
            if (isLightBoardTile) {
                output << lightBoardTile;
            } else if (board->GetPiece(row, column) == nullptr) {
                output << darkBoardTile;
            } else {
                output << *(board->GetPiece(row, column));
            }
            isLightBoardTile = not isLightBoardTile;
        }
        output << "  " << static_cast<char>('A' + row) << std::endl;

        isLightBoardTile = not isLightBoardTile;
    }
    output << "\n    1  2  3  4  5  6  7  8 \n" << std::endl;

    // Footer
    output << "Enter a sequence of coordinates to move a piece\n"
           << "  e.g., 'F1 D4 B1' would be a double jump\n";
    if (turn_number % 2 == 1)
        output << "\033[1;31;40mPlayer One's Move:\033[0m ";
    else
        output << "\033[1;40mPlayer Two's Move:\033[0m ";

    std::cout << "\n\n" << output.str();
}

// Outputs the game over message depending on which player won
void GameUI::OutputGameOver(bool player1_wins_game) {

    const std::string winForPlayer1 = "\n\n\n"
                                      "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      ██╗\n"
                                      "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ███║\n"
                                      "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝    ╚██║\n"
                                      "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║\n"
                                      "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ██║\n"
                                      "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     ╚═╝\n"
                                      "        ██╗    ██╗██╗███╗   ██╗███████╗██╗██╗██╗         \n"
                                      "        ██║    ██║██║████╗  ██║██╔════╝██║██║██║         \n"
                                      "        ██║ █╗ ██║██║██╔██╗ ██║███████╗██║██║██║         \n"
                                      "        ██║███╗██║██║██║╚██╗██║╚════██║╚═╝╚═╝╚═╝         \n"
                                      "        ╚███╔███╔╝██║██║ ╚████║███████║██╗██╗██╗         \n"
                                      "         ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝╚═╝         \n";

    const std::string winForPlayer2 = "\n\n\n"
                                      "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗ \n"
                                      "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗\n"
                                      "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝\n"
                                      "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗    ██╔═══╝ \n"
                                      "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ███████╗\n"
                                      "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚══════╝\n"
                                      "        ██╗    ██╗██╗███╗   ██╗███████╗██╗██╗██╗             \n"
                                      "        ██║    ██║██║████╗  ██║██╔════╝██║██║██║             \n"
                                      "        ██║ █╗ ██║██║██╔██╗ ██║███████╗██║██║██║             \n"
                                      "        ██║███╗██║██║██║╚██╗██║╚════██║╚═╝╚═╝╚═╝             \n"
                                      "        ╚███╔███╔╝██║██║ ╚████║███████║██╗██╗██╗             \n"
                                      "         ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝╚═╝             \n";

    const std::string askToPlayAgain = "Would you like to play again? (y or n): ";

    if ( player1_wins_game ) {
        std::cout << winForPlayer1 << std::endl;
    } else {
        std::cout << winForPlayer2 << std::endl;
    }

    std::cout << askToPlayAgain;
}

// Output when quiting the program
void GameUI::MostrarMensajeDeDespedida() {

    const std::string clearScreen = std::string(75, '\n');

    const std::string quitProgramMessage =
            "  ████████╗██╗  ██╗ █████╗ ███╗   ██╗██╗  ██╗███████╗  \n"
            "  ╚══██╔══╝██║  ██║██╔══██╗████╗  ██║██║ ██╔╝██╔════╝  \n"
            "     ██║   ███████║███████║██╔██╗ ██║█████╔╝ ███████╗  \n"
            "     ██║   ██╔══██║██╔══██║██║╚██╗██║██╔═██╗ ╚════██║  \n"
            "     ██║   ██║  ██║██║  ██║██║ ╚████║██║  ██╗███████║  \n"
            "     ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝  \n"
            "               ███████╗ ██████╗ ██████╗                \n"
            "               ██╔════╝██╔═══██╗██╔══██╗               \n"
            "               █████╗  ██║   ██║██████╔╝               \n"
            "               ██╔══╝  ██║   ██║██╔══██╗               \n"
            "               ██║     ╚██████╔╝██║  ██║               \n"
            "               ╚═╝      ╚═════╝ ╚═╝  ╚═╝               \n"
            "██████╗ ██╗      █████╗ ██╗   ██╗██╗███╗   ██╗ ██████╗ \n"
            "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██║████╗  ██║██╔════╝ \n"
            "██████╔╝██║     ███████║ ╚████╔╝ ██║██╔██╗ ██║██║  ███╗\n"
            "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██║██║╚██╗██║██║   ██║\n"
            "██║     ███████╗██║  ██║   ██║   ██║██║ ╚████║╚██████╔╝\n"
            "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚═╝╚═╝  ╚═══╝ ╚═════╝ \n";

    std::cout << clearScreen << quitProgramMessage << std::endl;
}

// Controls output for error messages
void GameUI::OutputErrorMessage(GameError errorType) {

    std::string errorMessage = "\n\033[31mERROR\033[0m: ";

    switch(errorType) {
        // Output when user input cannot be parsed
        case GameError::INVALID_INPUT: {
            errorMessage += "Invalid input provided";
            break;
        }
            // Output when user input can be parsed, but violates one of the game rules
        case GameError::ILLEGAL_MOVE: {
            errorMessage += "Illegal move attempted";
            break;
        }
    }

    std::cout << errorMessage << std::endl;
}