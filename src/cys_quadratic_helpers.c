/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cys_quadratic_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:47:27 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/02 11:49:28 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	get_A_cylinder(t_vector *d_vertical, double *A, t_mini_rt *rt)
{
	double	tmp;

	if (vector_multiply_vector(d_vertical, d_vertical, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	*A = tmp;
	if (isnan(tmp) || isinf(tmp))
		clean_exit_rt(rt, CALC);
	return (SUCCESS);
}

int	get_B_cylinder(t_vector *OC_vertical, t_vector *d_vertical,
		double *B, t_mini_rt *rt)
{
	if (vector_multiply_vector(OC_vertical, d_vertical, B) == FAILURE)
		clean_exit_rt(rt, CALC);
	*B *= 2;
	if (isnan(*B) || isinf(*B))
		clean_exit_rt(rt, CALC);
	return (SUCCESS);
}

int	get_C_cylinder(t_vector *OC_vertical, double radius,
	double *C, t_mini_rt *rt)
{
	if (vector_multiply_vector(OC_vertical, OC_vertical, C) == FAILURE)
		clean_exit_rt(rt, CALC);
	*C -= radius * radius;
	if (isnan(*C) || isinf(*C))
		clean_exit_rt(rt, CALC);
	return (SUCCESS);
}

int	get_vertical_parts(t_vector *d_vertical, t_vector *OC_vertical,
		t_cys *cy, t_ray *ray, t_mini_rt *rt)
{
	double tmp;
	t_vector	v_tmp;
	t_vector	CO;
	//d_vertical
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&ray->v_dir, &v_tmp, &v_tmp);
	d_vertical->x = v_tmp.x;
	d_vertical->y = v_tmp.y;
	d_vertical->z = v_tmp.z;
	//OC_vertical
	point_minus_point(&ray->c, &cy->point, &CO);
	if (vector_multiply_vector(&CO, &cy->norm_vec, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&CO, &v_tmp, &v_tmp);
	OC_vertical->x = v_tmp.x;
	OC_vertical->y = v_tmp.y;
	OC_vertical->z = v_tmp.z;
	return (SUCCESS);
}

int	calculate_quadratic_arguments(double *args, t_cys *cy,
	t_ray *ray, t_mini_rt *rt)
{
	t_vector	d_vertical;
	t_vector	OC_vertical;

	if (get_vertical_parts(&d_vertical, &OC_vertical, cy, ray, rt) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (get_A_cylinder(&d_vertical, &args[0], rt) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (get_B_cylinder(&OC_vertical, &d_vertical, &args[1], rt) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (get_C_cylinder(&OC_vertical, cy->diam / 2, &args[2], rt) == FAILURE)
		clean_exit_rt(rt, CALC);
	return (SUCCESS);
}
