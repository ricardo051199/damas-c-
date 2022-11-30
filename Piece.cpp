//
// Created by solangel quiroga on 23/11/22.
//

#include "Piece.h"

Piece::Piece(Colour newColour) {
    colour = newColour;
    type = PieceType::NORMAL;
}
Piece::Piece(PieceType newType, Colour newColour) {
    colour = newColour;
    type = newType;
}
Piece::~Piece() {};
Colour Piece::GetColour() const {
    return colour;
}
PieceType Piece::GetType() const {
    return type;
}
void Piece::SetType(PieceType newType) {
    type = newType;
}
ostream &operator<< (ostream& output, const Piece& piece) {
    string token;
    switch(piece.GetColour()){
        case Colour::DARK: {
            token = Piece::RED;
            break;
        }
        case Colour::LIGHT: {
            token = Piece::WHITE;
            break;
        }
    }
    switch(piece.GetType()){
        case PieceType::NORMAL: {
            token += Piece::NORMAL;
            break;
        }
        case PieceType::KING: {
            token += Piece::KING;
            break;
        }
    }
    return output << token << Piece::RESET_STREAM;
}

const string Piece::RED          = "\033[1;31;40m";
const string Piece::WHITE        = "\033[1;40m";
const string Piece::RESET_STREAM = "\033[0m";
const string Piece::NORMAL       = " \u25CF "; //"\u25CF" => filled circle
const string Piece::KING         = " \u265B "; //"\u25CB" => hollow circle
