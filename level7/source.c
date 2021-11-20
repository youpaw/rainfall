#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char	c[68];

void	m(void)
{
    printf("%s - %d\n", c, (int)time(0));
}

int		main(int ac, char **av)
{
    int		*b1;
    int		*b2;

    b1 = malloc(8);
    b1[0] = 1;
    b1[1] = (int)malloc(8);

    b2 = malloc(8);
    b2[0] = 2;
    b2[1] = (int)malloc(8);

    strcpy((char *)b1[1], av[1]);
    strcpy((char *)b2[1], av[2]);

    fgets(c, 68, fopen("/home/user/level8/.pass", "r"));
    puts("~~");
    return (0);
}