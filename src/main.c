#include "../inc/miniRT.h"

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
int	color_map_1(t_config *cf, int w, int h)
{
	int	x;
	int	y;
	int	color;
	void *win = cf->win;
	void *mlx = cf->mlx;

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

int main(int argc, char **argv)
{
	t_mini_rt rt;

	if (argc != 2)
		arg_error(argc);

	if (open_config(argv[1], &rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);  // Load the configuration

	// Initialize mlx and window
	setup_mlx(&rt);

	//calculate viewport
	if (viewport_calculation(&rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);
	
	//calculate picture
	rays_loop(&rt);
	//display_picture - function man 3 mlx_pixel_put()
	// functions: mlx_new_image(), mlx_get_data_addr(),
	// mlx_put_image_to_window(), mlx_destroy_image()
	// instruction in minilibx/test/main.c
	// Start the event loop
	printf(" => Colormap sans event ...\n");
  	color_map_1(&rt.cf, WIN_WIDTH, WIN_HEIGHT);
	
	mlx_loop(rt.cf.mlx);
	// Cleanup resources before exit
	cleanup(&rt.cf);
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
