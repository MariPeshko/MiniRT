#include "../inc/miniRT.h"

/**
 * Define "world up" vector
 *
 * If the camera is looking straight up or down (aligned with 
 * the Z-axis), it sets up = (1,0,0), meaning the world up 
 * vector is along the X-axis. This avoids the issue where 
 * the standard up (0,1,0) could be parallel to the camera 
 * direction.
 * 
 * In all other cases it sets up = (0,0,1), meaning the 
 * world up vector is along the Z-axis.
*/
void	get_up_vector(t_config *cf, t_vector *up)
{
	if (cf->cam.norm_vec.x == 0 && cf->cam.norm_vec.y == 0
		&& cf->cam.norm_vec.z != 0)
	{
		up->x = 0;
		up->y = -1;
		up->z = 0;
	/* 	up->x = 1;
		up->y = 0;
		up->z = 0; */
	}
	else
	{
		up->x = 0;
		up->y = 0;
		up->z = 1;
	}
}

// gpt
/* int	calculate_viewport_orientation(t_config *cf)
{
	t_vector	up;
	t_vector	right;
	t_vector	vertical;

	get_up_vector(cf, &up);
	//Right (horizontal direction) = cross(forward, up)
	if (cross_product(&cf->cam.norm_vec, &up, &right) == FAILURE)
		return (FAILURE);
	if (normalize_vector(&right) == FAILURE)
		return (FAILURE);
	// True Up (vertical) = cross(right, forward)
	if (cross_product(&right, &cf->cam.norm_vec, &vertical) == FAILURE)
		return (FAILURE);
	if (normalize_vector(&vertical) == FAILURE)
		return (FAILURE);
	// Scale vectors to match pixel size
	// pixel step calculation
	right.x *= cf->viewp.width / WIN_WIDTH;
	right.y *= cf->viewp.width / WIN_WIDTH;
	right.z *= cf->viewp.width / WIN_WIDTH;
	vertical.x *= cf->viewp.height / WIN_HEIGHT;
	vertical.y *= cf->viewp.height / WIN_HEIGHT;
	vertical.z *= cf->viewp.height / WIN_HEIGHT;
	// Save to viewport
	cf->viewp.horizontal = right;
	cf->viewp.vertical = vertical;
	return (SUCCESS);
} */

/** Calculate viewport orientation and pixel step calculation.
 * - Defines "world up" vector.
 * - Finds Basis Vectors for Viewport Orientation.
 * pixel step calculation:
 * - Scale horizontal & vertical vectors to match pixel spacing.
*/
int	calculate_viewport_orientation(t_config *cf)
{
	t_vector	up;
	t_vector	horizontal;
	t_vector	vertical;

	get_up_vector(cf, &up);
	// Horizontal = cross(forward, up)
	if (cross_product(&cf->cam.norm_vec, &up, &horizontal) == FAILURE)
		return (FAILURE);
	if (normalize_vector(&horizontal) == FAILURE)
		return (FAILURE);
	// Vertical = cross(forward, horizontal)
	if (cross_product(&cf->cam.norm_vec, &horizontal, &vertical) == FAILURE)
		return (FAILURE);
	if (normalize_vector(&vertical) == FAILURE)
		return (FAILURE);
	// pixel step calculation
	horizontal.x *= cf->viewp.width / WIN_WIDTH;
	horizontal.y *= cf->viewp.width / WIN_WIDTH;
	horizontal.z *= cf->viewp.width / WIN_WIDTH;
	vertical.x *= cf->viewp.height / WIN_HEIGHT;
	vertical.y *= cf->viewp.height / WIN_HEIGHT;
	vertical.z *= cf->viewp.height / WIN_HEIGHT;

	cf->viewp.horizontal = horizontal;
	cf->viewp.vertical = vertical;
	return (SUCCESS);
}

/** Calculate upper left corner point.
 * (later this is the first pixel)
 * - Calculate half vectors
 * - Calculating the upper left corner = center - half_horizontal 
 * + half_vertical.
 * @param upperleft - the upper left corner
*/
int	calculate_upper_left_corner(t_vp *viewp)
{
	t_vector	half_horizontal;
	t_vector	half_vertical;

	if (!viewp)
		return (FAILURE);
	half_horizontal.x = viewp->horizontal.x * 0.5 * WIN_WIDTH;
	half_horizontal.y = viewp->horizontal.y * 0.5 * WIN_WIDTH;
	half_horizontal.z = viewp->horizontal.z * 0.5 * WIN_WIDTH;
	half_vertical.x = viewp->vertical.x * 0.5 * WIN_HEIGHT;
	half_vertical.y = viewp->vertical.y * 0.5 * WIN_HEIGHT;
	half_vertical.z = viewp->vertical.z * 0.5 * WIN_HEIGHT;
	viewp->upperleft.x = viewp->vp_center.x - half_horizontal.x - half_vertical.x;
	viewp->upperleft.y = viewp->vp_center.y - half_horizontal.y - half_vertical.y;
	viewp->upperleft.z = viewp->vp_center.z - half_horizontal.z - half_vertical.z;
	return (SUCCESS);
}

int	point_minus_vector(t_point *point, t_vector *vector, double scalar, t_point *result)
{
	double new_x, new_y, new_z;

	if (!point || !vector || !result)
		return (FAILURE);

	// Calculate the new coordinates
	new_x = point->x - scalar * vector->x;
	new_y = point->y - scalar * vector->y;
	new_z = point->z - scalar * vector->z;

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

/// gpt
/* 
int	calculate_upper_left_corner(t_vp *vp)
{
	t_vector	h_half;
	t_vector	v_half;

	scalar_multiply_vector(WIN_WIDTH / 2.0, &vp->horizontal, &h_half);
	scalar_multiply_vector(WIN_HEIGHT / 2.0, &vp->vertical, &v_half);

	// point = vp_center - horizontal_half + vertical_half
	if (point_minus_vector(&vp->vp_center, &h_half, 1, &vp->point) == FAILURE)
		return (FAILURE);
	if (point_plus_vector(&vp->point, &v_half, 1, &vp->point) == FAILURE) // subtract vertical
		return (FAILURE);
	return (SUCCESS);
} */

