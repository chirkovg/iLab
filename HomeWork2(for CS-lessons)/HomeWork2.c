#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <io.h>

/*!  \brief Converts text from file to Array
 *   @param FileName[] is the name of file copied 
 *   @return Pointer to array of chars
 *   @warning free result after using!
 */
char* FileToArray(char FileName[]);   
            
                  
/*!  \brief Finds beginnings of lines in the string
 *   @param String is the pointer to string analised
 *   @return Pointer to array of char pointers(pointer to array of strings)
 *   @warning free result after using!
 */
char** BegOfLinesFinder(char* String);                  
                    
                                                         
/*!  \brief Counts the lines in string                                                         
 *   @param String is the pointer to string analised                                                         
 *   @return number of lines in String                                                         
 */                                                         
int CountLines(char* String);                           
                                                         
                                                         
/*!  \brief strcmp() equivalent for qsort() 
 *   @param pointers to two strings compared                                                        
 *   @return integer > 0, if str1 > str2;
 *           0, if str1 = str2;
 *           integer < 0, if str2 < str1
 */
int StrCmp(const void* str1, const void* str2);         
                                                         
                                                         

int main()
{
    char* Onegin = FileToArray("Onegin.txt");
    int Lines = CountLines(Onegin);

    char** Text = BegOfLinesFinder(Onegin);

    qsort(Text, Lines, sizeof(*Text), StrCmp);

    FILE* ModifiedFile = fopen("OneginModified.txt", "w");
    for (int i = 0; i < Lines; i++)
    {
        fprintf(ModifiedFile, "%s \n", Text[i]);
    }
    fclose(ModifiedFile);
    ModifiedFile = NULL;

    free(Onegin);
    free(Text);
    return 0;
}

char* FileToArray(char* FileName)
{
    assert(FileName);
    FILE* File = fopen(FileName, "r");
    assert(File);

    long Length = _filelength(_fileno(File));
    assert(Length != 1L);

    char* result = (char*) calloc(Length + 1, sizeof(*result));
    assert(result != NULL);

    for (int i = 0; result[i - 1] != '\0'; i++)
    {
        fscanf(File, "%c", &result[i]);
    }
    fclose(File);
    File = NULL;
    return result;
}

int CountLines(char* String)
{
    assert(String);
    int result = 1;
    char* Pointer = String;
    while(Pointer = strchr(Pointer, '\n'))
    {
        result++;
        Pointer++;
    }
    return result;
}

char** BegOfLinesFinder(char* String)
{
    assert(String);
    int Lines = CountLines(String);
    char** result = (char**) calloc(Lines, sizeof(*result));
    char* CurrentPointer = String;
    result[0] = String;
    int Length = strlen(String);
    for (int i = 1; i < Lines; i++)
    {
        assert(i > 0);
        CurrentPointer = strchr(CurrentPointer, '\n') + 1;
        assert(CurrentPointer && (CurrentPointer <= (char*)String + Length)
               && (CurrentPointer > (char*)String));
        result[i] = CurrentPointer;
        *(CurrentPointer - 1) = '\0';
    }
    return result;
}

int StrCmp(const void* str1, const void* str2)
{
    assert(str1 && str2);
    char* x = *((char**) str1);
    char* y = *((char**) str2);
    return strcmp(x, y);
}
