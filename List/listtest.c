#define DATA_T double
#include "List.h"

int main()
{
    list* List = list_ctor();
    list_dump(List);
    el_add(List, List -> head, 5);
    list_dump(List);
    el_add(List, List -> head, 5);
    list_dump(List);
    el_add(List, List -> head, 5);
    list_dump(List);
    el_add(List, List -> head, 5);
    list_dump(List);
    el_add(List, List -> head, 5);
    list_dump(List);
}
