/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_plane_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:41:21 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 21:12:37 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// If dot product of ray direction and plane normal is near zero,
// the ray is parallel to the plane (no intersection unless on plane)
int	ray_paral_plane(t_ray *ray, t_plane *pl, double *denom, t_mini_rt *rt)
{
	double	dot_prod;

	if (dot_product(&ray->v_dir, &pl->pl_normal, &dot_prod) == FAILURE)
		clean_exit_rt(rt, CALC, D_P);
	if (fabs(dot_prod) < EPSILON)
	{
		return (true);
	}
	*denom = dot_prod;
	return (false);
}

// dot(P0 - ray_origin, plane_normal)
static int	get_plane_numerator(t_plane *pl, t_ray *ray, double *numerator)
{
	t_vector	origin_to_plane;

	if (point_minus_point(&pl->point, &ray->c, &origin_to_plane) == FAILURE)
		return (FAILURE);
	if (dot_product(&origin_to_plane, &pl->pl_normal, numerator) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * Compute t: distance along the ray where it 
 * hits the plane.
 * t = dot(P0 - ray_origin, plane_normal) / dot(ray_direction, plane_normal)
 */
int	get_hit_plane(t_plane *pl, t_ray *ray, t_mini_rt *rt)
{
	double	denominator;
	double	numerator;
	double	t;

	if (pl == NULL || ray == NULL)
		clean_exit_rt(rt, CALC, G_H_P);
	if (ray_paral_plane(ray, pl, &denominator, rt) == true)
		return (FAILURE);
	if (get_plane_numerator(pl, ray, &numerator) == FAILURE)
		clean_exit_rt(rt, CALC, G_P_N);
	t = numerator / denominator;
	rt->calc.t1 = t;
	if (t > EPSILON)
	{
		if (fill_hit(PLANE, &rt->calc, pl->id, &rt->calc.got) == FAILURE)
			clean_exit_rt(rt, CALC, F_H);
		return (SUCCESS);
	}
	return (FAILURE);
}

/*sets min to got, if got is closer than min*/
void	update_min_plane(t_hit *min, t_hit *got, t_plane *pl, t_col *calc)
{
	if (!min || !got)
		return ;
	if (got->distance == -1)
		return ;
	if (min->distance == -1 && got->distance > 0)
	{
		*min = *got;
		save_color(calc, pl->col);
	}
	else if (got->distance < min->distance)
	{
		*min = *got;
		save_color(calc, pl->col);
	}
}

void	check_plane_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_col	*calc;
	t_plane	*pl;

	calc = &rt->calc;
	pl = cf->pl;
	while (pl)
	{
		if (camera_on_the_plane(cf, pl, rt) == SUCCESS)
		{
			display_error(CAM_ON_PLANE);
			if (cam_dir_in_plane(cf->cam.norm_vec, pl->pl_normal) == FAILURE)
				clean_exit_rt(rt, NULL, NULL);
			clean_exit_rt(rt, CALC, C_P_H);
		}
		if (get_hit_plane(pl, ray, rt) == SUCCESS)
		{
			update_min_plane(&calc->min, &calc->got, pl, calc);
		}
		pl = pl->next;
	}
}
