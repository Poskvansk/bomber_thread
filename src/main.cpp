#include <vector>
#include <string>
#include <unordered_map>

#include <thread>
#include <mutex>

//////////////////////////////////////////
#include "player.hpp"
#include "bomb.hpp"
#include "input.hpp"
#include "renderer.hpp"
#include "ranking.hpp"
//////////////////////////////////////////

using namespace std;

InputManager inputManager = InputManager::GetInstance();

Position p(5,5);
Bomb bomb1(p, 10);

vector<Bomb> bombs = {bomb1};
unordered_map<string, int> player_id;

mutex mtx_input;

const int MAP_WIDTH = 150;
const int MAP_HEIGHT = 15;
bool game_over = false;

void update(Player& player) {
    
    int up, down, left, right, grab;
    
    if (player_id[player.getName()] == 0) {
        up = SDLK_w;
        down = SDLK_s;
        left = SDLK_a;
        right = SDLK_d;
        grab = SDLK_SPACE;
    }
    else {
        up = SDLK_UP;
        down = SDLK_DOWN;
        left = SDLK_LEFT;
        right = SDLK_RIGHT;
        grab = SDLK_RETURN;
    }

    while (!game_over && !inputManager.QuitRequested()) {

        // CONDIÇÃO DE CORRIDA - UM PLAYER ACABAVA TRABVANDO
        // POR QUE??
        mtx_input.lock();
        inputManager.Update();
        mtx_input.unlock();

        if (inputManager.IsKeyDown(up)) {
            player.moveUp();
        }
        if (inputManager.IsKeyDown(down)) {
            player.moveDown();
        }
        if (inputManager.IsKeyDown(left)) {
            player.moveLeft();
        }
        if (inputManager.IsKeyDown(right)) {
            player.moveRight();
        }
        if (inputManager.IsKeyDown(grab)) {
            player.grabBomb();
        }
        if (inputManager.IsKeyDown(SDLK_ESCAPE)) {
            game_over = true;
        }
        SDL_Delay(100);
    }
}

int main(int argc, char const *argv[]) {
    
    struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Bomberman", 0, 0, 0, 0, SDL_WINDOW_BORDERLESS);
    
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

    cout << "======== GAME OVER =========" << endl;
    update_ranking();

    SDL_DestroyWindow(window);
    SDL_Quit();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
