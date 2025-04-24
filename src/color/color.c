#include "../inc/miniRT.h"

bool	cylinder_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_cys	*cy;

	cy = rt->cf.cy;
	while (cy)
	{
		if (coca->cy != NULL && cy->id == coca->cy->id)
		{
			cy = cy->next;
			continue ;
		}
		if (get_hit_cys(rt, cy, &coca->r_shadow) == SUCCESS)
			return (true);
		cy = cy->next;
	}
	return (false);
}

bool	in_light(t_mini_rt *rt, t_color_calc *coca)
{
	if (vector_multiply_vector(&coca->r_shadow.v_dir, &coca->hit_n, &coca->tmp) == FAILURE)
		clean_exit_rt(rt, CALC, I_L);
	if (coca->tmp < 0)
		return (false);
	//printf("tmp = %10f\n", coca->tmp);
	if (plane_blocks_light(rt, coca) == true)
		return (false);
	if (sphere_blocks_light(rt, coca) == true)
		return (false);
	if (cylinder_blocks_light(rt, coca) == true)
		return (false);
	
	return (true);
}


void	get_ray_color(t_mini_rt *rt, t_point light, t_point hit_p)
{
	/*calculates a ray*/
	double	triplet[3];
	triplet[0] = light.x - hit_p.x;
	triplet[1] = light.y - hit_p.y;
	triplet[2] = light.z - hit_p.z;
	if (isnan(triplet[0]) || isnan(triplet[1]) || isnan(triplet[2]) || 
		isinf(triplet[0]) || isinf(triplet[1]) || isinf(triplet[2]))
	{
		clean_exit_rt(rt, CALC, G_R_C);
	}
	
	rt->coca.r_shadow.c = hit_p;
	init_vec(&rt->coca.r_shadow.v_dir, triplet);
	rt->coca.L_distance = vector_length(&rt->coca.r_shadow.v_dir, rt);
	normalize_vector(&rt->coca.r_shadow.v_dir);
	return ;
}

bool	cyhere_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_cys	*cy;

	cy = rt->cf.cy;
	while (cy)
	{
		if (coca->cy != NULL && cy->id == coca->cy->id)
		{
			cy = cy->next;
			continue ;
		}
		if (get_hit_cys(rt, cy, &coca->r_shadow) == SUCCESS)
			return (true);
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

/*claculates color of pixel based on hit*/
void	get_color(t_mini_rt *rt, t_color *color)
{
	//printf("get Color hi\n");
	t_color	ambient;
	t_color	diffuse;

	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;
	get_ray_color(rt, rt->cf.light.point, rt->calc.min.point);
	//save distance to light, so objects behind the light do not count as shadow. 
	if (ft_strncmp(rt->calc.min.type, PLANE, 5) == SUCCESS)
		get_colors_plane(rt, &ambient, &diffuse);
	else if (ft_strncmp(rt->calc.min.type, SPHERE, 6) == SUCCESS)
		get_colors_sphere(rt, &ambient, &diffuse);
	else if (ft_strncmp(rt->calc.min.type, CYLINDER, 8) == SUCCESS)
		get_colors_cylinder(rt, &ambient, &diffuse);
	ambient.r += diffuse.r;
	ambient.g += diffuse.g;
	ambient.b += diffuse.b;
	// ambient.r = powf(ambient.r, 1.0f / 2.2f);
	// ambient.g = powf(ambient.g, 1.0f / 2.2f);
	// ambient.b = powf(ambient.b, 1.0f / 2.2f);
	color->r = d_min(1.0, d_max(0, ambient.r));
	color->g = d_min(1.0, d_max(0, ambient.g));
	color->b = d_min(1.0, d_max(0, ambient.b));
	//printf("rgb end %d, %d, %d\n", color->r, color->g, color->b);

	return ;
}
