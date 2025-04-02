#include "../inc/miniRT.h"

int main(int argc, char **argv)
{
	t_mini_rt rt;

	if (argc != 2)
		arg_error(argc);

	if (open_config(argv[1], &rt.cf) == FAILURE)
		clean_exit_rt(&rt, NULL);  // Load the configuration

	// Initialize mlx and window
	setup_mlx(&rt);

	//calculate viewport
	if (viewport_calculation(&rt.cf, &rt) == FAILURE)
		clean_exit_rt(&rt, NULL);
	
	//calculate picture
	rays_loop(&rt);
	//display_picture
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
