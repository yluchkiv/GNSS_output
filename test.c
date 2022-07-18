#include <stdio.h>
int a = 0;
int b = 5;
int c = 8;

void ass(void)
{
    a = (b = ++c);
}

int main(void)
{
    ass();
    printf("%d %d %d\n", a = b, b ,c);
    return 0;
}

