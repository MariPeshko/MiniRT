/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_help_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:40:34 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 20:53:56 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	init_col(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	init_point(t_point *p, double *triplet)
{
	if (p != NULL)
	{
		p->x = triplet[0];
		p->y = triplet[1];
		p->z = triplet[2];
	}
}

void	init_vec(t_vector *vec, double *triplet)
{
	if (vec != NULL)
	{
		vec->x = triplet[0];
		vec->y = triplet[1];
		vec->z = triplet[2];
	}
}
