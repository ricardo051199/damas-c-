//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_PIECE_H
#define PRUEBAISAAC_PIECE_H

#include <iostream>
#include <string>

#include "Colour.h"
#include "PieceType.h"

using namespace std;

class Piece {
public:
    Piece(PieceType newType, Colour newColour);
    Piece(Colour newColour);
    ~Piece();

    Colour GetColour() const;
    PieceType GetType() const;
    void SetType(PieceType type);

    friend std::ostream &operator<<(std::ostream& output, const Piece& piece);

private:
    PieceType type;
    Colour colour;

    static const std::string RED;
    static const std::string WHITE;
    static const std::string RESET_STREAM;

    static const std::string NORMAL;
    static const std::string KING;
};

#endif //PRUEBAISAAC_PIECE_H
