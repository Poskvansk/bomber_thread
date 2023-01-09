#ifndef __BOMB_HPP__
#define __BOMB_HPP__

#include "position.hpp"

class Bomb {
    private:
        // time_t start;
        // time_t end;
        // int x;
        // int y;
        int range;
        bool exploded;
        int holded_by = -1;

    public:

        Position pos;
        char skin = 'o';

        Bomb(Position pos, int range) : pos(pos), range(range), exploded(false) {};
        ~Bomb() {};

        void explode();

        void setHoldedBy(int id);
        int getHoldedBy();

};


#endif // __BOMB_HPP__