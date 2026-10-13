#include <stdio.h>

#define SET_ON 0b00101110

unsigned long next = 1;
int rand(void);
void srand(unsigned int seed);

int htoi(const char s[]);

void squeeze(char s1[], char s2[]);

int any(char s1[], char s2[]);

void binary(unsigned char val);


main()
{
    int x = 0b00101101;
    x | SET_ON;
    binary(x);
    return 0;
}

void binary(unsigned char val)
{
    for(int i = 7; i >= 0; i--)
    {
        printf("%d", (val >> i) & 1);
    }
    printf("\n");
}


int htoi(const char s[])
{
    int i = 0;
    int result = 0;
    int c;
    if(s[i] == '0')
    {
        i++;
        if(s[i] == 'x' || s[i] == 'X')
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    for(i ; s[i] != '\0'; i++)
    {
        
        if(s[i] >= '0' && s[i] <= '9')
        {
            c = s[i] - '0';
        }
        else if(s[i] >= 'a' && s[i] <= 'f')
        {
            c = s[i] - 'a' + 10;
        }
        else if(s[i] >= 'A' && s[i] <= 'F')
        {
            c = s[i] - 'A' + 10;
        }
        else
        {
            break;
        }
        result = (result * 16) + c;
    }
    return result;
}

int rand(void)
{
    next = next * 1103515242 + 12345;
    return (unsigned int) (next /65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

void squeeze(char s1[], char s2[])
{
    int i, j, x, y;
    for(i = j = 0; s1[i] != '\0'; i++)
    {
        y = 0;
        for(x = 0; s2[x] != '\0'; x++)
        {
            if(s1[i] == s2[x])
            {
                y = 1;
                break;
            }
        }
        if(y == 0)
        {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}

int any(char s1[], char s2[])
{
    int i, j, x;
    for(i = 0; s1[i] != '\0'; i++)
    {
        x = 0;
        for(j = 0; s2[j] != '\0'; j++)
        {
            if(s1[i] == s2[j])
            {
                return i;
            }
        }
    }
    return -1;
}