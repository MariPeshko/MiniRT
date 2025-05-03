/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_ins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:50:25 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 21:04:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	dist_squared(t_cys cyl, double distance_squared)
{
	double		radius;

	radius = cyl.diam / 2;
	if (distance_squared < radius * radius)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * proj - Projected vector along the cylinder axis
 * if (projection_length < 0 || projection_length > cyl.height)
 * // outside vertically
 * v_perp - Perpendicular vector
 */
int	check_camera_inside_cylinder(t_point camera_pos, t_cys cyl)
{
	t_vector	v;
	double		projection_length;
	t_vector	proj;
	t_vector	v_perp;
	double		distance_squared;

	point_minus_point(&camera_pos, &cyl.point, &v);
	dot_product(&v, &cyl.norm_vec, &projection_length);
	if (projection_length < 0 || projection_length > cyl.height)
		return (SUCCESS);
	proj.x = projection_length * cyl.norm_vec.x;
	proj.y = projection_length * cyl.norm_vec.y;
	proj.z = projection_length * cyl.norm_vec.z;
	subtract_vectors(&v, &proj, &v_perp);
	if (dot_product(&v_perp, &v_perp, &distance_squared) == FAILURE)
		return (FAILURE);
	if (dist_squared(cyl, distance_squared) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	cam_inside_cyl(t_config *cf)
{
	t_cys	*cy;

	cy = cf->cy;
	while (cy)
	{
		if (check_camera_inside_cylinder(cf->cam.point, *cy) == FAILURE)
		{
			display_error(CAM_INS_CY);
			return (FAILURE);
		}
		cy = cy->next;
	}
	return (SUCCESS);
}

static void	check_camera_inside_sphere(t_point camera_pos,
	t_point sphere_center, double diametr)
{
	double	radius;
	double	dx;
	double	dy;
	double	dz;
	double	distance_squared;

	radius = diametr / 2;
	dx = camera_pos.x - sphere_center.x;
	dy = camera_pos.y - sphere_center.y;
	dz = camera_pos.z - sphere_center.z;
	distance_squared = dx * dx + dy * dy + dz * dz;
	if (distance_squared < radius * radius)
	{
		printf(GREEN "Message: " RESET);
		printf("Camera is inside the sphere!\n");
	}
}

void	cam_inside_sphere(t_config *cf)
{
	t_spher	*sp;

	sp = cf->sp;
	while (sp)
	{
		check_camera_inside_sphere(cf->cam.point, sp->point, sp->diam);
		sp = sp->next;
	}
}
