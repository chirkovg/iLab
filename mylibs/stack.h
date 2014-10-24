#include <stdlib.h>
#define POISON 13666

struct stack_t
{
    double* Array;
    int Position;
    int ElementsCount;
};

enum StackError {NOERROR, STACKPOINTERNULL, MALLOCERROR, STACKARRAYNULLPOINTER,
                 BROKENPOSITION, NOTENOUGHMEMORY, NOELEMENTS};

enum StackError stackerrno = NOERROR;


int Stack_ctor (struct stack_t* Stack, int ElementsAmount)
{
    if (!Stack)
    {
        stackerrno = STACKPOINTERNULL;
        return 0;
    }
    Stack -> ElementsCount = ElementsAmount;
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

    Stack -> Position = 0;
    return 1;
}

int Stack_Ok(struct stack_t* Stack)
{
    if (!Stack)
    {
        stackerrno = STACKPOINTERNULL;
        return 0;
    }
    if (Stack -> Array == NULL)
    {
        stackerrno = STACKARRAYNULLPOINTER;
        return 0;
    }
    if (Stack -> Position < 0 || Stack -> Position > Stack -> ElementsCount)
    {
        stackerrno = BROKENPOSITION;
        return 0;
    }
    for (int i = Stack -> Position; i < Stack -> ElementsCount; i++)
    {
        if (Stack -> Array[i] != POISON)
        {
            stackerrno = BROKENPOSITION;
            return 0;
            break;
        }
    }
    return 1;
}

char* stackerror(int code)
{
    if (code == NOERROR)
    {
        return "There's no errors with stack";
    }
    if (code == STACKPOINTERNULL)
    {
        return "Stack Pointer is invalid";
    }
    if (code == MALLOCERROR)
    {
        return "Malloc didn't work properly";
    }
    if (code == STACKARRAYNULLPOINTER)
    {
        return "Array in stack has invalid pointer";
    }
    if (code == BROKENPOSITION)
    {
        return "Something's bad with stack counter";
    }
    if (code == NOTENOUGHMEMORY)
    {
        return "There's not enough memory for your stack";
    }
    if (code == NOELEMENTS)
    {
        return "There's no elements in your stack";
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
                stackerrno = NOTENOUGHMEMORY;
                return 0;
            }
            else
            {
                Stack -> Array = NewArray;
                Stack -> ElementsCount++;
                Stack -> Position++;
                return 1;
            }
        }
    }
    return 0;
}

int Stack_pull(struct stack_t* Stack, double* Element)
{
    if(Stack_Ok(Stack))
    {
        if (Stack -> Position == 0)
        {
            stackerrno = NOELEMENTS;
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
        else printf ("%s\n%s\n" , "Stack is not ok!", stackerror(stackerrno));
    printf("%s %d\n%s %d\n", "Size of Stack:", Stack -> ElementsCount, "Number of elements in stack:", Stack -> Position);
    printf("%s \n", "Elements in stack:");
    for (int i = 0; i < Stack -> ElementsCount; i++)
    {
        printf("%d:%lg \n", i, Stack -> Array[i]);
    }
    return 0;
}
