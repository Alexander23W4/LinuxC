#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MEMORY_ALLOCATION_ERROR  "MEMORY ALLOCATION ERROR"
#define REGULAR_ARRAY_SIZE  128U

typedef struct{
    int32_t profile_code;
    int32_t regular_price;
    const char* author;
    char whatever;
}Book;


void _die(const char* info){
    if(errno){
        perror(info);
    }
    else{
        printf("ERROR: %s\n", info);
    }
    exit(1);
}

void V_struct_mem_test__T(size_t size){
    Book* p_library__Book = (Book*)malloc(sizeof(Book) * size);
    if(!p_library__Book){
        _die(MEMORY_ALLOCATION_ERROR);
    }
    printf("First: %p\n", p_library__Book);
    printf("Second: %p\n", p_library__Book + 1);
    free(p_library__Book);
}

int main(int argc, char** argv){
    V_struct_mem_test__T(REGULAR_ARRAY_SIZE);
}
