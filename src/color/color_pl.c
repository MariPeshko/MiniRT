#include "../inc/miniRT.h"

bool	collision_on_plane(t_point *p, t_plane *pl, t_mini_rt *rt)
{
	t_vector	p_to_plane;
	double		dot_prod;

	if (point_minus_point(p, &pl->point, &p_to_plane) == FAILURE)
		clean_exit_rt(rt, CALC, C_O_P);
	if (dot_product(&pl->pl_normal, &p_to_plane, &dot_prod) == FAILURE)
		clean_exit_rt(rt, CALC, C_O_P);
	if (fabs(dot_prod) < EPSILON)
		return (true);
	return (false);
}

bool	plane_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_plane	*pl;

	pl = rt->cf.pl;
	while (pl)
	{
		if (coca->pl != 00 && pl->id == coca->pl->id)
		{
			pl = pl->next;
			continue ;
		}
		if (collision_on_plane(&rt->calc.min.point, pl, rt) == true)
			return (false);
		if (get_hit_plane(pl, &coca->r_shadow, rt) == SUCCESS)
		{
			if (rt->calc.got.distance < coca->L_distance)
				return (true);
		}
		pl = pl->next;
	}
	return (false);
}

t_plane	*get_plane_pointer(t_mini_rt *rt, t_hit *min)
{
	t_plane *pl;
	int i;

	pl = rt->cf.pl;
	i = 1; 
	while (i < min->id)
	{
		pl = pl->next;
		i ++;
	}
	return (pl);
}

void	get_colors_plane(t_mini_rt *rt, t_color *ambient, t_color *diffuse)
{
	//pointers to existing structs for less . and ->
	rt->coca.pl = get_plane_pointer(rt, &rt->calc.min);
	rt->coca.hit_n = rt->coca.pl->pl_normal;
	rt->coca.A = rt->cf.amb;
	rt->coca.L = rt->cf.light;
	//abient color calculation
	ambient->r = rt->coca.pl->col.r * rt->coca.A.col.r * rt->coca.A.lighting_ratio;
	ambient->g = rt->coca.pl->col.g * rt->coca.A.col.g * rt->coca.A.lighting_ratio;
	ambient->b = rt->coca.pl->col.b * rt->coca.A.col.b * rt->coca.A.lighting_ratio;

	//collisons licht-collision vector with all objects. ausgenommen eigenes objekt mit t = 0
	if (in_light(rt, &rt->coca) == false)
		return ;
	//if norm vector * ray vector >0, norm vector + -1
	if (vector_multiply_vector(&rt->calc.ray.v_dir, &rt->coca.hit_n, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_P);
	if (rt->coca.tmp > 0)
	{
		if (scalar_multiply_vector(-1, &rt->coca.hit_n, &rt->coca.hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, G_C_P);
	}
	//now we have a normal in the right direction
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir, &rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_P);
	//printf("tmp = %10f \n", rt->coca.tmp);
	diffuse->r = rt->coca.pl->col.r * rt->coca.L.bright * rt->coca.L.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.pl->col.g * rt->coca.L.bright * rt->coca.L.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.pl->col.b * rt->coca.L.bright * rt->coca.L.col.b * d_max(0, rt->coca.tmp);	
}
