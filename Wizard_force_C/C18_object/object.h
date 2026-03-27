/*
C预处理器的工作原理是，如果你给它一个文件，比如.c文件，它会处理以#（井号）字符开头的各种文本。
当它遇到一个这样的文本时，它会对输入文件中的文本做特定的替换。
C预处理器的主要优点是他可以包含其他文件，并且基于该文件的内容对它的宏列表进行扩展。
*/


#ifndef _object_h
#define _object_h

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>

// enum & function_pointer  is flexible 

typedef enum {
    NORTH, SOUTH, EAST, WEST
} Direction;    // enum -> a group of state parameters

typedef struct {    // different character has different locomotive behaviour
    char *description;
    int (*init)(void *self);
    void (*describe)(void *self);
    void (*destroy)(void *self);
    void *(*move)(void *self, Direction direction);
    int (*attack)(void *self, int damage);
} Object;

// default locomotive setting for Objects
int Object_init(void *self);
void Object_destroy(void *self);
void Object_describe(void *self);
void *Object_move(void *self, Direction direction);
int Object_attack(void *self, int damage);
void *Object_new(size_t size, Object proto, char *description);

#define NEW(T, N) Object_new(sizeof(T), T##Proto, N)
#define _(N) proto.N

#endif