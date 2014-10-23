#ifndef MY_STACK_C
#define MY_STACK_C

#include "my_stack.h"
#include "stddef.h"
#include <stdlib.h>
#define ElementsCount size
#define Array data


enum StackError {NOERROR, STACKPOINTERNULL, MALLOCERROR, STACKARRAYNULLPOINTER,
                 BROKENPOSITION, NOTENOUGHMEMORY, NOELEMENTS};

enum StackError stackerrno = NOERROR;

int const POISON = 13666;

my_stack_double * my_stack_double_new( size_t size)
{
    my_stack_double* Stack = NULL;
    Stack = (my_stack_double*) calloc(1, sizeof(double*) + sizeof(size_t) + size*sizeof(double));
    if (!Stack)
    {
        stackerrno = STACKPOINTERNULL;
        return 0;
    }
    Stack -> ElementsCount = size;
    Stack -> Array = (double*) malloc(Stack -> ElementsCount*sizeof(double));  //Stack -> Array initialized later,
                                                                               //cause want to put POISON in unused
                                                                               //elements of array for more protection

    if (Stack -> Array == NULL)
    {
        stackerrno = MALLOCERROR;
        return 0;
    }
    for (int i = 0; i < Stack -> ElementsCount; i++)                           //here it's initialized
    {
        Stack -> Array[i] = POISON;
    }

    Stack -> stack_pointer = Stack -> Array;
    return Stack;
}


int               my_stack_double_delete( my_stack_double * this)
{
    #define Stack this
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    free(Stack -> Array);
    Stack -> Array = NULL;
    Stack -> stack_pointer = 0;
    Stack -> ElementsCount = 0;
    Stack = NULL;
    return NOERROR;
    #undef Stack
}

size_t my_stack_double_size( my_stack_double * this)
{
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    return this -> size;
}

int my_stack_double_empty( my_stack_double * this)
{
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    for (int i = 0; i < this -> size; i++)
    {
        this -> data[i] = POISON;
    }
    this -> stack_pointer = this -> data;
    return NOERROR;
}

int my_stack_double_push( my_stack_double * this, double data)
{
    #define Stack this
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    if (Stack -> stack_pointer - Stack -> data < Stack -> ElementsCount)
    {
        *(Stack -> stack_pointer) = data;
        Stack -> stack_pointer ++;
        return NOERROR;
    }
    else
    {
        double* NewArray = (double*) realloc(Stack -> Array, (Stack -> ElementsCount + 1)*sizeof(double));
        if (!NewArray)
        {
            return NOTENOUGHMEMORY;
        }
        else
        {
            *(Stack -> stack_pointer) = data;
            Stack -> Array = NewArray;
            Stack -> ElementsCount++;
            Stack -> stack_pointer++;
            return NOERROR;
        }
    }
    #undef Stack
    return 0;
}

double my_stack_double_pop( my_stack_double * this)
{
    #define Stack this
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    if (Stack -> stack_pointer == Stack -> data)
    {
        return NOELEMENTS;
    }
    else
    {
        double Element = *(Stack -> stack_pointer - 1);
        *(Stack -> stack_pointer - 1) = POISON;
        Stack -> stack_pointer--;
        return Element;
    }
    #undef Stack
}

double my_stack_double_top( my_stack_double * this)
{
    #define Stack this
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    if (Stack -> stack_pointer == 0)
    {
        return NOELEMENTS;
    }
    else
    {
        return *(Stack -> stack_pointer - 1);
    }
}

int my_stack_double_swap( my_stack_double * this)
{
    if (this == NULL) return STACKPOINTERNULL;
    if (this -> Array == NULL) return STACKARRAYNULLPOINTER;
    double a = *(this -> stack_pointer - 1);
    *(this -> stack_pointer - 1) = *(this -> stack_pointer - 2);
    *(this -> stack_pointer - 2) = a;
    return 0;
}

void my_stack_double_dump( my_stack_double * this)
{
    #define Stack this
    printf("%s %d\n%s %d\n", "Size of Stack:", Stack -> ElementsCount, "Number of elements in stack:", Stack -> stack_pointer -
                                                                                                       Stack -> data);
    printf("%s \n", "Elements in stack:");
    for (int i = 0; i < Stack -> ElementsCount; i++)
    {
        printf("%d:%lg \n", i, Stack -> Array[i]);
    }
    #undef Stack
}



#endif // MY_STACK_C
