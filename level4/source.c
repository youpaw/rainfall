#include <stdio.h>
#include <stdlib.h>

int m;

void p(char *buff)
{
    char str[24];
    printf(buff);
}

void n(void)
{
    char buff[520];

    fgets(buff, 512, stdin);
    p(buff);
    if (m == 64)
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
}

int main(void)
{
    n();
}
