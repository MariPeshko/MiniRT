/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cam_lig.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:09:45 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/04 08:42:21 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void	apply_ambient_light(t_ambient *amb)
{
	t_color	result;

	result.r = (int)(amb->col.r * amb->lighting_ratio);
	result.g = (int)(amb->col.g * amb->lighting_ratio);
	result.b = (int)(amb->col.b * amb->lighting_ratio);
	amb->adjusted = result;
}

/* potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/
/*parses a line starting with A*/
int	full_parse_ambient(char *line, t_ambient *amb)
{
	int		pos;
	float	tmp;
	int		nmb_args;
	t_color	rgb;

	pos = 1;
	tmp = 0;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 3)
		return (display_error(INVALID_NBR_ARG));
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	amb->lighting_ratio = tmp;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&amb->col, rgb);
	apply_ambient_light(amb);
	return (SUCCESS);
}

/*parses a line starting with C*/
int	full_parse_camera(char *line, t_camera *camera)
{
	double	triplet[3];
	int		pos;
	float	tmp_fov;
	int		nmb_args;

	pos = 1;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG));
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&camera->point, triplet);
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&camera->norm_vec, triplet);
	if (normalize_vector(&camera->norm_vec) == FAILURE)
		return (FAILURE);
	if (get_float(line, &pos, &tmp_fov) == FAILURE)
		return (FAILURE);
	if (tmp_fov >= 180 || tmp_fov <= EPSILON)
		return (display_error(FOV_SCOPE));
	camera->fov = tmp_fov;
	return (SUCCESS);
}

/*parses a line starting with L*/
int	full_parse_light(char *line, t_light *light)
{
	int		pos;
	float	tmp;
	int		nmb_args;
	double	triplet[3];
	t_color	rgb;

	pos = 1;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG));
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&light->point, triplet);
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	light->bright = tmp;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&light->col, rgb);
	return (SUCCESS);
}
