#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void Problem_C_4_2008();                                //    Problem C from 4th ... from year 2008

const int MaxTableSize = 50;
const int MaxAnswersCount = 2*MaxTableSize - 1;                       //    extra columns in table for counting sums

void Problem_C_1_2008();

const int MaxStringSize = 100003;                                //!    @warning Max Size of the typed string in ALL problems
         
void Problem_C_3_2008();

void Problem_A_6_2008();

void Problem_B_6_2008();

const int MaxNumberOfStudents = 10000;
const int MaxNameSize = 29;

struct student
{
    char name[MaxNameSize];
    int mark;
};

struct twostudents
{
    struct student Student1;
    struct student Student2;
};

void Problem_B_8_2008();

                                                         
int main()
{
    printf("%s %c", "Type the code of the problem:", '\n');
    int CodeOfProblem;
    scanf("%d", &CodeOfProblem);
    
    if (CodeOfProblem == 1)
    {
        Problem_C_4_2008();
    }
    
    if (CodeOfProblem == 2)
    {
        Problem_C_1_2008();
    }
    if (CodeOfProblem == 3)
    {
        Problem_C_3_2008();
    }
    if (CodeOfProblem == 4)
    {
        Problem_A_6_2008();
    }
    if (CodeOfProblem == 5)
    {
        Problem_B_6_2008();
    }
    if (CodeOfProblem == 6)
    {
        Problem_B_8_2008();
    }
}

void Problem_C_4_2008()                                

{   
    printf("%s %c", "Type the size of table and its elements:", '\n');
    int TableSize = 0;         
    scanf("%d", &TableSize);
    
    int Table[MaxTableSize][MaxAnswersCount];            //    made our table
    for (int i = 0; i < MaxTableSize; i++) 
    {
        for (int j = 0; j < MaxAnswersCount; j++) 
        {
            Table[i][j] = 0;    
        }    
    }
                                                 
    for (int i = 0; i < TableSize; i++)                 //
    {                                                   //
        assert(i < MaxTableSize);                       //
        for (int j = 0; j < TableSize; j++)             //
        {                                               //    reading the items of table
            assert(j < MaxTableSize);                   //
            scanf("%d", &Table[i][j]);                  //
        }                                               //
    }                                                   //
    
    int answer[2*MaxTableSize - 1];
    for (int i = 0; i < 2*MaxTableSize - 1; i++) 
    {
        answer[i] = 0;        
    }
    
    int AnswersCount = 2*TableSize - 1;
    
    for (int k = 0; k < AnswersCount; k++) 
    {
        assert(k < MaxAnswersCount);
        answer[k] = 0;        
        for (int i = 0; i <= k && i < TableSize; i++)
        {
            answer[k] = answer[k] + Table[(TableSize - 1) - i][k - i];
        }
    }
    
    for (int i = 0; i < AnswersCount; i++) 
    {
        printf("%d %c", answer[i], ' ');    
    }
}



void Problem_C_1_2008()  
                                              
{   
    char ModifiedString[MaxStringSize];
    
    char String[MaxStringSize];
    int StringSize = 0;
    
    printf("%s %c", "Type your string with EOF in the end:", '\n');
    for (int i = 0; i < MaxStringSize; i++)
    {
        scanf("%c", &String[i]);
        if(i > 1 && String[i] == 'F' && String[i - 1] == 'O' && String[i - 2] == 'E') //    if last three characters are "EOF"
        {
            StringSize = i - 3;
            break;
        }
    }
    
    int ModifiedStringSize = 0;
    for (int i = 0; i < StringSize; i++) 
    {
        assert(i < MaxStringSize);
        if (String[i] != ' ') 
        {
            ModifiedString[ModifiedStringSize] = String[i];
        }
        if (String[i] == ' ')
        {
            ModifiedString[ModifiedStringSize] = ' ';
            while (String[i] == ' ') 
            {
                i++;    
            }
            i--;
        }
        ModifiedStringSize++;
    }
    
    for (int i = 0; i < ModifiedStringSize; i++) 
    {
        printf("%c", ModifiedString[i]);    
    }
}

void Problem_C_3_2008()
{
    printf("%s", "Type your string: \n");
    int ModifiedStringSize = 0;
    char Word[MaxStringSize];                                                           //here we'll put every word from inputted string
    char ModifiedString[MaxStringSize];                                                 //future result
    for (int l = 0; l < MaxStringSize; l++)                                             //counter of words
    {
        
        for (int i = 0; i < MaxStringSize; i++)                                         //
        {                                                                               //
            Word[i] = '0';                                                              //    initializing Word[]
        }                                                                               //
        
        for (int i = 0; i < MaxStringSize; i++)                                         //counter of characters
        {
            scanf("%c", &Word[i]);
            if (!(((int)'A' <= (int)Word[i] && (int)Word[i] <= (int)'Z') ||             //
                ((int)'a' <= (int)Word[i] && (int)Word[i] <= (int)'z')))                //if the character is NOT a letter
            {
                for (int j = i - 1; j >= 0; j--)                                        //
                {                                                                       //
                    ModifiedString[ModifiedStringSize] = Word[j];                       //rewriting Word into ModifiedString
                    ModifiedStringSize++;                                               //in opposite order
                }                                                                       //
                                                                                        
                ModifiedString[ModifiedStringSize] = Word[i];                           //
                ModifiedStringSize++;                                                   //rewriting the character which is not a letter
                break;                                                                  //in its place
            }                                                                           //
       
        }
        if (ModifiedStringSize >= 2 && ModifiedString[ModifiedStringSize - 1] == '\n')  //-1 because we've already increased  
        {                                                                               //ModifiedStringSize but havent written anything
            break;                                                                      //in the new position yet
        }                                                                               //2 because String must have at least one char.
        
    }
    
    for (int i = 0; i < ModifiedStringSize; i++) 
    {
        printf("%c", ModifiedString[i]);    
    }    
}

void Problem_A_6_2008()
{
    printf("%s", "Type the sizes of the table: \n");
    int Height = 0, Length = 0;
    scanf("%d %d", &Length, &Height);
    for (int i = 0; i < Height; i++) 
    {
        for (int j = 0; j < Length; j++)
        {
            printf("%d %c", j*Height + (i + 1), ' ');
        }    
        printf("%c", '\n');
    }
}

void Problem_B_6_2008()
{
    struct student Students[MaxNumberOfStudents];
    for (int i = 0; i < MaxNumberOfStudents; i++) 
    {
        Students[i].mark = 0;    
    }
    
    printf("%s", "Type the number of students: \n");
    int NumberOfStudents = 0;
    scanf("%d", &NumberOfStudents);
    
    printf("%s", "Type each student's name and his mark: \n");
    for (int i = 0; i < NumberOfStudents; i++) 
    {
        assert(i < MaxNumberOfStudents);
        scanf("%s %d", Students[i].name, &Students[i].mark);
    }
    
    for (int i = NumberOfStudents - 1; i > 0; i--) 
    {
        for (int j = 0; j < i; j++) 
        {
            if (strcmp(Students[j].name, Students[j + 1].name) > 0)
            {
                struct twostudents TwoStudents = {Students[j], Students[j + 1]};
                Students[j] = TwoStudents.Student2;
                Students[j + 1] = TwoStudents.Student1;
            }
        }    
    }
    
    for (int i = 0; i < NumberOfStudents; i++) 
    {
        printf("%s %c %d %c", Students[i].name, ' ', Students[i].mark, '\n');   
    }
    printf("%c", '\n');
    
    for (int i = NumberOfStudents - 1; i > 0; i--) 
    {
        for (int j = 0; j < i; j++) 
        {
            if (Students[j].mark - Students[j + 1].mark < 0)
            {
                struct twostudents TwoStudents = {Students[j], Students[j + 1]};
                Students[j] = TwoStudents.Student2;
                Students[j + 1] = TwoStudents.Student1;
            }
        }    
    }
    
    for (int i = 0; i < NumberOfStudents; i++) 
    {
        printf("%s %c %d %c", Students[i].name, ' ', Students[i].mark, '\n');
    }
}

void Problem_B_8_2008()
{
    printf("%s", "Type your string: \n");
    char String[MaxStringSize];
    int i = 0;                                                     // i means iterator
    while (String[i - 1] != '\n' || i < 2)                         //2 is because there must be at least 1 character, so we are looking 
    {                                                              //for \n just from the second symbol
        assert(i < MaxStringSize);
        scanf("%c", &String[i]);
        i++;    
    }
    
    int DigitsCount = 0, LettersCount = 0;
    for (int j = 0; j < i; j++) 
    {
        if ('0' <= String[j] && String[j] <= '9') 
        {
            DigitsCount++;    
        }
        if (('a' <= String[j] && String[j] <= 'z') || ('A' <= String[j] && String[j] <= 'Z'))
        {
            LettersCount++;
        }
    }
    printf("%c %s %d %c %s %d %c", '\n', "Digits =", DigitsCount, '\n', "Letters =", LettersCount, '\n');
}