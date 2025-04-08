#include "../inc/miniRT.h"

// Are vectors parallel? If yes, true returns.
int	is_parallel(t_vector first, t_vector second)
{
	if ((first.x / second.x == first.y / second.y) && 
		(first.y / second.y  == first.z / second.z))
		return(true);
	else
		return (false);
}
// First, we should check, if the ray is parallel to the Plane.
// If The camera ray is on the plane: how to check it?
// d * n is not 0
// d = direction vector of a ray (Pixel - Camera)
// n - normal normal vector to the plane (perpendicular to the plane)
int	ray_parallel_to_plane(t_ray *ray, t_plane *pl, double *divisor)
{
	double	result = -4;

	dot_product(&ray->v_dir, &pl->pl_normal, &result);
	if (fabs(result) < DBL_EPSILON)
	{
		/* printf("Plane. Dot product of d * n is 0\n");
		printf("So this ray is parallel to the Plane\n"); */
		return(true);
	}
	else
	{
		*divisor = result;
		return(false);
	}
	return (false);
}

// dot(P0 - ray_origin, plane_normal)
int	plane_numerator(t_plane *pl, t_ray *ray, double *numerator)
{
	t_vector	origin_to_plane;
	point_minus_point(&pl->point, &ray->c, &origin_to_plane);
	dot_product(&origin_to_plane, &pl->pl_normal, numerator);
	return (SUCCESS);
}

int	calc_plane_point(t_ray *ray, double t, t_point *point_on_ray)
{
	t_vector	result;

	scalar_multiply_vector(t, &ray->v_dir, &result);
	//print_vec(&result, "result");
	point_plus_vector(&ray->c, &result, 1, point_on_ray);
	return (SUCCESS);
}

/**
 * t = dot(P0 - ray_origin, plane_normal) / dot(ray_direction, plane_normal)
 */
int	get_hit_plane(t_plane *pl, t_hit *got, t_ray *ray)
{
	double	denominatior = -2;
	double	numerator = -2;
	double	t = -2;

	init_hit(got);
	if (pl && got && ray)
	{
		// First, we should check, if the ray is parallel to the Plane.
		if (ray_parallel_to_plane(ray, pl, &denominatior) == true)
			return (FAILURE);
		plane_numerator(pl, ray, &numerator);
		//printf("numerator: %f\n", numerator);
	}
	t = numerator / denominatior;
	//printf("t scalar is: %f\n", t);
	if (t > 0)
	{
		fill_hit(PLANE, t, ray, got);
		//print_point(&got->point, "plane");
		return (SUCCESS);
	}
	else if (t < 0)
	{
		return (FAILURE);
	}
	return (FAILURE);
}

/**
 * Check if the camera is positioned on the plane.
*/
int	camera_on_the_plane(t_config *cf, t_plane *pl)
{
	t_vector camera_to_plane;
	if(point_minus_point(&cf->cam.point, &pl->point, &camera_to_plane) == FAILURE)
	{
		printf("Camera on plane FAILURE\n");
		return(FAILURE);
	}
	double	result;
	if (vector_multiply_vector(&pl->pl_normal, &camera_to_plane, &result) == FAILURE)
	{
		printf("dot_product plane normal and camera_to_plane FAILURE\n");
		return(FAILURE);
	}
	if(result == 0)
		return(SUCCESS);
	return(FAILURE);
}

/**
 * Camera's Direction is Parallel to the Plane and lies Inside the 
 * Plane.
*/
int	camera_direction_in_plane(t_vector cam_dir, t_vector pl_normal)
{
	double	result;
	if(dot_product(&cam_dir, &pl_normal, &result) == FAILURE)
	{
		printf("Error dot_product\n");
		return (FAILURE);
	}
	if (result == 0)
	{
		display_error(CAM_DIR_ON_PLANE);
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	check_plane_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_col	*calc;
	t_plane	*pl;

	calc = &rt->calc;	
	pl = cf->pl;
	while (pl)
	{
		if (camera_on_the_plane(cf, pl) == SUCCESS)
		{
			display_error(CAM_ON_PLANE);
			camera_direction_in_plane(cf->cam.norm_vec, pl->pl_normal);
			clean_exit_rt(rt, CALC);
		}
		if (get_hit_plane(pl, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		pl = pl->next;
	}
}
