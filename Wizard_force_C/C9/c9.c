#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }
    char letter;
    for(int i = 0, letter = argv[1][0]; argv[1][i] != '\0'; letter = argv[1][++i]) {
        switch(letter) {
            case 'a':
                printf("%d: 'A'\n", i);
                break;

            case 'e':
                printf("%d: 'E'\n", i);
                break;

            case 'i':
                printf("%d: 'I'\n", i);
                break;

            case 'o':
                printf("%d: 'O'\n", i);
                break;

            case 'u':
                printf("%d: 'U'\n", i);
                break;

            case 'y':
                if(i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }
                break;

            default:
                printf("%d: %c is not a vowel\n", i, letter);
                break;
        }
    }

    return 0;
}
/*
int i = 0;
while(i < argc && i < num_states) {
    states[i] = argv[i];
    i++;
}

states[i] = argv[i]   // it's addr copy

states[i] = malloc(strlen(argv[i]) + 1);
strcpy(states[i], argv[i]);
*/