#include <stdio.h>

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("ERROR: You need one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int i = 0;
    for(i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];

        switch(letter) {
            case 'a':
            case 'A':
                printf("%d: 'A'\n", i);
                break;

            case 'e':
            case 'E':
                printf("%d: 'E'\n", i);
                break;

            case 'i':
            case 'I':
                printf("%d: 'I'\n", i);
                break;

            case 'o':
            case 'O':
                printf("%d: 'O'\n", i);
                break;

            case 'u':
            case 'U':
                printf("%d: 'U'\n", i);
                break;

            case 'y':
            case 'Y':
                if(i > 2) {
                    // it's only sometimes Y
                    printf("%d: 'Y'\n", i);
                }
                break;

            default:
                printf("%d: %c is not a vowel\n", i, letter);
        }
    }

    return 0;
}

// additional question:
/*
if(letter >= 'A' && letter <= 'Z')
    letter = letter + 32;

switch(letter) {
    case 'a': case 'e': case 'i': case 'o': case 'u':
        printf("vowel\n");
        break;
    default:
        printf("consonant\n");
}

for(int i = 1; i < argc; i++) {
    for(int j = 0; argv[i][j] != '\0'; j++) {
        char letter = argv[i][j];
        ...
    }
}
if(letter == 'a' || letter == 'e' ||
   letter == 'i' || letter == 'o' || letter == 'u') {
    printf("vowel\n");
} else {
    printf("consonant\n");
}
*/