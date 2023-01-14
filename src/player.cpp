#include "player.hpp"

#include <iostream>

// int count = 0;
// sem_t p1_sem;
// sem_t p2_sem;
std::mutex p1_mtx;

Player::Player(std::string name, char skin) : name(name), score(0), skin(skin) {};


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

void Player::move() {

    char up = 'w';
    char down = 's';
    char left = 'a';
    char right = 'd';
    char grab = 'q';

    if(player_id[this->name] == 1) {
        up = 'i';
        down = 'k';
        left = 'j';
        right = 'l';
        grab = ' '; // space
    }

    if (Input::kbhit()) {
        char input = Input::getch();  // Read a keystroke without waiting

        if (input == up) {
            this->pos.y--;
            this->setDirection('w');
            if (this->getHasBomb()) {
                for(int i = 0; i < bombs.size(); i++) {
                    if (bombs[i].getHoldedBy() == player_id[this->name]) {
                        bombs[i].pos.y--;
                        break;
                    }
                }
            }
        }

        else if (input == down) {
            this->pos.y++;
            this->setDirection('s');
            if (this->getHasBomb()) {
                for(int i = 0; i < bombs.size(); i++) {
                    if (bombs[i].getHoldedBy() == player_id[this->name]) {
                        bombs[i].pos.y++;
                        break;
                    }
                }
            }
        }

        else if (input == left) {
            this->pos.x--;
            this->setDirection('a');
            if (this->getHasBomb()) {
                for(int i = 0; i < bombs.size(); i++) {
                    if (bombs[i].getHoldedBy() == player_id[this->name]) {
                        bombs[i].pos.x--;
                        break;
                    }
                }
            }
        }

        else if (input == right) {
            this->pos.x++;
            this->setDirection('d');
            if (this->getHasBomb()) {
                for(int i = 0; i < bombs.size(); i++) {
                    if (bombs[i].getHoldedBy() == player_id[this->name]) {
                        bombs[i].pos.x++;
                        break;
                    }
                }
            }
        }
        
        else if (input == grab) {
            this->grabBomb();
        }

        else if (input == 'v') game_over = true;
    }

    if(this->pos.x == 0) this->pos.x = 1;
    if(this->pos.x == MAP_WIDTH - 1) this->pos.x = MAP_WIDTH - 2;
    if(this->pos.y == 0) this->pos.y = 1;
    if(this->pos.y == MAP_HEIGHT - 1) this->pos.y = MAP_HEIGHT - 2;
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
