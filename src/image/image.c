/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:24:51 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 21:07:19 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

// Function to print color in HEX and DECIMAL
static int	get_intcolor_print_color(t_color color)
{
	int	r;
	int	g;
	int	b;
	int	color_int;

	r = color.r * 255;
	g = color.g * 255;
	b = color.b * 255;
	color_int = (r << 16) | (g << 8) | b;
	return (color_int);
}

void	put_pixel(t_img *img, int x, int y, t_color rgb_color)
{
	unsigned int	color;
	char			*dst;

	color = get_intcolor_print_color(rgb_color);
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
