/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:50:35 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:50:41 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_height_two(t_mini_rt *rt, t_ray *ray, t_cys *cy, double *t)
{
	t_point		p;
	double		vertical;
	t_vector	v;

	if (point_plus_vector(&ray->c, &ray->v_dir, *t, &p) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (point_minus_point(&cy->point, &p, &v) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (vector_multiply_vector(&cy->norm_vec, &v, &vertical) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (vertical < 0)
		vertical *= -1;
	if (vertical > ((cy->height / 2) + EPSILON))
		*t = -1;
}

void	check_height(t_mini_rt *rt, t_ray *ray, t_cys *cy)
{
	if (rt->calc.t1 >= 0)
		check_height_two(rt, ray, cy, &rt->calc.t1);
	if (rt->calc.t2 >= 0)
		check_height_two(rt, ray, cy, &rt->calc.t2);
}

/*calcualtes collision of raz and rounded wall of a single cylinder*/
int	get_cys_wall_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
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
	if (rt->calc.t1 == 0)
		clean_exit_rt(rt, C_IN_CY_W, NULL);
	fill_hit(CYLINDER, &rt->calc, cy->id, new);
	return (SUCCESS);
}

int	get_vertical_parts(t_vector *d_vertical, t_vector *OC_vertical,
	t_cys *cy, t_ray *ray, t_mini_rt *rt)
{
	double		tmp;
	t_vector	v_tmp;
	t_vector	co;

	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (subtract_vectors(&ray->v_dir, &v_tmp, &v_tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	d_vertical->x = v_tmp.x;
	d_vertical->y = v_tmp.y;
	d_vertical->z = v_tmp.z;
	if (point_minus_point(&ray->c, &cy->point, &co) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (vector_multiply_vector(&co, &cy->norm_vec, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	if (subtract_vectors(&co, &v_tmp, &v_tmp) == FAILURE)
		clean_exit_rt(rt, CALC, NULL);
	OC_vertical->x = v_tmp.x;
	OC_vertical->y = v_tmp.y;
	OC_vertical->z = v_tmp.z;
	return (SUCCESS);
}

double	vector_length_cy(t_vector *v, t_mini_rt *rt)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (isnan(length) || isinf(length))
		clean_exit_rt(rt, CALC, V_L_CY);
	return (length);
}
