#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <unordered_map>

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

unordered_map<string, int> player_id;

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

void update(Player& player) {

    while (true) {
    
        if(player_id[player.getName()] == 0) {
            
            if (Input::kbhit()) {
                char input = Input::getch();  // Read a keystroke without waiting
                if (input == 'w') player.pos.y--;
                else if (input == 's') player.pos.y++;
                else if (input == 'a') player.pos.x--;
                else if (input == 'd') player.pos.x++;
            }
        }
        else {
            if (Input::kbhit()) {
                char input = Input::getch();  // Read a keystroke without waiting
                if (input == 'i') player.pos.y--;
                else if (input == 'k') player.pos.y++;
                else if (input == 'j') player.pos.x--;
                else if (input == 'l') player.pos.x++;
            }
        }

        if (player.pos.x < 1) player.pos.x = 1;
        if (player.pos.x > MAP_WIDTH - 2) player.pos.x = MAP_WIDTH - 2;
        if (player.pos.y < 1) player.pos.y = 1;
        if (player.pos.y > MAP_HEIGHT - 2) player.pos.y = MAP_HEIGHT - 2;
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

    
    Player player1("Fulano", 'Y');
    player_id[player1.getName()] = 0;

    Player player2("Beltrano", 'P');
    player_id[player2.getName()] = 1;

    vector<Player> players = {player1, player2};

    thread t1(update, ref(players[0]));
    thread t2(update, ref(players[1]));
    thread render_thread(render, ref(players));


    t1.join();
    t2.join();
    render_thread.join();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
