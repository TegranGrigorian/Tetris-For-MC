#include <unistd.h>
#include "test/test.h"

int main() {
    // input_test();
    cube_fall_test();
    usleep(1000000); // Small delay to see the final output before exiting
    line_fall_test();
    return 0;
}