#include "../inc/miniRT.h"

bool	sphere_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_spher	*sp;

	sp = rt->cf.sp;
	while (sp)
	{
		if (get_hit_sphere(rt, sp, &coca->r_shadow) == SUCCESS)// && (rt->calc.got.id != coca->sp->id || rt->calc.t1 != 0))
			return (true);
		sp = sp->next;
	}
	return (false);
}

bool	in_light(t_mini_rt *rt, t_color_calc *coca)
{
	if (vector_multiply_vector(&coca->r_shadow.v_dir, &coca->hit_n, &coca->tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (coca->tmp < 0)
		return (false);
	//printf("tmp = %10f\n", coca->tmp);
	if (plane_blocks_light(rt, coca) == true)
		return (false);
	if (sphere_blocks_light(rt, coca) == true)
		return (false);
	/*if (cylinder_blocks_light(rt, coca) == true)
		return (false);*/
	
	return (true);
}

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

t_spher	*get_sphere_pointer(t_mini_rt *rt, t_hit *min)
{
	t_spher *sp;
	int i;

	sp = rt->cf.sp;
	i = 1; 
	while (i < min->id)
	{
		sp = sp->next;
		i ++;
	}
	return (sp);
}


void	get_colors_sphere(t_mini_rt *rt, t_color *ambient, t_color *diffuse)
{
	//pointers to existing structs for less . and ->
	rt->coca.sp = get_sphere_pointer(rt, &rt->calc.min);
	if (point_minus_point(&rt->calc.min.point, &rt->coca.sp->point, &rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (normalize_vector(&rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (point_plus_vector(&rt->calc.min.point, &rt->coca.hit_n, 0.1, &rt->calc.min.point) == FAILURE)
		clean_exit_rt(rt, CALC);
	rt->coca.A = rt->cf.amb;
	rt->coca.L = rt->cf.light;
	//abient color calculation
	ambient->r = rt->coca.sp->col.r * rt->coca.A.col.r * rt->coca.A.lighting_ratio;
	ambient->g = rt->coca.sp->col.g * rt->coca.A.col.g * rt->coca.A.lighting_ratio;
	ambient->b = rt->coca.sp->col.b * rt->coca.A.col.b * rt->coca.A.lighting_ratio;
	// printf("rgb amb %d, %d, %d\n", ambient->r, ambient->g, ambient->b);

	//collisons licht-collision vector with all objects. ausgenommen eigenes objekt mit t = 0
	if (in_light(rt, &rt->coca) == false)
		return ;
	//printf("light\n");
	//if norm vector * ray vector >0, norm vector + -1
	/*if (vector_multiply_vector(&rt->calc.ray.v_dir, &rt->coca.hit_n, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (rt->coca.tmp > 0)
	{
		if (scalar_multiply_vector(-1, &rt->coca.hit_n, &rt->coca.hit_n) == FAILURE)
			clean_exit_rt(rt, CALC);
	}*/
	//now we have a normal in the right direction
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	// printf("tmp = %10f\n", rt->coca.tmp);
	diffuse->r = rt->coca.sp->col.r * rt->coca.L.bright * rt->coca.L.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.sp->col.g * rt->coca.L.bright * rt->coca.L.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.sp->col.b * rt->coca.L.bright * rt->coca.L.col.b * d_max(0, rt->coca.tmp);
	//printf("rgb dif %d, %d, %d\n", diffuse->r, diffuse->g, diffuse->b);
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
	if (ft_strncmp(rt->calc.min.type, SPHERE, 6) == SUCCESS)
		get_colors_sphere(rt, &ambient, &diffuse);
	/*else if (rt->calc.min.type == CYLINDER)
		get_colors_cylinder(rt, &ambient, &diffuse);*/
	ambient.r += diffuse.r;
	ambient.g += diffuse.g;
	ambient.b += diffuse.b;
	color->r = d_min(255, d_max(0, ambient.r));
	color->g = d_min(255, d_max(0, ambient.g));
	color->b = d_min(255, d_max(0, ambient.b));
	return ;
}
