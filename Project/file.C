#include <stdio.h>
#include <ctype.h>

void binary(unsigned long val);

unsigned getbits(unsigned x, int p, int n);

int setbits(unsigned char x, int p, int n, unsigned char y);

int invert(unsigned x, int n, int p);

int rightrot(unsigned x, int n);

int bitcount(unsigned x);

int lower(int c);

int binsearch(int x, int v[], int n);

void escape(char s[], char t[]);

void unescape(char s[], char t[]);

unsigned long next = 1;
int rand(void);
void srand(unsigned int seed);

int htoi(const char s[]);

void squeeze(char s1[], char s2[]);

int any(char s1[], char s2[]);

int atoi(char s[]);

void shellsort(int v[], int n);

int main(void)
{
    int v[10] = {10, 9, 12, 33, 220, 110, 99, 89, 900, 12};
    int n = 10;
    shellsort(v, n);
    printf("v: ");
    for(int i = 0; i < 10; i++) {
        printf(" %d", v[i]);
    }
    return 0;
}

void shellsort(int v[], int n)
{
    int gap, i, j, temp;
    for(gap = n/2; gap > 0; gap /= 2)
    {
        for(i = gap; i < n; i++)
        {
            for(j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

void escape(char s[], char t[])
{
    int c;
    int i, j = 0;
    for(i = 0; t[i] != '\0'; i++)
    {
        c = t[i];
        switch (c)
        {
        case '\n':
            s[j] = '\\';
            s[j+1] = 'n';
            j += 2;
            break;
        case '\t':
            s[j] = '\\'; s[j+1] = 't'; j += 2; break;
        default:
            s[j] = c; j++; break;
        }
    }
    s[j] = '\0';
}

void unescape(char s[], char t[])
{
    int i = 0, j = 0;

    while (s[i] != '\0') {
        if (s[i] == '\\' && s[i + 1] != '\0') {
            switch (s[i + 1]) {
                case 'n':
                    t[j++] = '\n';
                    i += 2;
                    break;
                case 't':
                    t[j++] = '\t';
                    i += 2;
                    break;
                case '\\':
                    t[j++] = '\\';
                    i += 2;
                    break;
                default:
                    t[j++] = s[i];  // انسخ الشرطة العكسية
                    i++;            // ثم عالج المحرف التالي في الدورة القادمة
                    break;
            }
        } else {
            t[j++] = s[i++];
        }
    }
    t[j] = '\0';
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

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}

int bitcount(unsigned x)
{
    int b;
    for(b = 0; x != 0; x &= (x - 1))
        b++;
    return b;
}

int rightrot(unsigned x, int n)
{
    int word_size = 8;
    n = n % word_size;
    int mask = ~(~0 << n);
    int lost = x & mask;
    lost = lost << (word_size - n);
    x = x >> n;
    return lost | x;
}

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 -n)) & ~(~0 << n);
}

int setbits(unsigned char x, int p, int n, unsigned char y)
{
    unsigned mask = ~(~0 << n);
    unsigned clear_mask = ~(mask << (p + 1 - n));
    x = x &clear_mask;
    y = (y & mask) << (p + 1 - n);
    return x | y;
}

int invert(unsigned x, int n, int p)
{
    unsigned mask = ~(~0 << n);
    int clean_mask = (mask << (p + 1 - n));
    x = x ^ clean_mask;
    return x;
}

void binary(unsigned long val)
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

int atoi(char s[])
{
    int i, n, sign;
    for(i = 0; isspace(s[i]); i++)
    ;
    sign = (s[i] == '-') ? -1:1;
    for(n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}