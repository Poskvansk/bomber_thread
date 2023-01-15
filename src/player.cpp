#include "player.hpp"

#include <iostream>

Player::~Player() {
    // std::cout << "Player " << this->name << " has been destroyed" << std::endl;
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

void Player::setDirection(char direction) {
    this->direction = direction;
}

char Player::getDirection() {
    return this->direction;
}

void Player::moveUp() {
    this->pos.y--;
    if(this->pos.y == 0) this->pos.y = 1;
}

void Player::moveDown() {
    this->pos.y++;
    if(this->pos.y == MAP_HEIGHT - 1) this->pos.y = MAP_HEIGHT - 2;
}

void Player::moveLeft() {
    this->pos.x--;
    if(this->pos.x == 0) this->pos.x = 1;
}

void Player::moveRight() {
    this->pos.x++;
    if(this->pos.x == MAP_WIDTH - 1) this->pos.x = MAP_WIDTH - 2;
}

bool Player::getHasBomb() {
    return this->hasBomb;
}

void Player::grabBomb() {

    if (this->hasBomb) {

        this->hasBomb = false;

        for(int i = 0; i < bombs.size(); i++) {
            if (bombs[i].getHoldedBy() == player_id[this->name]) {
                bombs[i].setHoldedBy(-1);
                return;
            }
        }
    }

    //check player direction and checks if bomb exists in the block its looking
    //if bomb exists, set bomb holded_by to player id

    if (this->direction == 'w') {
        for(int i = 0; i < bombs.size(); i++) {
            if (bombs[i].pos.x == this->pos.x && bombs[i].pos.y == this->pos.y - 1) {
                bombs[i].setHoldedBy(player_id[this->name]);
                this->hasBomb = true;
                return;
            }
        }
    }
    else if (this->direction == 's') {
        for(int i = 0; i < bombs.size(); i++) {
            if (bombs[i].pos.x == this->pos.x && bombs[i].pos.y == this->pos.y + 1) {
                bombs[i].setHoldedBy(player_id[this->name]);
                this->hasBomb = true;
                return;
            }
        }
    }
    else if (this->direction == 'a') {
        for(int i = 0; i < bombs.size(); i++) {
            if (bombs[i].pos.x == this->pos.x - 1 && bombs[i].pos.y == this->pos.y) {
                bombs[i].setHoldedBy(player_id[this->name]);
                this->hasBomb = true;
                return;
            }
        }
    }
    else if (this->direction == 'd') {
        for(int i = 0; i < bombs.size(); i++) {
            if (bombs[i].pos.x == this->pos.x + 1 && bombs[i].pos.y == this->pos.y) {
                bombs[i].setHoldedBy(player_id[this->name]);
                this->hasBomb = true;
                return;
            }
        }
    }
}
