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
		up->x = 1;
		up->y = 0;
		up->z = 0;
	}
	else
	{
		up->x = 0;
		up->y = 0;
		up->z = 1;
	}
}

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
 * @param point - the upper left corner
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
	viewp->point.x = viewp->vp_center.x - half_horizontal.x - half_vertical.x;
	viewp->point.y = viewp->vp_center.y - half_horizontal.y - half_vertical.y;
	viewp->point.z = viewp->vp_center.z - half_horizontal.z - half_vertical.z;
	return (SUCCESS);
}
