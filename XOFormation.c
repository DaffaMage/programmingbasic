#include <stdio.h>

int main()
{
    int in, lo1, lo2;
    printf("INPUT : ");scanf("%d", &in);

    for (lo1=1;lo1<=in;lo1++)
    {
        for (lo2=1;lo2<=in;lo2++)
        {
            printf("X ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if (lo1%2==0)
                printf("O ");
            else
                printf("X ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if (lo2%2==0)
                printf("O ");
            else
                printf("X ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if ((lo1+lo2)%2==0)
                printf("O ");
            else
                printf("X ");
        }

        printf("\n");
    }

    printf("\n\n");

    for (lo1=1;lo1<=in;lo1++)
    {
        for (lo2=1;lo2<=in;lo2++)
        {
            if (lo1==lo2 || lo2==((in+1)-lo1))
                printf("X ");
            else
                printf("O ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if (lo1==1 || lo2==1 || lo1==in || lo2==in)
                printf("X ");
            else
                printf("O ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if ((lo1>=((in/2)+1) && lo2<=(in/2))|| (lo1<=(in/2) && lo2>=((in/2)+1)))
                printf("X ");
            else
                printf("O ");
        }
        printf("\t");

        for (lo2=1;lo2<=in;lo2++)
        {
            if (lo1==lo2 || lo2==((in+1)-lo1) || (lo1+lo2)%in==((in/2)+1) || (in/2)==(lo1-lo2) || (in/2)==(lo2-lo1))
                printf("X ");
            else
                printf("O ");
        }

        printf("\n");
    }
    return 0;
}
