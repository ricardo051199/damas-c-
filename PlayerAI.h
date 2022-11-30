//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_PLAYERAI_H
#define PRUEBAISAAC_PLAYERAI_H

#include <memory>
#include <random>
#include <vector>

#include "Colour.h"
#include "GameBoard.h"
#include "Move.h"
#include "Player.h"

class PlayerAI : public Player {
public:
    // Constructor
    PlayerAI(Colour newColour, std::shared_ptr<GameBoard> newBoard, std::string nombre);

    // Defined in base class
    // Colour DevolverColor();

    // Virtual in base class
    bool IsHuman();
    Move GetMove();

private:
    std::shared_ptr<GameBoard> board_copy;
};

#endif //PRUEBAISAAC_PLAYERAI_H
