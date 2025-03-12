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

int	calculate_width(t_config *cf)
{
	if (!cf)
		return (FAILURE);

	double fov_radians = cf->cam.fov * (M_PI / 180.0);
	double width = 2.0 * tan(fov_radians / 2.0);

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
    viewp->point.x = viewp->c_point.x - half_horizontal.x - half_vertical.x;
    viewp->point.y = viewp->c_point.y - half_horizontal.y - half_vertical.y;
    viewp->point.z = viewp->c_point.z - half_horizontal.z - half_vertical.z;

    return (SUCCESS);
}

/*delegates viewport calculations*/
int	viewport_calculation(t_config *cf)
{
	printf("meewo\n");
	init_viewport(&cf->viewp);
	//center view port
	if (point_plus_vector(&cf->cam.point, &cf->cam.norm_vec, 1, &cf->viewp.c_point) == FAILURE)
		clean_exit(cf, VIEWP_C);
	printf("meewo\n");
	//width
	if (calculate_width(cf) == FAILURE)
		clean_exit(cf, NULL);
	//height
	if (calculate_height(cf) == FAILURE)
		clean_exit(cf, NULL);
	//horizontal and vertical vector
	if (calculate_viewport_orientation(cf) == FAILURE)
		clean_exit(cf, NULL);
	printf("meewo\n");
	//corner
	if (calculate_upper_left_corner(&cf->viewp) == FAILURE)
		clean_exit(cf, NULL);
	print_viewport(&cf->viewp);
	return (SUCCESS);
}