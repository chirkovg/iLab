#include <stdio.h>
#include <math.h>

const int all_reals = -1;

struct Solutions
{
    double x1;
    double x2;
    int roots_count;
};

struct Solutions get_solutions(double a, double b, double c)
{
    struct Solutions solutions = {0, 0, 0};
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                solutions.roots_count = all_reals;
            }
            else 
            {
                solutions.roots_count = 0;
            }
        }
        else
        {
            solutions.roots_count = 1;
            solutions.x1 = -c/b;
        }
    }
    else 
    {
        double D = b*b - 4*a*c;
        if (D < 0)
        {
            solutions.roots_count = 0;
        }
        else if (D == 0) 
        {
            solutions.roots_count = 1;
            solutions.x1 = -b/(2*a);
        }
        else 
        {
        solutions.roots_count = 2;
        solutions.x1 = (-b + sqrt(D))/(2*a);
        solutions.x2 = (-b - sqrt(D))/(2*a);
        }
    }
    return solutions;
}

int main() 
{
    printf("%s %c", "Type the coefficients of quadratic equation:", '\n');
    double a = 0, b = 0, c = 0;
    scanf("%lg %lg %lg", &a, &b, &c);
    struct Solutions solutions = get_solutions(a, b, c);
    if (solutions.roots_count == 0) 
    {
        printf("%s %c","Error 404: solutions were not found", '\n');
    }
    else if (solutions.roots_count == 1) 
    {
        printf("%s %lg %c", "This equation has one root: x =", solutions.x1, '\n');
    }
    else if (solutions.roots_count == 2) 
    {
        printf("%s %lg %s %lg %c", "This equation has two roots: x =", solutions.x1,"and x =" , solutions.x2, '\n');
    }
    else 
    {
        printf("%s %c", "All reals are roots",'\n');
    }
	//тралала
    return 0;
}

