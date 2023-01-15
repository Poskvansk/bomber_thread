#ifndef __BOMB_HPP__
#define __BOMB_HPP__

struct Position;

class Bomb {
    private:
        // time_t start;
        // time_t end;
        // int x;
        // int y;
        int range;
        bool exploded;

    public:
        Position *pos;
        char skin = 'o';
        // Bomb() : pos(nullptr), x(0), y(0), range(0), exploded(false) {};
        // Bomb(int x, int y, int range) : pos(nullptr), x(x), y(y), range(range), exploded(false) {};
        Bomb(Position *pos, int range) : pos(pos), range(range), exploded(false) {};

        ~Bomb() {};
};


#endif // __BOMB_HPP__