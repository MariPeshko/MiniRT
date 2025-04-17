/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cys_quadratic_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:47:27 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/14 14:44:29 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	get_A_cylinder(t_vector *d_vertical, double *A, t_mini_rt *rt)
{
	double	tmp;

	if (vector_multiply_vector(d_vertical, d_vertical, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*A = tmp;
	if (isnan(tmp) || isinf(tmp))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	get_B_cylinder(t_vector *OC_vertical, t_vector *d_vertical,
		double *B, t_mini_rt *rt)
{
	if (vector_multiply_vector(OC_vertical, d_vertical, B) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*B *= 2;
	if (isnan(*B) || isinf(*B))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	get_C_cylinder(t_vector *OC_vertical, double radius,
	double *C, t_mini_rt *rt)
{
	if (vector_multiply_vector(OC_vertical, OC_vertical, C) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	*C -= radius * radius;
	if (isnan(*C) || isinf(*C))
		clean_exit_rt(rt, CALC, NULL);
	return (SUCCESS);
}

int	cy_calculate_quadratic_arguments(double *args, t_cys *cy,
	t_ray *ray, t_mini_rt *rt)
{
	t_vector	d_vertical;
	t_vector	OC_vertical;

	if (get_vertical_parts(&d_vertical, &OC_vertical, cy, ray, rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_A_cylinder(&d_vertical, &args[0], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_B_cylinder(&OC_vertical, &d_vertical, &args[1], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	if (get_C_cylinder(&OC_vertical, cy->diam / 2, &args[2], rt) == FAILURE)
		clean_exit_rt(rt, CALC_CYL_QU, NULL);
	return (SUCCESS);
}
