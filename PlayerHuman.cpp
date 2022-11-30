//
// Created by solangel quiroga on 23/11/22.
//

#include "PlayerHuman.h"

PlayerHuman::PlayerHuman(Colour colour, string nombre): Player(colour, nombre), input("") {}
bool PlayerHuman::IsHuman(){
    return true;
}
Move PlayerHuman::GetMove() {

    if (not HasValidInput()) {
        return Move();
    }

    std::vector<std::pair<int,int>> sequence;
    auto split_input = Split(input, ' ');

    for (auto const& coordinates : split_input) {
        int row = coordinates[0]-'a';
        int column = coordinates[1]-'1';
        sequence.emplace_back(row, column);
    }

    return sequence;
}
void PlayerHuman::SetInput() {
    string newInput;
    getline(std::cin, newInput);

    transform(newInput.begin(), newInput.end(), newInput.begin(), ::tolower);

    input = newInput;
}
string PlayerHuman::GetInput() {
    return input;
}
bool PlayerHuman::HasValidInput() {
    if (input.length() < 2) {
        return false;
    }

    if (   input == "q"
           or input == "quit"
           or input == "exit") {
        return true;
    }

    vector<string> split_input = Split(input, ' ');
    if (split_input.size() < 2) {
        return false;
    }

    for (auto const& coordinates : split_input) {

        if (not ((coordinates.length() == 2)
                 and (0 <= (coordinates[0]-'a'))
                 and (7 >= (coordinates[0]-'a'))
                 and (0 <= (coordinates[1]-'1'))
                 and (7 >= (coordinates[1]-'1')) )) {
            return false;
        }
    }
    return true;
}
vector<string> PlayerHuman::Split(string input, char delim) {
    istringstream inputSequence(input);
    string newInput;
    vector<std::string> elements;

    while (getline(inputSequence, newInput, delim)) {
        elements.emplace_back(newInput);
    }
    return elements;
}