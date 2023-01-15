#include "player.hpp"

#include <iostream>

// struct Position {
//     int x;
//     int y;
//     Position() : x(10), y(10) {};
//     Position(int x, int y) : x(x), y(y) {};
// };

Player::~Player() {
    std::cout << "Player " << this->name << " has been destroyed" << std::endl;
}

void Player::setName(std::string& name) {
    //todo
}

std::string Player::getName() {
    return this->name;
}

int Player::getScore() {
    return this->score;
}

void Player::setScore(int score) {
    this->score = score;
}
