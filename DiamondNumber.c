#include <stdio.h>

int main()
{
int i, j, n;
    printf("Depth of diamond : ");scanf("%d",&n);

    for (i=0;i<=n;i++)
    {
        for (j=n-i;j>=0;j--)
        {
            printf(" ");
        }
        for (j=0;j<=i;j++)
        {
                printf("%d", j%10);
        }
        for (j=i-1;j>=0;j--)
        {
                printf("%d", j%10);
        }
        printf("\n");
    }

    for (i=n-1;i>=0;i--)
    {
        for (j=n-i;j>=0;j--)
        {
            printf(" ");
        }
        for (j=0;j<=i;j++)
        {
            printf("%d", j%10);
        }
        for (j=i-1;j>=0;j--)
        {
            printf("%d", j%10);
        }
        printf("\n");
    }
    return 0;
}
