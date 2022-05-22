#include <stdio.h>
#include <cmath>

int main()
{
    int words[10] = {-1, 2, 3, 4, -5, 6, 7, 8, 9, -10};
    int sum = 0;
    for (int i = 0; i < sizeof(words)/sizeof(words[0]); i++)
    {
        sum = sum + abs(words[i]);
    }
    printf("sum = %d\n", sum);
    
    return 0;
}