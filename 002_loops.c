#include <stdio.h>

int main(void)
{
    int sum, iterator;

    sum = 0;
    while (sum < 100)
    {
        sum = sum + 1;
    }
    printf ("%d\n", sum);
    
    sum = 0;
    for (iterator = 0; sum < 100; iterator = iterator + 1)
    {
        sum = sum + 1;
    }
    printf ("%d\n", sum);

    sum = 0;
    do
    {
        sum = sum + 1;
    }while (sum < 100);

    printf ("%d\n", sum);

    return 0;
}