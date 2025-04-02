#include "../inc/miniRT.h"

void	get_up_vector(t_config *cf, t_vector *up)
{
	if (cf->cam.norm_vec.x == 0 && cf->cam.norm_vec.y == 0 && cf->cam.norm_vec.z != 0)
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

int	calculate_viewport_orientation(t_config *cf)
{
	t_vector	up;
	t_vector	horizontal;
	t_vector	vertical;

	// Define "world up" vector
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
	// Scale horizontal & vertical to match pixel spacing
	horizontal.x *= cf->viewp.width / WIN_WIDTH;
	horizontal.y *= cf->viewp.width / WIN_WIDTH;
	horizontal.z *= cf->viewp.width / WIN_WIDTH;

	vertical.x *= cf->viewp.height / WIN_HEIGHT;
	vertical.y *= cf->viewp.height / WIN_HEIGHT;
	vertical.z *= cf->viewp.height / WIN_HEIGHT;

	// Store in viewport
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
	if (!cf)
		return (FAILURE);

	double height = cf->viewp.width * VIEWPORT_RATIO_REVERSE;

	if (isnan(height) || height <= 0.0)
	{
		printf("Error calculating viewport width\n");
		return (FAILURE);
	}

	cf->viewp.height = height;
	return (SUCCESS);
}

/*calculate upper left corner point.
later this is the first pixel*/
int calculate_upper_left_corner(t_vp *viewp)
{
    t_vector half_horizontal;
    t_vector half_vertical;

    // Safety check
    if (!viewp)
        return (FAILURE);

    // Calculate half vectors
    half_horizontal.x = viewp->horizontal.x * 0.5 * WIN_WIDTH;
    half_horizontal.y = viewp->horizontal.y * 0.5 *  WIN_WIDTH;
    half_horizontal.z = viewp->horizontal.z * 0.5 *  WIN_WIDTH;

    half_vertical.x = viewp->vertical.x * 0.5 * WIN_HEIGHT;
    half_vertical.y = viewp->vertical.y * 0.5 * WIN_HEIGHT;
    half_vertical.z = viewp->vertical.z * 0.5 * WIN_HEIGHT;

    // Upper left corner = center - half_horizontal + half_vertical
    viewp->point.x = viewp->vp_center.x - half_horizontal.x - half_vertical.x;
    viewp->point.y = viewp->vp_center.y - half_horizontal.y - half_vertical.y;
    viewp->point.z = viewp->vp_center.z - half_horizontal.z - half_vertical.z;

    return (SUCCESS);
}

/*delegates viewport calculations*/
int	viewport_calculation(t_config *cf, t_mini_rt *rt)
{
	printf("meewo\n");
	init_viewport(&cf->viewp);
	//center view port
	if (point_plus_vector(&cf->cam.point, &cf->cam.norm_vec, 1, &cf->viewp.vp_center) == FAILURE)
		clean_exit_rt(rt, VIEWP_C);
	printf("meewo\n");
	//width
	if (calculate_width(cf) == FAILURE)
		clean_exit_rt(rt, NULL);
	//height
	if (calculate_height(cf) == FAILURE)
		clean_exit_rt(rt, NULL);
	//horizontal and vertical vector
	if (calculate_viewport_orientation(cf) == FAILURE)
		clean_exit_rt(rt, NULL);
	printf("meewo\n");
	//corner
	if (calculate_upper_left_corner(&cf->viewp) == FAILURE)
		clean_exit_rt(rt, NULL);
	print_viewport(&cf->viewp);
	return (SUCCESS);
}
