#include <stdio.h>
#include "colors.h"

void    write_color(char *str, int color)
{
    printf("%c[%dm%s\n", 27, color, str);
}

int main(int ac, char **av)
{
    if (ac == 2)
    {
        write_color(av[1], magenta);
    }
    return (0);
}