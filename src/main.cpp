#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

//////////////////////////////////////////
#include "player.hpp"
#include "bomb.hpp"
#include "input.hpp"
//////////////////////////////////////////

using namespace std;

// #define 

#ifdef _WIN32
    #define CLEAR "cls"

#else
    #define CLEAR "clear"
    #include <termios.h>
#endif

Position p(5,5);
Bomb bomb1(&p, 10);

mutex mtx_input;

const int MAP_WIDTH = 150;
const int MAP_HEIGHT = 15;

void print_map(vector<Player>& players) {


    for (size_t i = 0; i < MAP_HEIGHT; i++) {
        
        for (size_t j = 0; j < MAP_WIDTH; j++) {

            bool cell_printed = false; // POR Q???

            for (size_t k = 0; k < players.size(); k++) {

                if(i == players[k].pos.y && j == players[k].pos.x) {
                    cout << players[k].skin;
                    cell_printed = true;
                    // continue;
                }
            }

            if (cell_printed) continue; // POR QUE ISSO FUNCIONA???

            if(i == bomb1.pos->y && j == bomb1.pos->x) {
                cout << bomb1.skin;
                continue;
            }

            if (i == 0 || i == MAP_HEIGHT - 1) {
                cout << "=";
            } 
            else {
                if (j == 0 || j == MAP_WIDTH - 1) 
                    cout << "|";

                else cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void update(Player& player1) {

    while (true) {
    
        mtx_input.lock();
        
        if (Input::kbhit()) {
            char input = Input::getch();  // Read a keystroke without waiting
            if (input == 'w') player1.pos.y--;
            else if (input == 's') player1.pos.y++;
            else if (input == 'a') player1.pos.x--;
            else if (input == 'd') player1.pos.x++;
        }


        if (player1.pos.x < 1) player1.pos.x = 1;
        if (player1.pos.x > MAP_WIDTH - 2) player1.pos.x = MAP_WIDTH - 2;
        if (player1.pos.y < 1) player1.pos.y = 1;
        if (player1.pos.y > MAP_HEIGHT - 2) player1.pos.y = MAP_HEIGHT - 2;

        mtx_input.unlock();
        // check_collision();
    }

}

void render(vector<Player>& players) {

    while (true) {
        system(CLEAR);
        print_map(players);
        usleep(80000); // 100ms delay
    }
}

int main(int argc, char const *argv[]) {
    

    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    
    Player player1("Fulano");
    Player player2("Beltrano");

    vector<Player> players = {player1, player2};

    // game_loop(players);
    thread t1(update, ref(players[0]));
    thread t2(update, ref(players[1]));
    thread render_thread(render, ref(players));


    t1.join();
    t2.join();
    render_thread.join();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
