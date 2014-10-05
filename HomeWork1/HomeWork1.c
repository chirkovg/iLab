#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>


void Problem_C_4_2008();                                //    Problem C from 4th ... from year 2008

const int MaxTableSize = 50;
const int MaxAnswersCount = 2*MaxTableSize - 1;                       //    extra columns in table for counting sums

void Problem_C_1_2008();

const int MaxStringSize = 100003;                                //!    @warning Max Size of the typed string in ALL problems
         
void Problem_C_3_2008();

void Problem_A_6_2008();

void Problem_B_6_2008();

void Problem_C_1_2007();

int Weigh(int mass);

const int MaxNumberOfStudents = 10000;
const int MaxNameSize = 29;

struct student
{
    char name[MaxNameSize];
    int mark;
};

void Problem_B_8_2008();

                                                         
int main()
{
    printf("%s %c", "Type the code of the problem:", '\n');
    int CodeOfProblem = 0;
    scanf("%d", &CodeOfProblem);
    
    switch(CodeOfProblem)
    {
        case 1: 
        {
            Problem_C_4_2008();
            break;
        }
        case 2: 
        {
            Problem_C_1_2008();
            break;
        }
        case 3: 
        {
            Problem_C_3_2008();
            break;
        }
        case 4: 
        {
            Problem_A_6_2008();
            break;
        }
        case 5: 
        {
            Problem_B_6_2008();
            break;
        }
        case 6: 
        {
            Problem_B_8_2008();
            break;
        }
        case 7: 
        {
            Problem_C_1_2007();
            break;
        }
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
        assert(i >= 0);
        for (int j = 0; j < MaxAnswersCount; j++) 
        {
            assert(j >= 0);
            Table[i][j] = 0;    
        }    
    }
                                                 
    for (int i = 0; i < TableSize; i++)                 //
    {                                                   //
        assert(i < MaxTableSize);                       //
        assert(i >= 0);                                 //
        for (int j = 0; j < TableSize; j++)             //
        {                                               //
            assert(j >= 0);                             //    reading the items of table
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
        assert(k >= 0);
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
    for (int i = 0; i < MaxStringSize; i++) 
    {
        String[i] = '\n';    
    }
    int StringSize = 0;
    
    printf("%s", "Type your string with EOF in the end:\n");
    for (int i = 0; i < MaxStringSize; i++)
    {
        assert(i >= 0);
        scanf("%c", &String[i]);
        if(i > 1 && strncmp(&String[i - 3], "EOF", 3) == 0) //    3 because we need to compare only 3 last letters
        {
            StringSize = i - 3;
            break;
        }
    }
    
    int ModifiedStringSize = 0;                                                        //this is iterator
    for (int i = 0; i < StringSize; i++) 
    {
        assert(i < MaxStringSize);
        assert(i >= 0);
        if (isspace(String[i]) == 0) 
        {
            ModifiedString[ModifiedStringSize] = String[i];
        }
        if (isspace(String[i]))
        {
            ModifiedString[ModifiedStringSize] = ' ';
            while (isspace(String[i])) 
            {
                i++;    
            }
            i--;
        }
        ModifiedStringSize++;
    }
        puts(ModifiedString);    
}

void Problem_C_3_2008()
{
    printf("%s", "Type your string: \n");
    int ModifiedStringSize = 0;
    
    char Word[MaxStringSize];                                                           //here we'll put every word from inputted string
    char ModifiedString[MaxStringSize];                                                 //future result
    for (int i = 0; i < MaxStringSize; i++) 
    {
        assert(i >= 0);
        assert(i < MaxStringSize);
        ModifiedString[i] = '0';
        Word[i] = '0';
    }
    
    for (int l = 0; l < MaxStringSize; l++)                                             //counter of words 
    {
        for (int i = 0; i < MaxStringSize; i++)                                         //
        {                                                                               //
            assert(i >= 0);                                                             //
            Word[i] = '0';                                                              //    initializing Word[]
        }                                                                               //
        
        for (int i = 0; i < MaxStringSize; i++)                                         //counter of characters
        {
            assert(i >= 0);
            scanf("%c", &Word[i]);
            if (isalpha(Word[i]) == 0)                                                  //if the character is NOT a letter
            {
                for (int j = i - 1; j >= 0; j--)                                        //
                {                    
                    assert(j < MaxStringSize);                                                   //
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
    puts(ModifiedString);
}

void Problem_A_6_2008()
{
    printf("%s", "Type the sizes of the table: \n");
    int Height = 0, Length = 0;
    scanf("%d %d", &Length, &Height);
    for (int i = 0; i < Height; i++) 
    {
        assert(i >= 0);
        for (int j = 0; j < Length; j++)
        {
            assert(j >= 0);
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
        for(int j = 0; j < MaxNameSize; j++) Students[i].name[j] = '0'; 
    }
    
    printf("%s", "Type the number of students: \n");
    int NumberOfStudents = 0;
    scanf("%d", &NumberOfStudents);
    
    printf("%s", "Type each student's name and his mark: \n");
    for (int i = 0; i < NumberOfStudents; i++) 
    {
        assert(i < MaxNumberOfStudents);
        assert(i >= 0);
        scanf("%s %d", Students[i].name, &Students[i].mark);
    }
    
    for (int i = NumberOfStudents - 1; i > 0; i--)                                 //
    {                                                                              //
        assert(i <= NumberOfStudents);                                             //
        for (int j = 0; j < i; j++)                                                //
        {                                                                          //
            assert(j >= 0);                                                        //
            if (strcmp(Students[j].name, Students[j + 1].name) > 0)                //
            {                                                                      //    sorting
                struct student SwapStudents = Students[j];                         //
                Students[j] = Students[j + 1];                                     //
                Students[j + 1] = SwapStudents;                                    //
            }                                                                      //
        }                                                                          //
    }                                                                              //
    
    for (int i = 0; i < NumberOfStudents; i++)                                     //
    {                                                                              //
        assert(i >= 0);                                                            //
        printf("%s %c %d %c", Students[i].name, ' ', Students[i].mark, '\n');      //    printing students
    }                                                                              //
    printf("%c", '\n');                                                            //
    
    for (int i = NumberOfStudents - 1; i > 0; i--)                                 //
    {                                                                              //
        assert(i <= NumberOfStudents);                                             //
        for (int j = 0; j < i; j++)                                                //
        {                                                                          //
            assert(j >= 0);                                                        //
            if (Students[j].mark - Students[j + 1].mark < 0)                       //
            {                                                                      //    sorting
                struct student SwapStudents = Students[j];                         //
                Students[j] = Students[j + 1];                                     //
                Students[j + 1] = SwapStudents;                                    //
            }                                                                      //
        }                                                                          //
    }                                                                              //
    
    for (int i = 0; i < NumberOfStudents; i++)                                     //
    {                                                                              //
        assert(i >= 0);                                                            //    printing
        printf("%s %c %d %c", Students[i].name, ' ', Students[i].mark, '\n');      //
    }                                                                              //
}

void Problem_B_8_2008()
{
    printf("%s", "Type your string: \n");
    char String[MaxStringSize];
    int i = 0;                                                     // i means iterator
    while (String[i - 1] != '\n' || i < 2)                         //2 is because there must be at least 1 character, so we are looking 
    {                                                              //for \n just from the second symbol
        assert(i < MaxStringSize);
        assert(i >= 0);
        scanf("%c", &String[i]);
        i++;    
    }
    
    int DigitsCount = 0, LettersCount = 0;
    for (int j = 0; j < i; j++) 
    {
        assert(j < MaxStringSize);
        if (isdigit(String[j])) 
        {
            DigitsCount++;    
        }
        if (isalpha(String[j]))
        {
            LettersCount++;
        }
    }
    printf("%c %s %d %c %s %d %c", '\n', "Digits =", DigitsCount, '\n', "Letters =", LettersCount, '\n');
}

int Weigh(int mass)
{
    for (int i = 0; 4*i + 2 <= mass; i++) 
    {
        if (mass == 4*i + 2) return 0; 
    }
    for (int i = 0; pow(4,i) <= mass; i++) 
    {
        if (mass == pow(4,i)) return 1;     
    }
    for (int i = 0; 4*i - 1 <= mass; i++) 
    {
        if ((4*i) == mass|| (4*i - 1) == mass || (4*i + 1) == mass) 
        {
            int j = i;
            return Weigh(j);
        }
    }
    assert("No condition worked" && 0);                                          // in case none of ifs works, 
                                                             //in other cases this assert is not destinated
                                                             //to be sure that some value from Weigh(mass) is returned
}

void Problem_C_1_2007()
{
    int mass = 0;
    printf("%s", "Type your number \n");
    scanf("%d", &mass);
    if (Weigh(mass) == 1) printf("%s", "YES \n");
    if(Weigh(mass) == 0) printf("%s", "NO \n");
}