/*
This file is for Debugging functions only. So all the lovely things
that help in coding, but should under no circumstances still be in the
code for an evaluation.
*/

#include "../inc/miniRT.h"

static void	print_col(t_color *c, const char *msg)
{
	if (msg)
		printf("%s RGB ", msg);
	else
		printf("Undefined element's RGB ");
	printf("%i,", c->r);
	printf("%i,", c->g);
	printf("%i\n", c->b);
}

static void	print_point(t_point *p, const char *msg)
{
	if (msg)
		printf("%s point ", msg);
	else
		printf("Undefined element's point ");
	printf("x: %f, ", p->x);
	printf("y: %f, ", p->y);
	printf("z: %f\n", p->y);
}

static void	print_vec(t_vector *vec, const char *msg)
{
	if (msg)
		printf("%s ", msg);
	else
		printf("Undefined element's vector ");
	printf("x: %f, ", vec->x);
	printf("y: %f, ", vec->y);
	printf("z: %f\n", vec->y);
}

void	print_test_config(t_config *cf)
{
	printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("Amb.lighting_ratio: %.1f\n", cf->amb.lighting_ratio);
	print_col(&cf->amb.col, "Ambience");
	print_vec(&cf->cam.norm_vec, "Camera norm vector");
	printf("Camera fov: %.2f\n", cf->cam.fov);
	print_point(&cf->cam.point, "Camera");
	print_col(&cf->light.col, "Light");
	print_col(&cf->pl->col, "Plane");
	print_col(&cf->sp->col, "Sphere");
	print_col(&cf->cy->col, "Cyliner");
}

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

/*prints out a triplet of floats*/
void	print_triplet(float *triplet)
{
	printf("%f , %f , %f\n", triplet[0], triplet[1], triplet[2]);
}