/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:05:19 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/03 11:30:09 by sgramsch         ###   ########.fr       */
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

void	get_cap_center(t_mini_rt *rt, t_cys *cy, t_point *center, double d)
{
	if (point_plus_vector(&cy->point, &cy->norm_vec,
			((cy->height / 2) * d), center) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_P_V);
}

int	get_cys_top_shadow(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	t_point		center;
	t_vector	tmp;

	get_cap_center(rt, cy, &center, 1);
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2)
		== FAILURE)
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
	if (rt->calc.t1 > rt->coca.l_distance)
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

	get_cap_center(rt, cy, &center, -1);
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2)
		== FAILURE)
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
	if (rt->calc.t1 > rt->coca.l_distance)
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
	if (rt->calc.t1 > rt->coca.l_distance)
		return (FAILURE);
	return (SUCCESS);
}
