#include "../inc/miniRT.h"

int	color_map_1(void *win, void *mlx, int w, int h)
{
	int	x;
	int	y;
	int	color;

	for (x = 0; x < w; x++)  // Loop over full width (1280)
	{
		for (y = 0; y < h; y++)  // Loop over full height (720)
		{
			color = (x * 255) / w + (((w - x) * 255) / w << 16) + ((y * 255) / h << 8);
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
	// Start the event loop
	printf(" => Colormap sans event ...");
  	color_map_1(rt.cf.win, rt.cf.mlx, WIN_WIDTH, WIN_HEIGHT);
	//printf("hi\n");
	mlx_loop(rt.cf.mlx);

	// Cleanup resources before exit
	cleanup(&rt.cf);
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
