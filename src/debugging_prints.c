#include "../inc/miniRT.h"

void    print_map(char **map)
{
    printf("\nPRINT MAP\n");
    int pos = 0;
    while (map[pos])
    {
        printf("%d : [%s]\n", pos, map[pos]);
        pos++;
    }
    printf("\n");
}