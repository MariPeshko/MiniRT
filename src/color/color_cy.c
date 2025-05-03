/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:09:44 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/03 13:54:29 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

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
		if (cys_shadow_check(rt, cy, &coca->r_shadow) == SUCCESS
			&& rt->calc.t1 > EPSILON)
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
		calculate_wall_normal(rt, coca, &p);
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
