/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:24:51 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:24:52 by sgramsch         ###   ########.fr       */
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

// 14126375 (decimal) = 0xD76167 (hex)
int	color_map_1(t_visual *vis, t_config *cf, int w, int h)
{
	//do we need this function at all? if not, please delete
	int		x;
	int		y;
	int		color;
	void	*win;
	void	*mlx;

	win = vis->win;
	mlx = vis->mlx;
	//delete if not needed please following print
	printf(" => Function to print color in HEX and DECIMAL ...\n");
	color = get_intcolor_print_color(cf->pl->col);
	for (x = 0; x < w; x++)
	{
		for (y = 0; y < h; y++)
		{
			//color = (x * 255) / w + (((w - x) * 255) / w << 16) + ((y * 255) / h << 8);
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return (0);
}
