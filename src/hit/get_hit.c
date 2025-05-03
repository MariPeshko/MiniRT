/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:50:28 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:50:28 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*for a single ray, find closest collision.
return SUCCESS or FAILURE if ther is /isnt a collision*/
int	get_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	init_hit(&rt->calc.got);
	init_hit(&rt->calc.min);
	check_plane_hit(cf, rt, ray);
	check_sphere_hit(cf, rt, ray);
	check_cys_hit(cf, rt, ray);
	if (ft_strncmp(rt->calc.min.type, NONE, 4) != SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

/**
 * 1. Compute the Direction Vector.
 * 2. Store the Ray Origin (camera).
 * 3. Initialize the Ray Direction Vector.
 * Note: we’ve already normalized the basis vectors when 
 * setting up the viewport, you don't need to normalize 
 * the ray direction again when calculating each ray.
*/
void	get_ray(t_mini_rt *rt, t_point pixel, t_point camera)
{
	double	triplet[3];

	triplet[0] = pixel.x - camera.x;
	triplet[1] = pixel.y - camera.y;
	triplet[2] = pixel.z - camera.z;
	if (isnan(triplet[0]) || isnan(triplet[1]) || isnan(triplet[2])
		|| isinf(triplet[0]) || isinf(triplet[1]) || isinf(triplet[2]))
	{
		clean_exit_rt(rt, CALC, G_R);
	}
	rt->calc.ray.c = camera;
	init_vec(&rt->calc.ray.v_dir, triplet);
	return ;
}

//gets the coordinates of a pixel
void	get_pixel(t_vp vp, int h, int w, t_point *pixel)
{
	pixel->x = vp.upperleft.x + h * vp.vertical.x + w * vp.horizontal.x;
	pixel->y = vp.upperleft.y + h * vp.vertical.y + w * vp.horizontal.y;
	pixel->z = vp.upperleft.z + h * vp.vertical.z + w * vp.horizontal.z;
}

void	init_coca(t_color_calc *coca)
{
	coca->pl = NULL;
	coca->sp = NULL;
	coca->cy = NULL;
	coca->L_distance = -1;
}

/*moves through pixels and delegates coloring it.
at the end: displayable picture*/
int	rays_loop(t_mini_rt *rt)
{
	int	h;
	int	w;

	h = 0;
	while (h < rt->visual.img.height)
	{
		w = 0;
		while (w < rt->visual.img.width)
		{
			init_coca(&rt->coca);
			get_pixel(rt->cf.viewp, h, w, &rt->calc.pixel);
			get_ray(rt, rt->calc.pixel, rt->cf.cam.point);
			if (get_hit(&rt->cf, rt, &rt->calc.ray) == SUCCESS)
			{
				get_color(rt, &rt->calc.hit_color);
				put_pixel(&rt->visual.img, w, h, rt->calc.hit_color);
			}
			else
				put_pixel(&rt->visual.img, w, h, rt->cf.amb.adjusted);
			w++;
		}
		h++;
	}
	return (SUCCESS);
}
