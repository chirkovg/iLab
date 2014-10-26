#ifndef _STACK_H
#define _STACK_H


#include <stdlib.h>
#include <stdio.h>
#define POISON 13666

struct stack_t
{
    double* Array;
    int Position;
    int ElementsCount;
};

enum StackError {NOERROR = 0, STACKPOINTERNULL = 1, MALLOCERROR = 2, STACKARRAYNULLPOINTER = 3,
                 BROKENPOSITION = 4, NOTENOUGHMEMORY = 5, NOELEMENTS = 6};

enum StackError Stack_errno = NOERROR;

int Stack_Ok(struct stack_t* Stack);


int Stack_ctor (struct stack_t* Stack, int ElementsAmount)
{
    if (!Stack)
    {
        Stack_errno = STACKPOINTERNULL;
        return 0;
    }
    Stack -> ElementsCount = ElementsAmount;
    Stack -> Array = (double*) malloc(Stack -> ElementsCount*sizeof(double));  //Stack -> Array initialized later,
                                                                               //cause want to put POISON in unused
                                                                               //elements of array for more protection

    if (Stack -> Array == NULL)
    {
        Stack_errno = MALLOCERROR;
        return 0;
    }
    for (int i = 0; i < Stack -> ElementsCount; i++)                           //here it's initialized
    {
        Stack -> Array[i] = POISON;
    }
    Stack -> Position = 0;
    if (Stack_OK(Stack)) return 1;
    else return 0;
}

int Stack_Ok(struct stack_t* Stack)
{
    if (!Stack)
    {
        Stack_errno = STACKPOINTERNULL;
        return 0;
    }
    if (Stack -> Array == NULL)
    {
        Stack_errno = STACKARRAYNULLPOINTER;
        return 0;
    }
    if (Stack -> Position < 0 || Stack -> Position > Stack -> ElementsCount)
    {
        Stack_errno = BROKENPOSITION;
        return 0;
    }
    for (int i = Stack -> Position; i < Stack -> ElementsCount; i++)
    {
        if (Stack -> Array[i] != POISON)
        {
            Stack_errno = BROKENPOSITION;
            return 0;
            break;
        }
    }
    return 1;
}

char* stackerror(int code)
{
    switch(code)
    {
        case NOERROR: return "There's no errors with stack";
        case STACKPOINTERNULL: return "Stack Pointer is invalid";
        case MALLOCERROR: return "Malloc didn't work properly";
        case STACKARRAYNULLPOINTER: return "Array in stack has invalid pointer";
        case BROKENPOSITION: return "Something's bad with stack counter";
        case NOTENOUGHMEMORY: return "There's not enough memory for your stack";
        case NOELEMENTS: return "There's no elements in your stack";
        default: return "Something wrong with Stack_errno";
    }
}


int Stack_dtor (struct stack_t* Stack)
{
    if (Stack_Ok(Stack))
    {
        free(Stack -> Array);
        Stack -> Array = NULL;
        Stack -> Position = 0;
        Stack -> ElementsCount = 0;
        Stack = NULL;
        return 1;
    }
    return 0;
}

int Stack_push(struct stack_t* Stack, double Element)
{
    if (Stack_Ok(Stack))
    {
        if (Stack -> Position < Stack -> ElementsCount)
        {
            Stack -> Array[Stack -> Position] = Element;
            Stack -> Position ++;
            return 1;
        }
        else
        {
            double* NewArray = (double*) realloc(Stack -> Array, (Stack -> ElementsCount + 1)*sizeof(double));
            if (!NewArray)
            {
                Stack_errno = NOTENOUGHMEMORY;
                return 0;
            }
            else
            {
                Stack -> Array = NewArray;
                Stack -> Array[Stack -> Position] = Element;
                Stack -> ElementsCount++;
                Stack -> Position++;
                return 1;
            }
        }
    }
    return 0;
}

int Stack_pop(struct stack_t* Stack, double* Element)
{
    if(Stack_Ok(Stack))
    {
        if (Stack -> Position == 0)
        {
            Stack_errno = NOELEMENTS;
            return 0;
        }
        else
        {
            *Element = Stack -> Array[Stack -> Position - 1];
            Stack -> Array[Stack -> Position - 1] = POISON;
            Stack -> Position--;
            return 1;
        }
    }
    else return 0;
}
int Stack_dump(struct stack_t* Stack)
{
    if (Stack_Ok(Stack)) printf("%s \n", "Stack is ok");
        else printf ("%s\n%s\n" , "Stack is not ok!", stackerror(Stack_errno));
    printf("%s %d\n%s %d\n", "Size of Stack:", Stack -> ElementsCount, "Number of elements in stack:", Stack -> Position);
    printf("%s \n", "Elements in stack:");
    for (int i = 0; i < Stack -> ElementsCount; i++)
    {
        printf("%d:%lg \n", i, Stack -> Array[i]);
    }
    return 0;
}


#endif   
//_STACK_H
