/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:47 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 21:23:25 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*calculates the cross product of a and b
result: a vector c perpendicular to a plane containing a and b*/
int	cross_product(t_vector *a, t_vector *b, t_vector *result)
{
	if (!a || !b || !result)
		return (FAILURE);
	result->x = a->y * b->z - a->z * b->y;
	result->y = a->z * b->x - a->x * b->z;
	result->z = a->x * b->y - a->y * b->x;
	return (SUCCESS);
}

/*calculates a vector from b to a*/
int	point_minus_point(t_point *a, t_point *b, t_vector *result)
{
	if (!a || !b || !result)
		return (FAILURE);
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	return (SUCCESS);
}

double	vector_length(t_vector *v, t_mini_rt *rt)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (length < EPSILON)
	{
		clean_exit_rt(rt, CALC, V_L_ZERO);
	}
	if (isinf(length))
	{
		clean_exit_rt(rt, CALC, V_L_ISINF);
	}
	if (isnan(length))
	{
		clean_exit_rt(rt, CALC, V_L_ISNAN);
	}
	return (length);
}

/*normalizes v to have length 1*/
int	normalize_vector(t_vector *v)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (isnan(length) || isinf(length) || length == 0)
		return (FAILURE);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	return (SUCCESS);
}

/*calcualtes a point result based on
result = point + vector * scalar (german: Skalar) */
int	point_plus_vector(t_point *point, t_vector *vector,
		double scalar, t_point *result)
{
	double	new_x;
	double	new_y;
	double	new_z;

	if (!point || !vector || !result)
		return (FAILURE);
	new_x = point->x + scalar * vector->x;
	new_y = point->y + scalar * vector->y;
	new_z = point->z + scalar * vector->z;
	if (isnan(new_x) || isnan(new_y) || isnan(new_z)
		|| isinf(new_x) || isinf(new_y) || isinf(new_z))
	{
		return (FAILURE);
	}
	result->x = new_x;
	result->y = new_y;
	result->z = new_z;
	return (SUCCESS);
}
