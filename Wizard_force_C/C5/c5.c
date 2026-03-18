#include <stdio.h>
#include <stdint.h>
int main(int argc, char* argv[])
{
    uint8_t _u8_distance = 100;
    float f_power = 2.345f;
    double lf_super_power = 2123.1412;
    char c_initial = 'A';
    char s_first_name[] = "Alexandre";
    char s_last_name[] = "Wang";

    printf("I'm %u mileds away\n", _u8_distance);
    printf("You have %.2f level of power\n", f_power);
    printf("You have %lf level of superpower\n", lf_super_power);
    printf("I have an initial %c \n", c_initial);
    printf("My first name is %s \n", s_first_name);

    return 0;
}

// extra question:
void test(){
    float power = 1.22;
    printf("You have %d levels of power.\n", power);

    int distance = 100;
    printf("%d\n", distance); 
    printf("%o\n", distance);  
    printf("%x\n", distance);  
    printf("%X\n", distance); 

    printf("%10d\n", distance);   // right width
    printf("%-10d\n", distance);  // light width

    printf("%e\n", distance);   // scientific

    printf("%s\n", " ");

}



