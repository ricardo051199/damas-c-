//
// Created by solangel quiroga on 23/11/22.
//

#include "PlayerAI.h"

PlayerAI::PlayerAI(Colour colour, shared_ptr<GameBoard> newBoard, string nombre): Player(colour, nombre), board_copy(newBoard) {}
bool PlayerAI::IsHuman() {
    return false;
}
Move PlayerAI::GetMove() {
    vector<Move> allValidMoves = board_copy->GetAllValidMoves(DevolverColor());

    random_device device;
    mt19937 generator(device());
    uniform_int_distribution<> distribution(0, allValidMoves.size()-1);

    return allValidMoves.at(distribution(generator));
}
