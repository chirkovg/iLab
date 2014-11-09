#ifndef _LIST_H
#define _LIST_H


#include <stdio.h>
#include <stdlib.h>

typedef DATA_T data_t;

struct trololo;
typedef struct trololo element;

struct trololo
{
    data_t data;
    element* next;
    element* prev;
};

typedef struct
{
    int ElCount;
    element* head;
    element* tail;
} list;

list* list_ctor();
int list_ok(list* check_me);
int list_dtor(list* delete_me);
void list_dump(list* dump_me);
void el_dump(element* dump_me);
element* el_delete(list* List, element* delete_me);
element* el_add(list* List, element* prev, data_t data);
int element_ok(element* check_me);


list* list_ctor()
{
    list* result = (list*) calloc(1, sizeof(list));
    return result;
}

int list_ok(list* check_me)
{
    if (check_me == NULL) return 0;
    element* ptr = check_me -> head;
    int i = 0;
    for (i = 0; i < check_me -> ElCount; i++)
    {
        if (ptr == NULL) break;
        if (element_ok(ptr)) ptr = ptr -> next;
        else return 0;
    }
    if (i == check_me -> ElCount)
    {
        ptr = check_me -> tail;
        i = 0;
        for (i = 0; i < check_me -> ElCount; i++)
        {
            if (ptr == NULL) break;
            if (element_ok(ptr)) ptr = ptr -> prev;
            else return 0;
        }
        if (i == check_me -> ElCount) return 1;
    }
    return 0;
}

int list_dtor(list* delete_me)
{
    if (!list_ok(delete_me)) return 0;
    element* ptr = delete_me -> head;
    for (int i = 0; i < delete_me -> ElCount; i++)
    {
        ptr = el_delete(delete_me, ptr);
        if (!ptr) return 0;
    }
    free(delete_me);
    return 1;
}

void list_dump(list* dump_me)
{
    if (list_ok(dump_me)) printf ("List is ok\n");
    else printf("List isn't ok\n");
    printf ("Number of elements %d\n", dump_me -> ElCount);
    element* ptr = dump_me -> head;
    for (int i = 0; i < dump_me -> ElCount; i++)
    {
        el_dump(ptr);
        ptr = ptr -> next;
    }
}

element* el_delete(list* List, element* delete_me)
{

    if (!list_ok(List)) return NULL;
    element* next = delete_me -> next;
    element* prev = delete_me -> prev;
    if (next) next -> prev = prev; else List -> tail = prev;
    if (prev) prev -> next = next; else List -> head = next;
    List -> ElCount--;
    free(delete_me);
    return next;
}

element* el_add(list* List, element* prev, data_t data)
{
    if (!list_ok(List)) return NULL;
    element* newel = (element*) calloc(1, sizeof(element));
    if (!newel) return NULL;

    List -> ElCount++;
    newel -> data = data;

    if (prev == NULL)
    {
        if (List -> tail == NULL)
        {
            List -> head = List -> tail = newel;
            return newel;
        }
        else
        {
            newel -> prev = NULL;
            newel -> next = List -> head;
            List -> head = newel;
            return newel;
        }
    }

    element* next = prev -> next;
    newel -> prev = prev;
    newel -> next = next;
    if (next) next -> prev = newel; else List -> tail = newel;
    if (prev) prev -> next = newel; else List -> head = newel;

    return newel;
}

int element_ok(element* check_me)
{
    if (check_me == NULL) return 0;
    if (check_me -> prev == NULL)
    {
        if (check_me -> next == NULL ||
            check_me -> next -> prev == check_me) return 1;
        else return 0;
    }
    else if (check_me -> prev -> next == check_me)
    {
        if (check_me -> next == NULL ||
            check_me -> next -> prev == check_me) return 1;
        else return 0;
    }
}

void el_dump(element* dump_me)
{
    if (element_ok(dump_me)) printf ("Element is ok, ");
    else printf ("Element isn't ok, ");
    printf ("Address: %p, ", dump_me);
    printf ("Prev: %p, " , dump_me -> prev);
    printf ("Next: %p\n", dump_me -> next);
}


#endif // _LIST_H
