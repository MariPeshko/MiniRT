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

/**
 * 
 */
int	get_hit_plane(t_plane *pl, t_hit *got, t_ray *ray)
{
	if (pl && got && ray)
	{
		// First, we should check, if the ray is parallel to the Plane.
		if (is_parallel(pl->pl_vec, ray->v_dir))
		{
			printf("This ray is parallel to the plane\n");
			return (FAILURE);
		}
		// The camera ray is on the plane.

	}
		return (SUCCESS);
	return (SUCCESS);
}

void	check_plane_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_col	*calc;
	t_plane *pl;

	calc = &rt->calc;	
	pl = cf->pl;
	while (pl)
	{
		// check if the camera is positioned on the plane
		// a) Camera's Direction is Parallel to the Plane 
		//		(Lies Inside the Plane)
		//		If the camera’s direction is exactly in 
		//		the plane (perpendicular to the normal), 
		//		consider warning the user.
		// b) other cases

		// Normal vector of the plane for calculation? (gpt && rasmus)
		if (get_hit_plane(pl, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		pl = pl->next;
	}
}
