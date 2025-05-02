/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:35:10 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:36:45 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	apply_ambient_light(t_ambient *amb)
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
	float	tmp = 0;
	int		nmb_args;
	t_color	rgb;

	pos = 1;
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
	int		tmp;
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
	if (get_int(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp > 180 || tmp < 0)
		return (display_error(FOV_SCOPE));
	camera->fov = tmp;
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

int	assign_value_plane(char *line, t_plane *lst_pl)
{
	int			pos;
	double		triplet[3];
	t_color		rgb;

	pos = 2;
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&lst_pl->point, triplet);
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&lst_pl->pl_normal, triplet);
	if (normalize_vector(&lst_pl->pl_normal) == FAILURE)
		return (FAILURE);
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&lst_pl->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with pl */
int	parse_plane(char *line, t_plane **plane)
{
	int			nmb_args;
	t_plane		*lst_pl;

	lst_pl = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG_PL));
	lst_pl = get_ptr_lst_pl(plane);
	if (lst_pl == NULL)
		return (FAILURE);
	if (assign_value_plane(line, lst_pl) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	assign_value_cyl(char *line, t_cys *cylinder)
{
	int		pos;
	float	tmp;
	double	triplet[3];

	pos = 2;
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&cylinder->point, triplet);
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&cylinder->norm_vec, triplet);
	if (normalize_vector(&cylinder->norm_vec) == FAILURE)
		return (FAILURE);
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp <= 0)
		return (display_error(CY_DIAMETER_SCOPE));
	cylinder->diam = tmp;
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	cylinder->height = tmp;
	t_color	rgb;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&cylinder->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with cy*/
int	parse_cylinder(char *line, t_cys **cylinder)
{
	int		nmb_args;
	t_cys	*lst_cyl;

	lst_cyl = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 6)
		return (display_error(INVALID_NBR_ARG_CY));
	lst_cyl = get_ptr_lst_cyl(cylinder);
	if (lst_cyl == NULL)
		return (FAILURE);
	if (assign_value_cyl(line, lst_cyl) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	assign_value_sphere(char *line, t_spher *lst_sph)
{
	int		pos;
	float	tmp;
	double	triplet[3];
	t_color	rgb;

	pos = 2;
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&lst_sph->point, triplet);
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp <= 0)
		return (display_error(SP_DIAMETER_SCOPE));
	lst_sph->diam = tmp;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&lst_sph->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with sp */
int	parse_sphere(char *line, t_spher **sphere)
{
	int			nmb_args;
	t_spher		*lst_sph;

	lst_sph = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG_SP));
	lst_sph = get_ptr_lst_sph(sphere);
	if (lst_sph == NULL)
		return (FAILURE);
	if (assign_value_sphere(line, lst_sph) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
