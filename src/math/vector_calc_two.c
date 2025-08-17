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

int	subtract_vectors(t_vector *a, t_vector *b, t_vector *result)
{
	double	new_x;
	double	new_y;
	double	new_z;

	if (!a || !b || !result)
		return (FAILURE);
	new_x = a->x - b->x;
	new_y = a->y - b->y;
	new_z = a->z - b->z;
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

/** The function calculates the normal(perpendicular vector for vector v) */
int	get_normal(t_vector *v, t_vector *n)
{
	if (!v || !n)
		return (FAILURE);
	if (v->x != 0 || v->y != 0)
	{
		n->x = -v->y;
		n->y = v->x;
		n->z = 0;
	}
	else
	{
		n->x = 1;
		n->y = 0;
		n->z = 0;
	}
	if (normalize_vector(n) == FAILURE)
	{
		printf("FAILURE plane get_normal() and normilise_vector()");
		return (FAILURE);
	}
	return (SUCCESS);
}

/** shorter vector_multiply_vector() */
int	dot_product(t_vector *a, t_vector *b, double *result)
{
	if (!a || !b || !result)
	{
		return (FAILURE);
	}
	*result = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	if (isnan(*result) || isinf(*result))
	{
		return (FAILURE);
	}
	return (SUCCESS);
}

/** dot product or scalar product */
int	vector_multiply_vector(t_vector *a, t_vector *b, double *result)
{
	double	new_x;
	double	new_y;
	double	new_z;

	if (!a || !b || !result)
		return (FAILURE);
	new_x = a->x * b->x;
	new_y = a->y * b->y;
	new_z = a->z * b->z;
	if (isnan(new_x) || isnan(new_y) || isnan(new_z)
		|| isinf(new_x) || isinf(new_y) || isinf(new_z))
	{
		return (FAILURE);
	}
	new_x += new_y + new_z;
	if (isnan(new_x) || isinf(new_x))
		return (FAILURE);
	*result = new_x;
	return (SUCCESS);
}

int	scalar_multiply_vector(double scalar, t_vector *vector, t_vector *result)
{
	double	new_x;
	double	new_y;
	double	new_z;

	if (!vector || !result)
		return (FAILURE);
	new_x = scalar * vector->x;
	new_y = scalar * vector->y;
	new_z = scalar * vector->z;
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
