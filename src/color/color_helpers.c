/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:13:20 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/03 11:16:48 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	d_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	d_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

void	calculate_wall_normal(t_mini_rt *rt, t_color_calc *coca, t_point *p)
{
	if (point_minus_point(&rt->calc.min.point, &coca->cy->point,
			&coca->hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
	if (vector_multiply_vector(&coca->hit_n, &coca->cy->norm_vec,
			&coca->tmp) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
	if (point_plus_vector(&rt->calc.min.point, &coca->cy->norm_vec,
			coca->tmp * -1, p) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
	if (point_minus_point(p, &coca->cy->point, &coca->hit_n) == FAILURE)
		clean_exit_rt(rt, CALC, C_H_N);
}
