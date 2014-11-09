#define DATA_T char*
#include "List.h"
#include <string.h>
#include <sys/stat.h>
#include <assert.h>

typedef struct
{
    list** Lists;
    long long unsigned (*hash_f)(const char*);
    long long unsigned size;
} table;

char* FileToArray(char* FileName);
long long unsigned hash1(const char*);
long long unsigned hash2(const char*);
long long unsigned hash3(const char*);
long long unsigned hash4(const char*);
long long unsigned hash5(const char*);
int table_add(table* here, char* data);
table* table_ctor(long long unsigned (*hash_f)(const char*), int size);
int table_dtor(table* destroy_me);
void table_dump(table* dump_me);
int table_ok(table* check_me);
element* finder(table* Table, char* str);

int main()
{
    char* buf = FileToArray("Onegin.txt");
    char* ptr = strtok(buf, " \t\n.,-!?():;'");

    table* Table = table_ctor(hash5, 101);
    while (ptr != NULL)
    {
        char* s = (char*) calloc(30, sizeof(char));
        assert(s);
        strcpy(s, ptr);
        table_add(Table, s);
        ptr = strtok(NULL, " \t\n.,-!?():;'*");
    }
    free(buf);
    FILE* result = fopen("Hash5.csv", "w");
    for (int i = 0; i < Table -> size; i++)
      fprintf(result, "%d; ", Table -> Lists[i] -> ElCount);
    fclose(result);
    table_dtor(Table);
    return 0;
}

table* table_ctor(long long unsigned (*hash_f)(const char*), int size)
{
    table* result = (table*) calloc(1, sizeof(table));
    if (!result) return NULL;
    result -> Lists = (list**) calloc(size, sizeof(list*));
    if (result -> Lists == NULL)
    {
        free(result);
        return NULL;
    }
    for (long long unsigned i = 0; i < size; i++)
    {
        result -> Lists[i] = list_ctor();
    }
    result -> hash_f = hash_f;
    result -> size = size;
    if (table_ok(result)) return result;
    else
    {
        free (result -> Lists);
        free (result);
        return NULL;
    }
}

int table_dtor(table* destroy_me)
{
    if (!table_ok(destroy_me)) return 0;
    for (long long unsigned i = 0; i < destroy_me -> size; i++)
    {
        list_dtor(destroy_me -> Lists[i]);
    }
    free(destroy_me -> Lists);
    destroy_me -> size = 0;
    free(destroy_me);
}

int table_ok(table* check_me)
{
    if (!check_me -> hash_f) return 0;
    if (!check_me -> size) return 0;
    for (long long unsigned i = 0; i < check_me -> size; i++)
    {
        if (!list_ok(check_me -> Lists[i])) return 0;
    }
    return 1;
}

void table_dump(table* dump_me)
{
    if (table_ok(dump_me)) printf("Table is ok\n");
    else printf("Table isn't ok\n");
    printf ("Size of the table %llu", dump_me -> size);
    for(long long unsigned i = 0; i < dump_me -> size; i++)
    {
        list_dump(dump_me -> Lists[i]);
    }
}

long long unsigned hash1(const char* s)
{
    return 1;
}

long long unsigned hash2(const char* s)
{
    return (int) s[0];
}

long long unsigned hash3(const char* s)
{
    return strlen(s);
}

long long unsigned hash4(const char* s)
{
    int sum = 0;
    for (int i = 0; ;i++)
    {
        if (s[i] == '\0') break;
        else sum += (int) s[i];
    }
    return sum;
}

long long unsigned hash5(const char* s)
{
    if (s[0] == '\0') return 0;
    if (s[1] == '\0') return (int) s[0];
    else
    {
        char* s1 = (char*) calloc(1, sizeof(s));
        strncpy(s1, s, strlen(s) - 1);
        int result = (hash5(s1) << 1) ^ (int) s[strlen(s) - 1];
        free(s1);
        return result;
    }
}

element* finder(table* Table, char* str)
{
    long long unsigned i = (*(Table -> hash_f))(str) % Table -> size;
    list* List = Table -> Lists[i];
    element* ptr = List -> head;
    for (int j = 0; j < List -> ElCount; j++)
    {
        if (!(strcmp(str, ptr -> data)))
        {
            return ptr;
        }
    }
    return NULL;
}

int table_add(table* here, char* data)
{
    if (!table_ok(here)) return 0;
    long long unsigned i = (*(here -> hash_f))(data) % here -> size;
    list* List = here -> Lists[i];
    if (!finder(here, data))
    {
        el_add(List, List -> head, data);
        return 1;
    }
    else return 0;
}

char* FileToArray(char* FileName)
{
    assert(FileName);
    FILE* File = fopen(FileName, "r");

    assert(File);

    struct stat buf;

    fstat(fileno(File), &buf);

    long long unsigned Length = (long long unsigned) buf.st_size;

    assert(Length);

    char* result = (char*) calloc(Length + 1, sizeof(*result));
    assert(result);

    for (int i = 0; i < Length; i++)
    {
        fscanf(File, "%c", &result[i]);
    }
    fclose(File);
    File = NULL;
    return result;
}







