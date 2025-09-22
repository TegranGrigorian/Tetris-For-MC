#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "input.h"

char get_input() {
    struct termios old_term, new_term;
    char buffer[3];
    int bytes_read;
    
    // Set up raw mode for immediate input
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 0;  // Don't wait for characters
    new_term.c_cc[VTIME] = 1; // Wait 1 tenth of a second
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    
    bytes_read = read(STDIN_FILENO, buffer, 3);
    
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    
    if (bytes_read == 0) {
        return 0; // No input
    }
    
    // arrow keys
    if (bytes_read == 3 && buffer[0] == 27 && buffer[1] == 91) {
        switch (buffer[2]) {
            case 65: return 1; // Up Arrow
            case 66: return 2; // Down Arrow  
            case 68: return 3; // Left Arrow
            case 67: return 4; // Right Arrow
        }
    }
    
    // normal
    if (bytes_read == 1 && buffer[0] != 27) {
        return map_normal_key_to_action(buffer[0]);
    }
    
    return 0; // default
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
            return 'Q'; // Quit
        case 'p':
        case 'P':
            return 'P'; // Pause
        case 'r':
        case 'R':
            return 'R'; // Resume
        case 's':
        case 'S':
            return 'S'; // Start
        default:
            return 0; // No action
    }
}

