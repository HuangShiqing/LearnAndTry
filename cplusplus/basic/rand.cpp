#include <stdlib.h>

// https://blog.csdn.net/cmm0401/article/details/54599083
int main(int argc, char const* argv[]) {
    int a = 0;
    float b = 0.0;
    a = rand();             // 0-RAND_MAX
    a = rand() % 100;       //[0, 99]
    a = rand() % 100 + 1;   //[1, 100]
    a = (rand() + 5) % 15;  //[5, 15]
    b = rand() / RAND_MAX;  //[0,1]
    return 0;
}
