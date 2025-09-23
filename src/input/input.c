#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "input.h"

char get_input() {
    struct termios old_term, new_term;
    char buffer[3];
    int bytes_read;
    
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    
    bytes_read = read(STDIN_FILENO, buffer, 3);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    
    if (bytes_read == 0) {
        return 0;
    }
    
    if (bytes_read == 3 && buffer[0] == 27 && buffer[1] == 91) {
        switch (buffer[2]) {
            case 65: return 1;
            case 66: return 2;
            case 68: return 3;
            case 67: return 4;
        }
    }
    
    if (bytes_read == 1 && buffer[0] != 27) {
        return map_normal_key_to_action(buffer[0]);
    }
    
    return 0;
}

void clear_input_buffer() {
    struct termios old_term, new_term;
    char dummy;
    
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 0;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    
    while (read(STDIN_FILENO, &dummy, 1) > 0) {
    }
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
}

char get_single_input() {
    clear_input_buffer();
    return get_input();
}
char get_arrow_key_input() {
    return get_input();
}

char get_normal_key_input() {
    return get_input();
}

char map_normal_key_to_action(char key) {
    switch (key) {
        case 'q':
        case 'Q':
            return 'Q';
        case 'p':
        case 'P':
            return 'P';
        case 'r':
        case 'R':
            return 'R';
        case 's':
        case 'S':
            return 'S';
        default:
            return 0;
    }
}

