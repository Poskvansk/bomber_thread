#include "input.hpp"


    #ifndef _WIN32

        int Input::kbhit(){

            struct termios oldt, newt;
            int ch, oldf;
            tcgetattr(STDIN_FILENO,&oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
            fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
            ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            fcntl(STDIN_FILENO, F_SETFL, oldf);
            if(ch != EOF){
                ungetc(ch,stdin);
                return 1;
            }
            return 0;
        }

        int Input::getch(void) {
            int ch;
            struct termios oldt;
            struct termios newt;
            tcgetattr(STDIN_FILENO,&oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            ch = getchar();
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return ch;
        }
    #else
        #include <conio.h>
        int Input::kbhit() {
            return _kbhit();
        }
        int Input::getch() {
            return _getch();
        }
    #endif