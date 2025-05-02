/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:09:44 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:13:11 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	fill_hit_shadow(char *object, t_col *calc, t_ray *ray, t_hit *got)
{
	got->type = object;
	got->distance = calc->t1;
	if (point_plus_vector(&ray->c, &ray->v_dir, got->distance,
			&got->point) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	get_cys_top_shadow(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	t_point		center;
	t_vector	tmp;

	if (point_plus_vector(&cy->point, &cy->norm_vec, cy->height / 2, &center) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_P_V);
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	if (rt->calc.t2 == 0)
		return (FAILURE);
	if (point_minus_point(&center, &ray->c, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_multiply_vector(&tmp, &cy->norm_vec, &rt->calc.t1) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	rt->calc.t1 = rt->calc.t1 / rt->calc.t2;
	if (isnan(rt->calc.t1) || isinf(rt->calc.t1))
		clean_exit_rt(rt, CALC_CT, NULL);
	if (rt->calc.t1 > rt->coca.L_distance)
		return (FAILURE);
	fill_hit_shadow(CYLINDER, &rt->calc, ray, new);
	if (point_minus_point(&new->point, &center, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_length_cy(&tmp, rt) > (cy->diam / 2))
		return (FAILURE);
	return (SUCCESS);
}

int	get_cys_bottom_shadow(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	t_point		center;
	t_vector	tmp;

	if (point_plus_vector(&cy->point, &cy->norm_vec, ((cy->height / 2) * -1), &center) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_P_V);
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	if (rt->calc.t2 == 0)
		return (FAILURE);
	if (point_minus_point(&center, &ray->c, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_multiply_vector(&tmp, &cy->norm_vec, &rt->calc.t1) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	rt->calc.t1 = rt->calc.t1 / rt->calc.t2;
	if (isnan(rt->calc.t1) || isinf(rt->calc.t1))
		clean_exit_rt(rt, CALC_CT, NULL);
	if (rt->calc.t1 > rt->coca.L_distance)
		return (FAILURE);
	fill_hit_shadow(CYLINDER, &rt->calc, ray, new);
	if (point_minus_point(&new->point, &center, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_length_cy(&tmp, rt) > (cy->diam / 2))
		return (FAILURE);
	return (SUCCESS);
}

int	get_cys_wall_shadow(t_mini_rt *rt, t_cys *cy, t_ray *ray)
{
	int		solutions;

	cy_calculate_quadratic_arguments(rt->calc.quadratic_args, cy, ray, rt);
	solutions = discriminant_check(rt->calc.quadratic_args[0],
			rt->calc.quadratic_args[1], rt->calc.quadratic_args[2], rt);
	if (solutions == 0)
		return (FAILURE);
	quadratic_formula_plus(rt->calc.quadratic_args, &rt->calc.t1, rt);
	if (solutions == 2)
		quadratic_formula_minus(rt->calc.quadratic_args, &rt->calc.t2, rt);
	check_height(rt, ray, cy);
	if (get_positive_min(rt->calc.t1, rt->calc.t2, &rt->calc.t1) == FAILURE)
		return (FAILURE);
	if (rt->calc.t1 > rt->coca.L_distance)
		return (FAILURE);
	return (SUCCESS);
}

int	cys_shadow_check(t_mini_rt *rt, t_cys *cy, t_ray *ray)
{
	t_hit	new;

	init_hit(&new);
	reset_calc(&rt->calc);
	if (get_cys_wall_shadow(rt, cy, ray) == SUCCESS)
		return (SUCCESS);
	if (get_cys_top_shadow(rt, cy, &new, ray) == SUCCESS)
		return (SUCCESS);
	init_hit(&new);
	if (get_cys_bottom_shadow(rt, cy, &new, ray) == SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

bool	cylinder_blocks_light(t_mini_rt *rt, t_color_calc *coca)
{
	t_cys	*cy;

	cy = rt->cf.cy;
	while (cy)
	{
		init_hit(&rt->calc.got);
		if (coca->cy != NULL && cy->id == coca->cy->id)
		{
			cy = cy->next;
			continue ;
		}
		if (cys_shadow_check(rt, cy, &coca->r_shadow) == SUCCESS)
			return (true);
		cy = cy->next;
	}
	return (false);
}

t_cys	*get_cylinder_pointer(t_mini_rt *rt, t_hit *min)
{
	t_cys	*cy;
	int		i;

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
		if (scalar_multiply_vector(-1, &coca->cy->norm_vec, &coca->hit_n)
			== FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
	}
	else
	{
		if (point_minus_point(&rt->calc.min.point, &coca->cy->point,
				&coca->hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		if (vector_multiply_vector(&coca->hit_n, &coca->cy->norm_vec,
				&coca->tmp) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		if (point_plus_vector(&rt->calc.min.point, &coca->cy->norm_vec,
				coca->tmp * -1, &p) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
		if (point_minus_point(&p, &coca->cy->point, &coca->hit_n) == FAILURE)
			clean_exit_rt(rt, CALC, C_H_N);
	}
	if (normalize_vector(&coca->hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
}

void	get_colors_cylinder(t_mini_rt *rt, t_color *ambient, t_color *diffuse)
{
	rt->coca.cy = get_cylinder_pointer(rt, &rt->calc.min);
	calculate_hit_normal(rt, &rt->coca);
	if (point_plus_vector(&rt->calc.min.point, &rt->coca.hit_n, EPSILON,
			&rt->calc.min.point) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_C);
	rt->coca.A = rt->cf.amb;
	rt->coca.L = rt->cf.light;
	ambient->r = rt->coca.cy->col.r * rt->coca.A.col.r
		* rt->coca.A.lighting_ratio;
	ambient->g = rt->coca.cy->col.g * rt->coca.A.col.g
		* rt->coca.A.lighting_ratio;
	ambient->b = rt->coca.cy->col.b * rt->coca.A.col.b
		* rt->coca.A.lighting_ratio;
	if (in_light(rt, &rt->coca) == false)
		return ;
	if (vector_multiply_vector(&rt->coca.hit_n, &rt->coca.r_shadow.v_dir,
			&rt->coca.tmp) == FAILURE)
		clean_exit_rt(rt, CALC, G_C_C);
	diffuse->r = rt->coca.cy->col.r * rt->coca.L.bright
		* rt->coca.L.col.r * d_max(0, rt->coca.tmp);
	diffuse->g = rt->coca.cy->col.g * rt->coca.L.bright
		* rt->coca.L.col.g * d_max(0, rt->coca.tmp);
	diffuse->b = rt->coca.cy->col.b * rt->coca.L.bright
		* rt->coca.L.col.b * d_max(0, rt->coca.tmp);
}
