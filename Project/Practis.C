#include <stdio.h>
#include <math.h>

void binary(unsigned long val);

int binsearch(int x, int v[], int n);

int main(void)
{
    int x = 90;
    int n = 10;
    int v[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int z = binsearch(x, v, n);
    printf("%d", z);
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, mid, high;
    low = 0;
    high = n - 1;
    while(low < high)
    {
        mid = (low + high) / 2;
        if(x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if(x == v[mid])
        return mid;
    else
        return -1;
}

void binary(unsigned long val)
{
    for(int i = 7; i >= 0; i--)
    {
        printf("%d", (val >> i) & 1);
    }
    printf("\n");
}