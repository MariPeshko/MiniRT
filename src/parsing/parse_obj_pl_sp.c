/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_pl_sp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:13:14 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 20:20:03 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	assign_value_plane(char *line, t_plane *lst_pl)
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

static int	assign_value_sphere(char *line, t_spher *lst_sph)
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
