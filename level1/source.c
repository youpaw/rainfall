#include <stdio.h>
#include <stdlib.h>

int run(void)
{
    fwrite("Good... Wait what?\n", 1, 19, stdout);
    system("/bin/sh");
}

int main(void)
{
    char buffer[60];

    gets(buffer);
}