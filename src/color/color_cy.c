#include "../inc/miniRT.h"

bool	cylinder_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_cys	*cy;

	cy = rt->cf.cy;
	while (cy)
	{
		init_hit(&rt->calc.got);
		if (coca->cy != NULL && cy->id == coca->cy->id)
		{
			//printf("skipped cy id = %d\n", cy->id);
			cy = cy->next;
			continue ;
		}
		if (get_hit_cys(rt, cy, &coca->r_shadow) == SUCCESS)
		{
			//printf("cylinder %d blocks light\n", cy->id);
			return (true);
		}
		cy = cy->next;
	}
	return (false);
}

t_cys	*get_cylinder_pointer(t_mini_rt *rt, t_hit *min)
{
	t_cys *cy;
	int i;

	cy = rt->cf.cy;
	i = 1; 
	while (i < min->id)
	{
		cy = cy->next;
		i ++;
	}
	return (cy);
}

void	calculate_hit_normal(t_mini_rt *rt, t_color_calc *coca)
{
	t_point	p;

	if (rt->calc.min.cy_top == 1)
		coca->hit_n = coca->cy->norm_vec;
	else if (rt->calc.min.cy_bottom == 1)
	{
		if (scalar_multiply_vector(-1, &coca->cy->norm_vec, &coca->hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
	}
	else
	{
		if (point_minus_point(&rt->calc.min.point, &coca->cy->point, &coca->hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		if (vector_multiply_vector(&coca->hit_n, &coca->cy->norm_vec, &coca->tmp) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		if (point_plus_vector(&rt->calc.min.point, &coca->cy->norm_vec, coca->tmp * -1, &p) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		//now P should be on the same plane as cy center. 
		if (point_minus_point(&p, &coca->cy->point, &coca->hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
	}
	if (normalize_vector(&coca->hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
}

void	get_colors_cylinder(t_mini_rt *rt, t_color *ambient, t_color *diffuse)
{
	//printf("hi\n");
	//pointers to existing structs for less . and ->
	rt->coca.cy = get_cylinder_pointer(rt, &rt->calc.min);
	calculate_hit_normal(rt, &rt->coca);
	//prevent self hit with collision
	if (point_plus_vector(&rt->calc.min.point, &rt->coca.hit_n, EPSILON, &rt->calc.min.point) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_C);
	rt->coca.A = rt->cf.amb;
	rt->coca.L = rt->cf.light;
	//abient color calculation
	ambient->r = rt->coca.cy->col.r * rt->coca.A.col.r * rt->coca.A.lighting_ratio;
	ambient->g = rt->coca.cy->col.g * rt->coca.A.col.g * rt->coca.A.lighting_ratio;
	ambient->b = rt->coca.cy->col.b * rt->coca.A.col.b * rt->coca.A.lighting_ratio;
	// printf("rgb amb %d, %d, %d\n", ambient->r, ambient->g, ambient->b);

	//collisons licht-collision vector with all objects. ausgenommen eigenes objekt mit t = 0
	if (in_light(rt, &rt->coca) == false)
		return ;
	//printf("in light\n");
	//now we have a normal in the right direction
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_C);
	//printf("tmp = %10f\n", rt->coca.tmp);
	diffuse->r = rt->coca.cy->col.r * rt->coca.L.bright * rt->coca.L.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.cy->col.g * rt->coca.L.bright * rt->coca.L.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.cy->col.b * rt->coca.L.bright * rt->coca.L.col.b * d_max(0, rt->coca.tmp);
	// printf("rgb dif %d, %d, %d\n", diffuse->r, diffuse->g, diffuse->b);
}