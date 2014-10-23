#ifndef MY_STACK_H
#define MY_STACK_H

#include <stddef.h> //reqired for size_t

typedef struct
{
    double * data;
    double * stack_pointer;
    size_t size;
} my_stack_double;

my_stack_double * my_stack_double_new( size_t size);
int               my_stack_double_delete( my_stack_double * this);

size_t my_stack_double_size( my_stack_double * this);
int my_stack_double_empty( my_stack_double * this);

int my_stack_double_push( my_stack_double * this, double data);
double my_stack_double_pop( my_stack_double * this);
double my_stack_double_top( my_stack_double * this);
int my_stack_double_swap( my_stack_double * this);

void my_stack_double_dump( my_stack_double * this);

#endif  //MY_STACK_H
