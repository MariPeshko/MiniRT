/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cys_quadratic_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:47:27 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 18:06:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	get_a_cylinder(t_vector *d_vertical, double *a, t_mini_rt *rt)
{
	double	tmp;

	if (vector_multiply_vector(d_vertical, d_vertical, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*a = tmp;
	if (isnan(tmp) || isinf(tmp))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	get_b_cylinder(t_vector *oc_vertical, t_vector *d_vertical,
		double *b, t_mini_rt *rt)
{
	if (vector_multiply_vector(oc_vertical, d_vertical, b) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*b *= 2;
	if (isnan(*b) || isinf(*b))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	get_c_cylinder(t_vector *oc_vertical, double radius,
	double *c, t_mini_rt *rt)
{
	if (vector_multiply_vector(oc_vertical, oc_vertical, c) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*c -= radius * radius;
	if (isnan(*c) || isinf(*c))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	cy_calculate_quadratic_arguments(double *args, t_cys *cy,
	t_ray *ray, t_mini_rt *rt)
{
	t_vector	d_vertical;
	t_vector	oc_vertical;

	if (get_vertical_parts(&d_vertical, &oc_vertical, cy, ray, rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_a_cylinder(&d_vertical, &args[0], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_b_cylinder(&oc_vertical, &d_vertical, &args[1], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_c_cylinder(&oc_vertical, cy->diam / 2, &args[2], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	return (SUCCESS);
}
