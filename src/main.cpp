#include <vector>
#include <string>
#include <unordered_map>

#include <thread>
#include <mutex>

//////////////////////////////////////////
// #include "player.hpp"
#include "bomb.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "ranking.hpp"
//////////////////////////////////////////

using namespace std;

Position p(5,5);
Bomb bomb1(p, 10);

vector<Bomb> bombs = {bomb1};
unordered_map<string, int> player_id;

mutex mtx_input;

const int MAP_WIDTH = 150;
const int MAP_HEIGHT = 15;
bool game_over = false;

void update(Player& player) {
    while (!game_over) {
        player.move();
        usleep(500); //
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

    // sem_init(&rendered, 0, 1);
    thread render_thread(render, ref(players));

    // Player* player11 = &players[0];
    // Player* player22 = &players[1];

    // thread t1(update, player11);
    // thread t2(update, player22);
    // thread render_thread(render, ref(players));

    t1.join();
    t2.join();
    render_thread.join();

    cout << "======== GAME OVER =========" << endl;
    update_ranking();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
