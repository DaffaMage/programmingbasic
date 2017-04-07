/***************************************************************
BY DAFFA THE MAGE

A SHORT, SIMPLE PROGRAM TO CHECK IF A NUMBER IS PRIME
****************************************************************/
#include <stdio.h>
#include <stdlib.h>

/*Copy from this line*/
///If you need this program, just took the function and the globals
#define PRIME_FALSE 0
#define PRIME_TRUE 1

int isPrime(int x)
{
    int c;
    ///First, we validate it's within the scope. Prime's Law implicitly states the scope starts from 2
    if (x<2)
        return PRIME_FALSE;
    ///By utilizing Prime Numbers Law, we can just make a check from 2 to x-1
    ///Prime Numbers Law : any number that can be divided by any number except 1 and that number itself is not a prime
    for (c=2;c<x;c++)
    {
        if (x%c==0)
            return PRIME_FALSE;
    }
    return PRIME_TRUE;
}
/*End of copy*/

///Now, test time
int main()
{
    int number,i;
    scanf("%d", &number); ///input number

    for (i=1;i<=number;i++)
    {
        if (isPrime(i))
            printf("%d\t", i);
    }

    return 0;
}
