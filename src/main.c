#include "../inc/miniRT.h"

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
	//display_picture
	// Start the event loop
	//printf("hi\n");
	mlx_loop(rt.cf.mlx);

	// Cleanup resources before exit
	cleanup(&rt.cf);
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
