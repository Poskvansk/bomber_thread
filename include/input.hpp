#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <termios.h>

namespace Input {

    #ifndef _WIN32
        int kbhit();
        int getch(void);
    #else
        #include <conio.h>
    #endif
}

#endif // __INPUT_HPP__