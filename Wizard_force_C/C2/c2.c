#include <stdio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    uint8_t _age = 10;
    uint8_t _height = 74;

    printf("I'm %d years old.\n", _age);
    printf("I'm %d inches tall.\n", _height);

    return 0;
}

// the direction of the stack grow is downward memory 
// from the upper memory 0x234235 -> 0x234200 lower memory 
