/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_cyl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:35:10 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 20:32:48 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	assign_value_cyl_01(char *line, t_cys *cylinder, int *pos)
{
	t_color	rgb;

	if (get_rgb(line, pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&cylinder->col, rgb);
	return (SUCCESS);
}

static int	assign_value_cyl_00(char *line, t_cys *cylinder, int *pos)
{
	float	diam;
	double	triplet[3];

	if (get_three_floats(line, pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&cylinder->point, triplet);
	if (get_three_floats(line, pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&cylinder->norm_vec, triplet);
	if (normalize_vector(&cylinder->norm_vec) == FAILURE)
		return (FAILURE);
	if (get_float(line, pos, &diam) == FAILURE)
		return (FAILURE);
	if (diam <= 0)
		return (display_error(CY_DIAMETER_SCOPE));
	cylinder->diam = diam;
	if (get_float(line, pos, &diam) == FAILURE)
		return (FAILURE);
	cylinder->height = diam;
	return (SUCCESS);
}

/* parses a line starting with cy*/
int	parse_cylinder(char *line, t_cys **cylinder)
{
	int		nmb_args;
	t_cys	*lst_cyl;
	int		pos;

	pos = 2;
	lst_cyl = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 6)
		return (display_error(INVALID_NBR_ARG_CY));
	lst_cyl = get_ptr_lst_cyl(cylinder);
	if (lst_cyl == NULL)
		return (FAILURE);
	if (assign_value_cyl_00(line, lst_cyl, &pos) == FAILURE)
		return (FAILURE);
	if (assign_value_cyl_01(line, lst_cyl, &pos) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
