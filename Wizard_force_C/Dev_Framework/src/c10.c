#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

// forward declarations
void v_print_letters(char arg[]);
void v_print_arguments(int argc, char** argv)
{
    for(int i = 0; i < argc; i++){
        v_print_letters(argv[i]); 
    }
}

void v_print_letters(char arg[])
{
    uint8_t u8_length = strlen(arg);
    for(int i = 0; i < u8_length; i++){
        if(isalpha(arg[i]) || isblank(arg[i])){
            printf("%c, ASCII:%d", arg[i], arg[i]);
        }
    }
    printf("\n");

}

int main(int argc, char *argv[])
{
    v_print_arguments(argc, argv);
    return 0;
}
