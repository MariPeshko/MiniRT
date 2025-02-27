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
	printf("x: %.1f, ", p->x);
	printf("y: %.1f, ", p->y);
	printf("z: %.1f\n", p->z);
}

static void	print_vec(t_vector *vec, const char *msg)
{
	if (msg)
		printf("%s norm vector ", msg);
	else
		printf("Undefined element's vector ");
	printf("x: %.1f, ", vec->x);
	printf("y: %.1f, ", vec->y);
	printf("z: %.1f\n", vec->z);
}

void	print_all_planes(t_config *cf)
{
	t_plane	*curr;
	int			i;

	i = 1;
	curr = cf->pl;
	while (curr != NULL)
	{
		printf("\n%i PLANE\n", i);
		print_point(&curr->point, "Plane");
		print_vec(&curr->norm_vec, "Plane");
		print_col(&curr->col, "Plane");
		curr = curr->next;
		i++;
	}
}

void	print_all_spheres(t_config *cf)
{
	t_spher	*curr;
	int		i;

	i = 1;
	curr = cf->sp;
	while (curr != NULL)
	{
		printf("\n%i SPHERE\n", i);
		print_point(&curr->point, "Sphere");
		printf("Diameter %.2f\n", curr->diam);
		print_col(&curr->col, "Sphere");
		curr = curr->next;
		i++;
	}
}

void	print_all_cylider(t_config *cf)
{
	t_cys	*curr;
	int		i;

	i = 1;
	curr = cf->cy;
	while (curr != NULL)
	{
		printf("\n%i CYLINDER\n", i);
		print_point(&curr->point, "Cylinder");
		print_vec(&curr->norm_vec, "Cylinder");
		printf("Cylinder diameter: %.2f\n", curr->diam);
		printf("Cylinder height: %.2f\n", curr->height);
		print_col(&curr->col, "Cylinder");
		curr = curr->next;
		i++;
	}
}

void	print_test_config(t_config *cf)
{
	printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
	printf("Amb.lighting_ratio: %.1f\n", cf->amb.lighting_ratio);
	print_col(&cf->amb.col, "Ambience");
	print_vec(&cf->cam.norm_vec, "Camera norm");
	print_point(&cf->cam.point, "Camera");
	printf("Camera fov: %.2f\n", cf->cam.fov);
	print_point(&cf->light.point, "Light");
	printf("Light brightness %.1f\n", cf->light.bright);
	print_col(&cf->light.col, "Light");

	// LOOP to print multiple planes:
	print_all_planes(cf);
	// LOOP to print multiple spheres:
	print_all_spheres(cf);
	// LOOP to print multiple cylinders:
	print_all_cylider(cf);
	printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
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
