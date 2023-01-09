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
Bomb bomb1(p, 10);

vector<Bomb> bombs = {bomb1};

mutex mtx_input;

const int MAP_WIDTH = 150;
const int MAP_HEIGHT = 15;

void print_infos(vector<Player>& players) {

    cout << "player " << players[0].getName() << " position " << players[0].pos.x << " " << players[0].pos.y << " direction " << players[0].getDirection()
    << " hasbomb " << players[0].getHasBomb();
    cout << "               ";
    cout << "player " << players[1].getName() << " position " << players[1].pos.x << " " << players[1].pos.y << " direction " << players[1].getDirection()
    << " hasbomb " << players[1].getHasBomb() << endl;

    cout << "bomb " << bombs[0].pos.x << " " << bombs[0].pos.y << " holded by " << bombs[0].getHoldedBy() << endl;

}

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

            for (size_t k = 0; k < bombs.size(); k++) {
                if(i == bombs[k].pos.y && j == bombs[k].pos.x) {
                    cout << bombs[k].skin;
                    cell_printed = true;
                    // continue;
                }
            }

            if (cell_printed) continue; // POR QUE ISSO FUNCIONA???


            if (i == 0 || i == MAP_HEIGHT - 1) cout << "=";

            else if (j == 0 || j == MAP_WIDTH - 1) cout << "|";

            else cout << " ";
        }
        cout << endl;
    }
    cout << endl;
    print_infos(players);
}

void update(Player& player) {

    while (true) {
        player.move();
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
