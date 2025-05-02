/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:41:07 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 18:03:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/**
 * Camera's Direction is Parallel to the Plane and 
 * lies Inside the Plane.
*/
int	cam_dir_in_plane(t_vector cam_dir, t_vector pl_normal)
{
	double	dot_prod;

	if (dot_product(&cam_dir, &pl_normal, &dot_prod) == FAILURE)
	{
		printf("Error\nCamera_direction_in_plane(). Error dot_product\n");
		return (FAILURE);
	}
	if (fabs(dot_prod) < EPSILON)
	{
		display_error(CAM_DIR_ON_PLANE);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	camera_on_the_plane(t_config *cf, t_plane *pl, t_mini_rt *rt)
{
	t_vector	cam_to_plane;
	double		dot_prod;

	if (point_minus_point(&cf->cam.point, &pl->point, &cam_to_plane) == FAILURE)
		clean_exit_rt(rt, CALC, C_C_O_P);
	if (dot_product(&pl->pl_normal, &cam_to_plane, &dot_prod) == FAILURE)
		clean_exit_rt(rt, CALC, C_C_O_P);
	if (fabs(dot_prod) < EPSILON)
		return (SUCCESS);
	return (FAILURE);
}
