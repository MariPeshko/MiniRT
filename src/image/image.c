#include "../../inc/miniRT.h"

// Function to print color in HEX and DECIMAL
static int	get_intcolor_print_color(t_color color)
{
	// Convert RGB to a single integer (0xRRGGBB)
	int	r;
	int	g;
	int	b;

	r = color.r * 255;
	g = color.r * 255;
	b = color.r * 255;
	int color_int = (r << 16) | (g << 8) | b;

	// Print HEX representation
	//printf("Hex: #%06X\n", color_int);

	// Print Decimal representation
	//printf("Decimal: %d\n", color_int);

	return (color_int);
}

void	put_pixel(t_img *img, int x, int y, t_color rgb_color)
{
	unsigned int color = get_intcolor_print_color(rgb_color);
	char			*dst;

	// Calculate the memory offset to pixel (x, y)
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	// Write the color value into the memory as a 32-bit pixel
	*(unsigned int *)dst = color;
}

// printf("x: %d, y: %d\n", x, y);
	// img->height = 50;
	// printf("%u\n", color);
	

// 14126375 (decimal) = 0xD76167 (hex)
int	color_map_1(t_visual *vis, t_config *cf, int w, int h)
{
	int	x;
	int	y;
	int	color;
	void *win = vis->win;
	void *mlx = vis->mlx;

	printf(" => Function to print color in HEX and DECIMAL ...\n");
	// get_the_color_of_the_plane
	color = get_intcolor_print_color(cf->pl->col);

	for (x = 0; x < w; x++)  // Loop over full width (1280)
	{
		for (y = 0; y < h; y++)  // Loop over full height (720)
		{
			//color = (x * 255) / w + (((w - x) * 255) / w << 16) + ((y * 255) / h << 8);
			// if ((y % 200 == 0) && (x % 200 == 0))
			// 	printf("color: %d\n", color);
			mlx_pixel_put(mlx, win, x, y, color);
		}
	}
	return 0;
}
