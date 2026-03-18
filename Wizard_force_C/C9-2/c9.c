#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    if(argc == 1) {
        printf("You only have one argument. You suck.\n");
    } else if(argc > 1 && argc < 4) {
        printf("Here's your arguments:\n");

        for(i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    } else {
        printf("You have too many arguments. You suck.\n");
    }

    return 0;
}

// additional question
/*
if(argc == 1) printf("no args\n");

if(argc > 5 && argc < 10) printf("medium args\n");

for(int i = 0; i < argc; i++) {
    if(argv[i] == NULL) break;
    printf("%s\n", argv[i]);
}

argv[0] is program name
*/
