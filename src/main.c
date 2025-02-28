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
	// Start the event loop
	mlx_loop(rt.cf.mlx);

	// Cleanup resources before exit
	cleanup(&rt.cf);
	printf("regular RETURN\n");
	return (SUCCESS);
}
