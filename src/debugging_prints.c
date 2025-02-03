/*
This file is for Debugging functions only. So all the lovely things
that help in coding, but should under no circumstances still be in the
code for an evaluation.
*/

#include "../inc/miniRT.h"

/*
takes a two dimensional array of characters and prints it in the format
Index : [map[index]]\n
*/
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


void	print_triplet(float *triplet)
{
	printf("%f , %f , %f\n", triplet[0], triplet[1], triplet[2]);
}