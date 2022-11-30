//
// Created by solangel quiroga on 23/11/22.
//

#ifndef PRUEBAISAAC_MOVE_H
#define PRUEBAISAAC_MOVE_H

#include <vector>     // vector
#include <utility>    // pair, make_pair

class Move {
public:
    Move();
    Move(std::vector< std::pair<int,int> > newSequence);

    std::pair<int,int> GetFirst();
    std::pair<int,int> GetNext();
    bool HasAnotherMove();
    std::vector< std::pair<int,int> > GetMoveSequence() const;
    int GetMoveSequenceLength();

    bool operator==(const Move &otherMoveSequence) const;
    bool operator!=(const Move &otherMoveSequence) const;

private:
    int cursor;
    std::vector< std::pair<int,int> > sequence;
};
#endif //PRUEBAISAAC_MOVE_H
