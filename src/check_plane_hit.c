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
int	ray_parallel_to_plane(t_ray *ray, t_plane *pl)
{
	double	result;

	dot_product(&ray->v_dir, &pl->pl_normal, &result);
	if(result == 0)
	{
		printf("dot product of d * n is 0\n");
		printf("the ray is parallel to the Plane\n");
		return(true);
	}
	else
		return(false);
}

/**
 * 
 */
int	get_hit_plane(t_plane *pl, t_hit *got, t_ray *ray)
{
	if (pl && got && ray)
	{
		// First, we should check, if the ray is parallel to the Plane.
		if (ray_parallel_to_plane(ray, pl) == true)
			printf("The ray and a plane are parallel, no intersections\n");
	}
		return (SUCCESS);
	return (SUCCESS);
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
		printf("Warning! The camera’s direction is exactly in the plane\n");
		// proper error
		// clean exit
		return (SUCCESS);
	}
	else
		return (FAILURE);
}

void	check_plane_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_col	*calc;
	t_plane *pl;

	calc = &rt->calc;	
	pl = cf->pl;
	while (pl)
	{
		
		if (camera_on_the_plane(cf, pl) == SUCCESS)
		{
			printf("Camera is embedded in the plane\n");
			// proper error
			// clean exit
			camera_direction_in_plane(cf->cam.norm_vec, pl->pl_normal);
		}
		if (get_hit_plane(pl, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		pl = pl->next;
	}
}
