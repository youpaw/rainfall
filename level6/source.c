#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void(*func_ptr)(void);

void	n(void)
{
    system("/bin/cat /home/user/level7/.pass");
}

void	m(void)
{
    puts("Nope");
}

int main(int ac, char **av)
{

    char *str = malloc(64);
    func_ptr *func = malloc(4);
    *func = (void *)m;
    strcpy(str, av[1]);
    (**func)();
}
