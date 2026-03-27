#include <stdio.h>
#include "./dbg.h"

#define MAX_DATA 100

typedef enum EyeColor{
    BLUE_EYES,
    GREEN_EYES,
    BROWN_EYES,
    BLACK_EYES,
    OTHER_EYES
} EyeColor;
// naminated enumeration
// function of naminated enumeration is "CHOICE"

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;  // nominated enumeration (CHOICE)
    float income;
} Person;


int main(int argc, char *argv[])
{
    Person you = {.age = 0}; // significant

    // Person foo = {
    //     .age = 10,
    //     .eyes = BLACK_EYES
    // };

    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");  // check

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);   // open stdin interface, read data from command line
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}


appendix_1(){

    Person bar = {.last_name = "Jordan"};
    char* in;

    printf("What's your First Name? ");
    in = fgets(bar.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");  // check

    printf("Your age:");
    char* age;
    in = fgets(age, MAX_DATA - 1, stdin);
    // check

    bar.age = atoi(age);

    scanf("%d", &bar.income);
    // check

error:

}

appendix_2(){
    // make input name stored without blank and \n


}

char* optimize_name(char* name){
    char* temp = name;
    char* buffer = (char*)malloc(sizeof(char) * MAX_DATA);
    int n = 0;
    while(*temp != '\0'){
        if(*temp != '\n' && *temp != ' ') {
            buffer[n] = (*temp);
            n++;
        }
        temp++;
    }
    buffer[n] = '\0';
    return buffer;
}

/*
使用scanf编写函数，按照文件名读取文件内容，每次读取单个字符，但是不要越过（文件和缓冲区的）末尾。
使这个函数接受字符串大小来更加通用，并且确保无论什么情况下字符串都以'\0'结尾。
*/

void get_content(char* file_name, Person* person){
    FILE* f = fopen(file_name, "r");
    assert(f);

    char* buffer;
    char* buffer_pointer;
    int read_success;
    while(read_success = fscanf(f, "%c", buffer_pointer) != EOF){
        assert(read_success);
        buffer_pointer++;
    }
    *buffer_pointer = '\0';

    /// case..
    // e.g. case income:
    person->income = atoi(buffer);
}


// void get_content(char* file_name){
//     FILE* f = fopen(file_name, "r");
//     assert(f);

//     char* buffer;
//     char* buffer_pointer;

//     assert(scanf("%c", buffer_pointer));
    
// }



// #ifndef A
// #define _concat(A,B) (#A)(#B)A##B
// #endif

/*
fscanf
fgets
fopen
freopen
fdopen
fclose
fcloseall
fgetpos
fseek
ftell
rewind
fprintf
fwrite
fread
*/