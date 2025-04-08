#include "../inc/miniRT.h"

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

static int	calc_center_viewport(t_config *cf, double scalar)
{
	if (point_plus_vector(&cf->cam.point, &cf->cam.norm_vec,
			scalar, &cf->viewp.vp_center) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * initialized viewport struct
 * @param point - upper-left corner aka first pixel.
 * @param c_point - easier access to Camera point?
 * @param horizontal - from one pixel to next in row.
 * @param vertical - from one pixel to next in column
*/
void	init_viewport(t_vp *vp)
{
	double	triplet[3];

    triplet[0] = 0.0;
    triplet[1] = 0.0;
    triplet[2] = 0.0;
	if (!vp)
		return ;
	// Initialize the corner point and c_point to (0, 0, 0)
	init_point(&vp->point, triplet);
	init_point(&vp->vp_center, triplet);

	// Initialize the horizontal and vertical vectors to (0, 0, 0)
	init_vec(&vp->horizontal, triplet);
	init_vec(&vp->vertical, triplet);

	// Set width and height to 0
	vp->width = 0;
	vp->height = 0;
}

/** delegates viewport calculations
 * - calculate the center view port
 * - calculate the width and the height
 * - calculate the viewport orientation, horizontal and vertical vectors
 * - calculate the upper left corner
*/
int	viewport_calculation(t_config *cf)
{
	init_viewport(&cf->viewp);
	if (calc_center_viewport(cf, 1) == FAILURE)
		clean_exit(cf, VIEWP_C);
	if (calculate_width(cf) == FAILURE)
		clean_exit(cf, NULL);
	if (calculate_height(cf) == FAILURE)
		clean_exit(cf, NULL);
	if (calculate_viewport_orientation(cf) == FAILURE)
		clean_exit(cf, NULL);
	if (calculate_upper_left_corner(&cf->viewp) == FAILURE)
		clean_exit(cf, NULL);
	//print_viewport(&cf->viewp);
	return (SUCCESS);
}
