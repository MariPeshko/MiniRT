#include "../inc/miniRT.h"


int main(int argc, char **argv)
{
	t_mini_rt rt;

	if (argc != 2)
		arg_error(argc);
	if (open_config(argv[1], &rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);  // Load the configuration
	rt.visual.mlx = NULL;
	rt.visual.win = NULL;
	// Initialize mlx and window
	setup_mlx(&rt);
	//calculate viewport
	if (viewport_calculation(&rt.cf, &rt) == FAILURE)
	clean_exit(&(rt.cf), NULL);
	
	//calculate picture
	rays_loop(&rt);
	//display_picture - function man 3 mlx_pixel_put()
	// functions: mlx_new_image(), mlx_get_data_addr(),
	// mlx_put_image_to_window(), mlx_destroy_image()
	// instruction in minilibx/test/main.c

	color_map_1(&rt.visual, &rt.cf, WIN_WIDTH, WIN_HEIGHT);

	// Start the event loop
	//printf("hi\n");
	mlx_loop(rt.visual.mlx);

	// Cleanup resources before exit
	cleanup_mlx(&rt);
	cleanup_cf(&rt.cf);
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
