#ifndef INPUT_H
#define INPUT_H

char get_input();
char get_arrow_key_input();
char get_normal_key_input();
char map_normal_key_to_action(char key);
void clear_input_buffer();
char get_single_input();

#endif