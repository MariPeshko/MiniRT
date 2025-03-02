#include "../inc/miniRT.h"

int	viewport_calculation(t_config *cf)
{
	if (cf)
		return (SUCCESS);
	return (SUCCESS);
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

	//calculate picture
	if (viewport_calculation(&rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);
	//display_picture
	// Start the event loop
	mlx_loop(rt.cf.mlx);

	// Cleanup resources before exit
	cleanup(&rt.cf);
	printf("regular RETURN\n");
	/*technically we shouldn't ever end up here, since both clean ways to end
	the program (esc and X) both exit in the signal handler but well, we'll see. */
	return (SUCCESS);
}
