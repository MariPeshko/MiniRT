#include "../../inc/miniRT.h"

// Function to print color in HEX and DECIMAL
static int	get_intcolor_print_color(t_color color)
{
	// Convert RGB to a single integer (0xRRGGBB)
	int color_int = (color.r << 16) | (color.g << 8) | color.b;

	// Print HEX representation
	printf("Hex: #%06X\n", color_int);

	// Print Decimal representation
	printf("Decimal: %d\n", color_int);

	return (color_int);
}

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
