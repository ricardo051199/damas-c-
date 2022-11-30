//
// Created by solangel quiroga on 23/11/22.
//



#include "GameBoard.h"

GameBoard::GameBoard() {
    darkPieces = 12;
    lightPieces = 12;

    for (auto row = 0; row < 3; ++row) {
        bool placePiece = row % 2 != 0;
        for (auto column = 0; column < 8; ++column) {
            if (placePiece) {
                board[row][column] = std::make_shared<Piece>(Piece(Colour::DARK));
            }
            placePiece = !placePiece;
        }
    }
    for (auto row = 5; row < 8; ++row) {
        bool placePiece = row % 2 != 0;
        for (auto column = 0; column < 8; ++column) {
            if (placePiece) {
                board[row][column] = std::make_shared<Piece>(Piece(Colour::LIGHT));
            }
            placePiece = !placePiece;
        }
    }
}
GameBoard::GameBoard(GameBoard *obj) {
    darkPieces = obj->darkPieces;
    lightPieces = obj->lightPieces;

    for (auto row = 0; row < 8; ++row) {
        for (auto column = 0; column < 8; ++column) {
            if (obj->GetPiece(row, column) != nullptr) {
                Colour copyColour = (obj->GetPiece(row, column))->GetColour();
                PieceType copyType = (obj->GetPiece(row, column))->GetType();
                board[row][column] = std::make_shared<Piece>(copyType, copyColour);
            }
        }
    }
}
GameBoard::GameBoard(const GameBoard &obj) {
    darkPieces = obj.darkPieces;
    lightPieces = obj.lightPieces;

    for (auto row = 0; row < 8; ++row) {
        for (auto column = 0; column < 8; ++column) {
            if (obj.GetPiece(row, column) != nullptr) {
                Colour copyColour = obj.GetPiece(row, column)->GetColour();
                PieceType copyType = obj.GetPiece(row, column)->GetType();
                board[row][column] = std::make_shared<Piece>(copyType, copyColour);
            }
        }
    }
}
GameBoard::~GameBoard() {

    for(auto row : board) {
        for (auto gridSpot : row){
            gridSpot = nullptr;
        }
    }
}
std::shared_ptr<Piece> GameBoard::GetPiece(int row, int column) const {
    if(row < 0 or 7 < row or column < 0 or 7 < column) {
        return nullptr;
    }
    return board[row][column];
}
std::shared_ptr<Piece> GameBoard::GetPiece(std::pair<int,int> gridSpot) const {
    return GetPiece(gridSpot.first, gridSpot.second);
}
bool GameBoard::IsEmpty(std::pair<int,int> gridSpot) {
    return board[gridSpot.first][gridSpot.second] == nullptr;
}
bool GameBoard::WithinBounds(std::pair<int,int> gridSpot) {
    const int lowerBound = 0;
    const int upperBound = 7;

    bool isValidLow = (gridSpot.first >= lowerBound) and (gridSpot.second >= lowerBound);
    bool isValidUp  = (gridSpot.first <= upperBound) and (gridSpot.second <= upperBound);

    return isValidLow and isValidUp;
}
void GameBoard::MovePiece(pair<int,int> fromTile, pair<int,int> toTile) {
    board[toTile.first][toTile.second] = std::make_shared<Piece>(*(GetPiece(fromTile)));
    board[fromTile.first][fromTile.second] = nullptr;

    if (toTile.first == 0 and GetPiece(toTile)->GetColour() == Colour::LIGHT) {
        GetPiece(toTile)->SetType(PieceType::KING);
    }
    if (toTile.first == 7 and GetPiece(toTile)->GetColour() == Colour::DARK) {
        GetPiece(toTile)->SetType(PieceType::KING);
    }
}
void GameBoard::RemovePiece(std::pair<int,int> gridSpot) {
    if (GetPiece(gridSpot)->GetColour() == Colour::LIGHT) {
        lightPieces -= 1;
    }
    if (GetPiece(gridSpot)->GetColour() == Colour::DARK) {
        darkPieces -= 1;
    }
    board[gridSpot.first][gridSpot.second] = nullptr;
}
bool GameBoard::PiecesRemaining(Colour colour) {
    return (colour == Colour::DARK) ? (darkPieces > 0) : (lightPieces > 0);
}
bool GameBoard::MovesRemaining(Colour colour) {
    bool result = false;
    for (auto row = 0; row < 8; row++) {
        for (auto column = 0; column < 8; ++column) {

            auto piece = GetPiece(row, column);

            if (piece == nullptr || piece->GetColour() != colour) {
                continue;
            }

            if ((piece->GetType() == PieceType::KING or colour == Colour::LIGHT)
                and (  IsLegalJump( piece,
                                    std::make_pair(row    , column    ),
                                    std::make_pair(row - 2, column + 2))
                       or IsLegalJump( piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row - 2, column - 2))
                       or IsLegalSlide(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row - 1, column + 1))
                       or IsLegalSlide(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row - 1, column - 1)))) {

                result = true;
            }

            if ((piece->GetType() == PieceType::KING or colour == Colour::DARK)
                and (  IsLegalJump( piece,
                                    std::make_pair(row    , column    ),
                                    std::make_pair(row + 2, column + 2))
                       or IsLegalJump( piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row + 2, column - 2))
                       or IsLegalSlide(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row + 1, column + 1))
                       or IsLegalSlide(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row + 1, column - 1)))) {

                result = true;
            }
        }
    }
    return result;
}

// Checks for legal slide moves between two diagonally adjacent tiles
bool GameBoard::IsLegalSlide(std::shared_ptr<Piece> piece,
                             std::pair<int,int> fromTile,
                             std::pair<int,int> toTile) {

    if (piece == nullptr
        or (not WithinBounds(toTile))
        or GetPiece(toTile) != nullptr) {
        return false;
    }

    if ((piece->GetType() == PieceType::KING
         or piece->GetColour() == Colour::LIGHT)
        and (toTile.first - fromTile.first == -1)
        and (std::abs(toTile.second - fromTile.second) == 1)) {

        return true;
    }

    if ((piece->GetType() == PieceType::KING
         or piece->GetColour() == Colour::DARK)
        and (toTile.first - fromTile.first == 1)
        and (std::abs(toTile.second - fromTile.second) == 1)) {

        return true;
    }
    return false;
}

// Checks for legal diagonal jumps between two tiles
bool GameBoard::IsLegalJump(std::shared_ptr<Piece> piece,
                            std::pair<int,int> fromTile,
                            std::pair<int,int> toTile) {

    if (piece == nullptr
        or (not WithinBounds(toTile))
        or (GetPiece(toTile) != nullptr)) {

        return false;
    }

    if ((  piece->GetType() == PieceType::KING
           or piece->GetColour() == Colour::LIGHT)
        and (toTile.first - fromTile.first == -2)
        and (std::abs(toTile.second - fromTile.second) == 2)) {

        auto jumped = GetPiece((toTile.first + 1),
                               (toTile.second + fromTile.second) / 2);
        return (jumped != nullptr) and (jumped->GetColour() != piece->GetColour());
    }

    if ((  piece->GetType() == PieceType::KING
           or piece->GetColour() == Colour::DARK)
        and (toTile.first - fromTile.first == 2)
        and (std::abs(toTile.second - fromTile.second) == 2)) {

        auto jumped = GetPiece((toTile.first - 1),
                               (toTile.second + fromTile.second) / 2);
        return (jumped != nullptr) and (jumped->GetColour() != piece->GetColour());
    }

    return false;
}

// Checks for available legal diagonal jumps (cannot make slide move if a jump
// is available)
bool GameBoard::JumpsAvailable(Colour colour) {

    for (auto row = 0; row < 8; ++row) {
        for (auto column = 0; column < 8; ++column) {

            auto piece = board[row][column];
            if (piece == nullptr or piece->GetColour() != colour) {
                continue;
            }

            if ((piece->GetType() == PieceType::KING or colour == Colour::LIGHT)
                and (   IsLegalJump(piece,
                                    std::make_pair(row    , column    ),
                                    std::make_pair(row - 2, column + 2))
                        or IsLegalJump(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row - 2, column - 2)))) {

                return true;
            }

            if ((piece->GetType() == PieceType::KING or colour == Colour::DARK)
                and (   IsLegalJump(piece,
                                    std::make_pair(row    , column    ),
                                    std::make_pair(row + 2, column + 2))
                        or IsLegalJump(piece,
                                       std::make_pair(row    , column    ),
                                       std::make_pair(row + 2, column - 2)))) {

                return true;
            }
        }
    }

    return false;
}

// An ugly recursive method that looks for other jump moves that can be added
// on to the current list of moves. If no additional jumps are found the
// current jump sequence is added to a vector storing possible move sequences.
// This method should probably be split into a few others that are shorter and
// repeat less.
void GameBoard::GetMultiJumps(std::shared_ptr<Piece> piece,
                              std::vector<std::pair<int,int>> seedSequence,
                              std::vector<Move> &allValidMoves) {

    std::pair<int,int> fromTile = seedSequence.back(); // Start point of next jump

    bool jump_up_right = false;
    bool jump_up_left = false;

    // Checks for jump moves going up on the tablero (towards player 1)
    if ((piece->GetType() == PieceType::KING)
        or (piece->GetColour() == Colour::LIGHT)) {

        std::pair<int,int> toTile = std::make_pair(fromTile.first - 2, fromTile.second + 2);

        if (IsLegalJump(piece, fromTile, toTile)
            and (toTile != *(seedSequence.end() - 2))
            and HasNoRepeatMoves(seedSequence, toTile)) {

            auto newSeedSequence = seedSequence;
            newSeedSequence.emplace_back(toTile);
            GetMultiJumps(piece, newSeedSequence, allValidMoves);
            jump_up_right = true;
        }

        toTile = std::make_pair(fromTile.first - 2, fromTile.second - 2);
        if (IsLegalJump(piece, fromTile, toTile)
            and (toTile != *(seedSequence.end() - 2))
            and HasNoRepeatMoves(seedSequence, toTile)) {

            auto newSeedSequence = seedSequence;
            newSeedSequence.emplace_back(toTile);
            GetMultiJumps(piece, newSeedSequence, allValidMoves);
            jump_up_left = true;
        }

        if ((piece->GetType() != PieceType::KING)
            and (not jump_up_right)
            and (not jump_up_left)) {

            allValidMoves.emplace_back(Move(seedSequence));
        }
    }

    bool jump_down_right = false;
    bool jump_down_left = false;

    // Checks for jump moves going down on the tablero (towards player 2)
    if ((piece->GetType() == PieceType::KING)
        or (piece->GetColour() == Colour::DARK)) {

        auto toTile = std::make_pair(fromTile.first + 2, fromTile.second + 2);

        if (IsLegalJump(piece, fromTile, toTile)
            and (toTile != *(seedSequence.end() - 2))
            and HasNoRepeatMoves(seedSequence, toTile)) {

            auto newSeedSequence = seedSequence;
            newSeedSequence.emplace_back(toTile);
            GetMultiJumps(piece, newSeedSequence, allValidMoves);
            jump_down_right = true;
        }

        toTile = std::make_pair(fromTile.first + 2, fromTile.second - 2);
        if (IsLegalJump(piece, fromTile, toTile)
            and (toTile != *(seedSequence.end() - 2))
            and HasNoRepeatMoves(seedSequence, toTile)) {

            auto newSeedSequence = seedSequence;
            newSeedSequence.emplace_back(toTile);
            GetMultiJumps(piece, newSeedSequence, allValidMoves);
            jump_down_left = true;
        }

        if ((piece->GetType() != PieceType::KING)
            and (not jump_down_right)
            and (not jump_down_left)) {

            allValidMoves.emplace_back(Move(seedSequence));
        }
    }

    if ((piece->GetType() == PieceType::KING)
        and (not jump_up_right)
        and (not jump_up_left)
        and (not jump_down_right)
        and (not jump_down_left)) {

        allValidMoves.emplace_back(Move(seedSequence));
    }
}

// Searches for and returns all possible sets of move sequences from every
// piece for the given colour
std::vector<Move> GameBoard::GetAllValidMoves(Colour colour) {

    std::vector<Move> allValidMoves;
    std::vector<std::pair<int,int>> moveSequence;

    for (auto row = 0; row < 8; ++row) {
        for (auto column = 0; column < 8; ++column) {

            std::shared_ptr<Piece> piece = GetPiece(row, column);

            // Check if empty tile or wrong player piece
            if (piece == nullptr or piece->GetColour() != colour) {
                continue;
            }

            // Check for legal upward jump moves
            if (piece->GetType() == PieceType::KING
                or piece->GetColour() == Colour::LIGHT) {

                moveSequence = { std::make_pair(row    , column    ),
                                 std::make_pair(row - 2, column + 2) };
                if (IsLegalJump(piece, moveSequence[0], moveSequence[1])) {
                    GetMultiJumps(piece, moveSequence, allValidMoves);
                }

                moveSequence = { std::make_pair(row    , column    ),
                                 std::make_pair(row - 2, column - 2) };
                if (IsLegalJump(piece, moveSequence[0], moveSequence[1])) {
                    GetMultiJumps(piece, moveSequence, allValidMoves);
                }
            }

            // Check for legal downward jump moves
            if (piece->GetType() == PieceType::KING
                or piece->GetColour() == Colour::DARK) {

                moveSequence = { std::make_pair(row    , column    ),
                                 std::make_pair(row + 2, column + 2) };
                if (IsLegalJump(piece, moveSequence[0], moveSequence[1])) {
                    GetMultiJumps(piece, moveSequence, allValidMoves);
                }

                moveSequence = { std::make_pair(row    , column    ),
                                 std::make_pair(row + 2, column - 2) };
                if (IsLegalJump(piece, moveSequence[0], moveSequence[1])) {
                    GetMultiJumps(piece, moveSequence, allValidMoves);
                }
            }
        }
    }

    if (allValidMoves.empty()) {
        for (auto row = 0; row < 8; ++row) {
            for (auto column = 0; column < 8; ++column) {

                std::shared_ptr<Piece> piece = GetPiece(row, column);

                if (piece == nullptr or piece->GetColour() != colour) {
                    continue;
                }

                // Check for legal upward slide moves
                if (piece->GetType() == PieceType::KING
                    or piece->GetColour() == Colour::LIGHT) {

                    if (IsLegalSlide(piece,
                                     std::make_pair(row    , column    ),
                                     std::make_pair(row - 1, column + 1) )) {

                        Move downRight = Move({std::make_pair(row    , column    ),
                                               std::make_pair(row - 1, column + 1) });
                        allValidMoves.emplace_back(downRight);
                    }

                    if (IsLegalSlide(piece,
                                     std::make_pair(row    , column    ),
                                     std::make_pair(row - 1, column - 1) )) {

                        Move downLeft = Move({std::make_pair(row    , column    ),
                                              std::make_pair(row - 1, column - 1) });
                        allValidMoves.emplace_back(downLeft);
                    }
                }

                // Check for legal downward slide moves
                if (piece->GetType() == PieceType::KING
                    or piece->GetColour() == Colour::DARK) {

                    if (IsLegalSlide(piece,
                                     std::make_pair(row    , column    ),
                                     std::make_pair(row + 1, column + 1) )) {

                        Move downLeft = Move({std::make_pair(row    , column    ),
                                              std::make_pair(row + 1, column + 1) });
                        allValidMoves.emplace_back(downLeft);
                    }

                    if (IsLegalSlide(piece,
                                     std::make_pair(row    , column    ),
                                     std::make_pair(row + 1, column - 1) )) {

                        Move downLeft = Move({std::make_pair(row    , column    ),
                                              std::make_pair(row + 1, column - 1) });
                        allValidMoves.emplace_back(downLeft);
                    }
                }
            }
        }
    }
    return allValidMoves;
}
GameBoard &GameBoard::operator=(GameBoard newBoard){
    std::swap(darkPieces, newBoard.darkPieces);
    std::swap(lightPieces, newBoard.lightPieces);
    std::swap(board, newBoard.board);
    return *this;
}
bool GameBoard::HasNoRepeatMoves(std::vector<std::pair<int,int>> &sequence, pair<int,int> &toTile) {
    bool hasNoRepeatMoves = true;
    for (int i = 1; i < ((int)sequence.size() - 1); ++i){
        if (sequence.at(i) == sequence.back() and (  sequence.at(i - 1) == toTile or sequence.at(i + 1) == toTile)) {
            hasNoRepeatMoves = false;
            break;
        }
    }
    return hasNoRepeatMoves;
}
