/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:58 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/03 11:31:11 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	in_light(t_mini_rt *rt, t_color_calc *coca)
{
	if (vector_multiply_vector(&coca->r_shadow.v_dir,
			&coca->hit_n, &coca->tmp) == FAILURE)
		clean_exit_rt(rt, CALC, I_L);
	if (coca->tmp < 0)
		return (false);
	if (plane_blocks_light(rt, coca) == true)
		return (false);
	if (sphere_blocks_light(rt, coca) == true)
		return (false);
	if (cylinder_blocks_light(rt, coca) == true)
		return (false);
	return (true);
}

void	get_ray_color(t_mini_rt *rt, t_point light, t_point hit_p)
{
	double	triplet[3];

	triplet[0] = light.x - hit_p.x;
	triplet[1] = light.y - hit_p.y;
	triplet[2] = light.z - hit_p.z;
	if (isnan(triplet[0]) || isnan(triplet[1]) || isnan(triplet[2])
		|| isinf(triplet[0]) || isinf(triplet[1]) || isinf(triplet[2]))
	{
		clean_exit_rt(rt, CALC, G_R_C);
	}
	rt->coca.r_shadow.c = hit_p;
	init_vec(&rt->coca.r_shadow.v_dir, triplet);
	rt->coca.l_distance = vector_length_light(&rt->coca.r_shadow.v_dir, rt);
	normalize_vector(&rt->coca.r_shadow.v_dir);
	return ;
}

/*claculates color of pixel based on hit*/
void	get_color(t_mini_rt *rt, t_color *color)
{
	t_color	ambient;
	t_color	diffuse;

	diffuse.r = 0;
	diffuse.g = 0;
	diffuse.b = 0;
	get_ray_color(rt, rt->cf.light.point, rt->calc.min.point);
	if (ft_strncmp(rt->calc.min.type, PLANE, 5) == SUCCESS)
		get_colors_plane(rt, &ambient, &diffuse);
	else if (ft_strncmp(rt->calc.min.type, SPHERE, 6) == SUCCESS)
		get_colors_sphere(rt, &ambient, &diffuse);
	else if (ft_strncmp(rt->calc.min.type, CYLINDER, 8) == SUCCESS)
		get_colors_cylinder(rt, &ambient, &diffuse);
	ambient.r += diffuse.r;
	ambient.g += diffuse.g;
	ambient.b += diffuse.b;
	ambient.r = powf(ambient.r, 1.0f / 2.2f);
	ambient.g = powf(ambient.g, 1.0f / 2.2f);
	ambient.b = powf(ambient.b, 1.0f / 2.2f);
	color->r = d_min(1.0, d_max(0, ambient.r));
	color->g = d_min(1.0, d_max(0, ambient.g));
	color->b = d_min(1.0, d_max(0, ambient.b));
	return ;
}
