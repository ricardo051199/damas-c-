//
// Created by solangel quiroga on 23/11/22.
//

#include "Controller.h"

Controller::Controller() {
    interfazDeUsuario = make_shared<GameUI>(GameUI());
}
void Controller::IniciarJuego() {
    bool forzarSalto;
    while(true) {
        forzarSalto = false;
        interfazDeUsuario->MostrarMensajeDeBienvenida();
        interfazDeUsuario->mostrarOpcionesDelJuego();
        tablero = make_shared<GameBoard>(GameBoard());
        switch (DevolverModoDeJuego()) {
            case GameMode::VerInstrucciones:
                interfazDeUsuario->mostrarInstruccionesDelJuego();
                break;
            case GameMode::UnJugador:
                interfazDeUsuario->MostrarIngresarDatos(1);
                jugador1 = make_shared<PlayerHuman>(PlayerHuman(Colour::LIGHT, GetInput()));
                jugador2 = make_shared<PlayerAI>(PlayerAI(Colour::DARK, tablero, "computadora"));
                Jugar(DevolverOpcionForzarSalto(forzarSalto));
                break;
            case GameMode::DosJugadores:
                interfazDeUsuario->MostrarIngresarDatos(1);
                jugador1 = make_shared<PlayerHuman>(PlayerHuman(Colour::DARK, GetInput()));
                interfazDeUsuario->MostrarIngresarDatos(2);
                jugador2 = make_shared<PlayerHuman>(PlayerHuman(Colour::LIGHT, GetInput()));
                Jugar(DevolverOpcionForzarSalto(forzarSalto));
                break;
        }
        if( !VolverAJuagar() ) {
            interfazDeUsuario->MostrarMensajeDeDespedida();
            break;
        }
    }
    interfazDeUsuario->MostrarMensajeDeDespedida();
}
GameMode Controller::DevolverModoDeJuego() {
    map< std::string, int > userChoice = {
            { "1",    1 },
            { "2",    2 },
            { "3",    3 },
            { "0",    0 }
    };
    string input = GetInput();
    switch(userChoice[input]) {
        case 0:
            interfazDeUsuario->MostrarMensajeDeDespedida();
            exit(0);
        case 1:
            return GameMode::VerInstrucciones;
        case 2:
            return GameMode::UnJugador;
        case 3:
            return GameMode::DosJugadores;
        default:
            interfazDeUsuario->OutputErrorMessage(GameError::INVALID_INPUT);
            interfazDeUsuario->MostrarMensajeDeBienvenida();
            return DevolverModoDeJuego();
    }
}
bool Controller::DevolverOpcionForzarSalto(bool forzarSalto) {
    interfazDeUsuario->MostrarOpcionForzarSalto();
    string input = GetInput();
    if (input == "si" or input == "s") forzarSalto = true;
    else if (input == "no" or input == "n") forzarSalto = false;
    else forzarSalto = DevolverOpcionForzarSalto(forzarSalto);
    return forzarSalto;
}
bool Controller::VolverAJuagar() {
    while (true){
        string input = GetInput();
        if ( input == "0" ) return false;
        else if ( input == "si" or input == "s" or input == "" ) return true;
        else interfazDeUsuario->OutputErrorMessage(GameError::INVALID_INPUT);
    }
}
void Controller::Jugar(bool configuracionForzarSalto){
    turnoActual = jugador1;
    interfazDeUsuario->InitUI(tablero, jugador1, jugador2);
    while (JugadorTieneMasTurnos() ) {
        bool legalMoveFound = false;
        bool lastMoveWasLegal = true;

        while ( not legalMoveFound ) {

            interfazDeUsuario->MostrarModoDeJuegoYTurnoActual(lastMoveWasLegal, true);
            interfazDeUsuario->MostrarMarcador();
            interfazDeUsuario->MostrarTablero();
            GetValidInput();

            // Stops turn increment in UI when false
            lastMoveWasLegal = true;

            if ( IsLegalMove(turnoActual->GetMove()) ){
                legalMoveFound = true;
                ExecuteMove(turnoActual->GetMove());

            } else {
                lastMoveWasLegal = false;
                interfazDeUsuario->OutputErrorMessage(GameError::ILLEGAL_MOVE);
            }
        }

        turnoActual = (turnoActual == jugador1) ? jugador2 : jugador1;
    }
    interfazDeUsuario->OutputGameOver(turnoActual != jugador1);
}
void Controller::GetValidInput() {
    if (turnoActual->IsHuman()) {
        dynamic_pointer_cast<PlayerHuman>(turnoActual)->SetInput();

        while (not dynamic_pointer_cast<PlayerHuman>
                (turnoActual)->HasValidInput()) {

            interfazDeUsuario->OutputErrorMessage(GameError::INVALID_INPUT);
            interfazDeUsuario->MostrarModoDeJuegoYTurnoActual(false, true);

            dynamic_pointer_cast<PlayerHuman>(turnoActual)->SetInput();
        }

        string input = dynamic_pointer_cast<PlayerHuman>
                (turnoActual)->GetInput();

        if ( input == "0" ) {
            interfazDeUsuario->MostrarMensajeDeDespedida();
            exit(0);
        }
    }
}
string Controller::GetInput() {
    string input;
    getline(cin, input, '\n');
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}
bool Controller::IsLegalMove(Move play) {
    bool moveIsLegal = false;
    auto allValidMoves = tablero->GetAllValidMoves(turnoActual->DevolverColor());

    for (const auto &validMove : allValidMoves) {
        if (play == validMove) {
            moveIsLegal = true;
            break;
        }
    }
    return moveIsLegal;
}
void Controller::ExecuteMove(Move play) {
    pair<int,int> fromTile = play.GetFirst();
    pair<int,int> toTile;

    if (play.GetMoveSequenceLength() == 2) {
        toTile = play.GetNext();
        if (not tablero->IsLegalSlide(tablero->GetPiece(fromTile), fromTile, toTile)) {
            tablero->RemovePiece({(fromTile.first  + toTile.first)  / 2,(fromTile.second + toTile.second) / 2});
            turnoActual->IncrementarFichasComidas();
        }
        tablero->MovePiece(fromTile, toTile);
    } else {

        while(play.HasAnotherMove()) {
            toTile = play.GetNext();

            tablero->RemovePiece({(fromTile.first  + toTile.first)  / 2,(fromTile.second + toTile.second) / 2});
            turnoActual->IncrementarFichasComidas();
            tablero->MovePiece(fromTile, toTile);

            fromTile = toTile;
        }
    }
}
bool Controller::JugadorTieneMasTurnos() {
    auto playerColour = turnoActual->DevolverColor();
    bool canMoveAPiece = tablero->MovesRemaining(playerColour);
    bool hasPiecesLeft = tablero->PiecesRemaining(playerColour);
    return canMoveAPiece or hasPiecesLeft;
}