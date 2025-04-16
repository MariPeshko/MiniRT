#include "../inc/miniRT.h"

bool	sphere_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_spher	*sp;

	sp = rt->cf.sp;
	while (sp)
	{
		if (coca->sp != NULL && sp->id == coca->sp->id)
		{
			sp = sp->next;
			continue ;
		}
		if (get_hit_sphere(rt, sp, &coca->r_shadow) == SUCCESS)
			return (true);
		sp = sp->next;
	}
	return (false);
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
	//printf("hi\n");
	//pointers to existing structs for less . and ->
	rt->coca.sp = get_sphere_pointer(rt, &rt->calc.min);
	if (point_minus_point(&rt->calc.min.point, &rt->coca.sp->point, &rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (normalize_vector(&rt->coca.hit_n) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (point_plus_vector(&rt->calc.min.point, &rt->coca.hit_n, EPSILON, &rt->calc.min.point) == FAILURE)
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
	//printf("in light\n");
	//now we have a normal in the right direction
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	//printf("tmp = %10f\n", rt->coca.tmp);
	diffuse->r = rt->coca.sp->col.r * rt->coca.L.bright * rt->coca.L.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.sp->col.g * rt->coca.L.bright * rt->coca.L.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.sp->col.b * rt->coca.L.bright * rt->coca.L.col.b * d_max(0, rt->coca.tmp);
	// printf("rgb dif %d, %d, %d\n", diffuse->r, diffuse->g, diffuse->b);
}