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

/** Calculate viewport orientation.
 * - Define "world up" vector.
 * ...
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

/**
 * Calculating the width of the viewport at a distance 
 * of 1 unit from the camera.
 * 
 * 1. It converts the camera's field of view (FOV) from degrees 
 * to radians. It multiplies the FOV in degrees by π/180.
 * 2. It calculates the width of the viewport. The tan() function
 * calculates the tangent of half the FOV in radians. Then it 
 * is multiplied by 2.
*/
int	calculate_width(t_config *cf)
{
	double	fov_radians;
	double	width;

	if (!cf)
		return (FAILURE);
	fov_radians = cf->cam.fov * (M_PI / 180.0);
	width = 2.0 * tan(fov_radians / 2.0);
	if (isnan(width) || width <= 0.0)
	{
		printf("Error calculating viewport height\n");
		return (FAILURE);
	}
	cf->viewp.width = width;
	return (SUCCESS);
}

int	calculate_height(t_config *cf)
{
	double	height;

	if (!cf)
		return (FAILURE);
	height = cf->viewp.width * VIEWPORT_RATIO_REVERSE;
	if (isnan(height) || height <= 0.0)
	{
		printf("Error calculating viewport width\n");
		return (FAILURE);
	}
	cf->viewp.height = height;
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

static int	calc_center_viewport(t_config *cf, double scalar)
{
	if (point_plus_vector(&cf->cam.point, &cf->cam.norm_vec,
			scalar, &cf->viewp.vp_center) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/** delegates viewport calculations
 * - calculate the center view port
 * - calculate the width and the height
 * - calculate the viewport orientation, horizontal and vertical vectors
 * - calculate the upper left corner
*/
int	viewport_calculation(t_config *cf)
{
	printf("meewo\n");
	init_viewport(&cf->viewp);
	if (calc_center_viewport(cf, 1) == FAILURE)
		clean_exit(cf, VIEWP_C);
	printf("meewo\n");
	if (calculate_width(cf) == FAILURE)
		clean_exit(cf, NULL);
	if (calculate_height(cf) == FAILURE)
		clean_exit(cf, NULL);
	if (calculate_viewport_orientation(cf) == FAILURE)
		clean_exit(cf, NULL);
	printf("meewo\n");
	if (calculate_upper_left_corner(&cf->viewp) == FAILURE)
		clean_exit(cf, NULL);
	print_viewport(&cf->viewp);
	return (SUCCESS);
}
