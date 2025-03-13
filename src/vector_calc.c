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

/*normalizes v to have length 1*/
int	normalize_vector(t_vector *v)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (length == 0)
		return (FAILURE);
	v->x /= length;
	v->y /= length;
	v->z /= length;
	return (SUCCESS);
}

/* !!! RENAME "factor" to "scalar"?
calcualtes a point result based on
result = point + vector * factor (german: Skalar) */
int	point_plus_vector(t_point *point, t_vector *vector, double factor, t_point *result)
{
	double new_x, new_y, new_z;

	if (!point || !vector || !result)
		return (FAILURE);

	// Calculate the new coordinates
	new_x = point->x + factor * vector->x;
	new_y = point->y + factor * vector->y;
	new_z = point->z + factor * vector->z;

	// Check for overflow/underflow or invalid results (math.h functions)
	if (isnan(new_x) || isnan(new_y) || isnan(new_z) ||
		isinf(new_x) || isinf(new_y) || isinf(new_z))
	{
		return (FAILURE);
	}

	// Assign the result if everything is fine
	result->x = new_x;
	result->y = new_y;
	result->z = new_z;

	return (SUCCESS);
}