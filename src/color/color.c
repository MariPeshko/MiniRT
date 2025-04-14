#include "../inc/miniRT.h"

double	d_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	d_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

void	get_ray_color(t_mini_rt *rt, t_point pixel, t_point camera)
{
	/*calculates a ray*/
	double	triplet[3];
	triplet[0] = pixel.x - camera.x;
	triplet[1] = pixel.y - camera.y;
	triplet[2] = pixel.z - camera.z;
	if (isnan(triplet[0]) || isnan(triplet[1]) || isnan(triplet[2]) || 
		isinf(triplet[0]) || isinf(triplet[1]) || isinf(triplet[2]))
	{
		clean_exit_rt(rt, CALC);
	}
	rt->coca.r_shadow.c = camera;
	init_vec(&rt->coca.r_shadow.v_dir, triplet);
	normalize_vector(&rt->coca.r_shadow.v_dir);
	return ;
}
/*claculates color of pixel based on hit*/
void	get_color(t_mini_rt *rt, t_color *color)
{
	t_color	ambient;
	t_color	diffuse;

	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;
	get_ray_color(rt, rt->cf.light.point, rt->calc.min.point);
	if (ft_strncmp(rt->calc.min.type, PLANE, 5) == SUCCESS)
		get_colors_plane(rt, &ambient, &diffuse);
	/*else if (rt->calc.min.type == SPHERE)
		get_colors_sphere(rt, &ambient, &diffuse);
	else if (rt->calc.min.type == CYLINDER)
		get_colors_cylinder(rt, &ambient, &diffuse);*/
	ambient.r += diffuse.r;
	ambient.g += diffuse.g;
	ambient.b += diffuse.b;
	color->r = d_min(255, d_max(0, ambient.r));
	color->g = d_min(255, d_max(0, ambient.g));
	color->b = d_min(255, d_max(0, ambient.b));
	return ;
}