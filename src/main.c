#include "../inc/miniRT.h"

int main(int argc, char **argv)
{
	t_mini_rt rt;

	if (argc != 2)
		arg_error(argc);
	if (open_config(argv[1], &rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);  // Load the configuration
	setup_mlx(&rt);
	if (viewport_calculation(&rt.cf, &rt) == FAILURE)
		clean_exit(&(rt.cf), NULL);
	
	//calculate picture
	rays_loop(&rt);
	mlx_put_image_to_window(rt.visual.mlx, rt.visual.win, \
							rt.visual.img.img_ptr, 0, 0);
	// Start the event loop
	mlx_loop(rt.visual.mlx);

	cleanup_mlx(&rt);
	cleanup_cf(&rt.cf);
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
