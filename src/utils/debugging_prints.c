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
	printf("%10f,", c->r);
	printf("%10f,", c->g);
	printf("%10f\n", c->b);
}

void	print_point(t_point *p)
{
	printf("x: %.4f, ", p->x);
	printf("y: %.4f, ", p->y);
	printf("z: %.4f\n", p->z);
}

void	print_vec(t_vector *vec)
{
	printf("x: %.8f, ", vec->x);
	printf("y: %.8f, ", vec->y);
	printf("z: %.8f\n", vec->z);
}

/*prints out a triplet of floats*/
void	print_triplet(float *triplet)
{
	printf("%f , %f , %f\n", triplet[0], triplet[1], triplet[2]);
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
		print_point(&curr->point);
		print_vec(&curr->pl_normal);
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
		printf("\n%i SPHERE id:%i\n", i, curr->id);
		print_point(&curr->point);
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
		printf("\n%i CYLINDER id:%i\n", i, curr->id);
		print_point(&curr->point);
		print_vec(&curr->norm_vec);
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
	printf("Camera norm vector:\n");
	print_vec(&cf->cam.norm_vec);
	printf("Camera point:\n");
	print_point(&cf->cam.point);
	printf("Camera fov: %.2f\n", cf->cam.fov);
	print_point(&cf->light.point);
	printf("Light brightness %.1f\n", cf->light.bright);
	print_col(&cf->light.col, "Light");

	// LOOP to print multiple planes:
	//print_all_planes(cf);
	// LOOP to print multiple spheres:
	//print_all_spheres(cf);
	// LOOP to print multiple cylinders:
	//print_all_cylider(cf);
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

void	print_viewport(t_vp *vp)
{
	if (!vp)
	{
		printf("Viewport is NULL\n");
		return;
	}

	printf("\nVIEWPORT\n");

	printf("VP Width: %f in 3D space\n", vp->width);
	printf("VP Height: %f in 3D space\n", vp->height);
	printf("VP upperleft point: \n");
	print_point(&vp->upperleft);
	printf("VP horizontal:\n");
	print_vec(&vp->horizontal);
	printf("VP vertical:\n");
	print_vec(&vp->vertical);
	printf("VP C-Point:\n");
	print_point(&vp->vp_center);
}

void	print_collision(t_col calc)
{
	printf("Closest collision for ");
	print_point(&calc.pixel);
	printf("hit object of TYPE: %s\n", calc.min.type);
	print_point(&calc.min.point);
	printf("Distance to camera: %10f\n\n", calc.min.distance);
	printf("cy top / bottom = %d, %d\n", calc.min.cy_top, calc.min.cy_bottom);
}
