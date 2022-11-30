//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_GAMEBOARD_H
#define PRUEBAISAAC_GAMEBOARD_H

#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <array>
#include <cmath>

#include "Colour.h"
#include "Move.h"
#include "Piece.h"
#include "PieceType.h"

using namespace std;

class GameBoard {
private:
    bool HasNoRepeatMoves(vector<pair<int,int>> &sequence, pair<int,int> &finish);

    int darkPieces;
    int lightPieces;
    array<array<shared_ptr<Piece>, 8>, 8> board;
public:
    GameBoard();
    GameBoard(GameBoard *obj);
    GameBoard(const GameBoard &obj);
    ~GameBoard();

    shared_ptr<Piece> GetPiece(int row, int column) const;
    shared_ptr<Piece> GetPiece(std::pair<int,int> gridSpot) const;
    bool IsEmpty(std::pair<int,int> gridSpot);

    bool WithinBounds(std::pair<int,int> gridSpot);
    void MovePiece(std::pair<int,int> fromTile, std::pair<int,int> toTile);
    void RemovePiece(std::pair<int,int> gridSpot);

    bool PiecesRemaining(Colour colour);
    bool MovesRemaining(Colour colour);

    bool IsLegalSlide(shared_ptr<Piece> piece, pair<int,int> fromTile, pair<int,int> toTile);
    bool IsLegalJump(shared_ptr<Piece> piece, pair<int,int> fromTile, pair<int,int> toTile);
    bool JumpsAvailable(Colour colour);
    void GetMultiJumps(shared_ptr<Piece> piece, vector<std::pair<int,int>> seedSequence, vector<Move> &allValidMoves);
    vector<Move> GetAllValidMoves(Colour colour);

    GameBoard &operator=(GameBoard newBoard);
};

#endif //PRUEBAISAAC_GAMEBOARD_H
