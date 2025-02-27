#include "../inc/miniRT.h"

void cleanup_mlx(t_config *cf)
{
	if (cf->win)
		mlx_destroy_window(cf->mlx, cf->win);  // Free the window
	if (cf->mlx)
		mlx_destroy_display(cf->mlx);  // Destroy the mlx display
	clean_exit(cf, NULL);  // Perform any other cleanup and exit
}

int handle_close(t_config *cf)
{
	cleanup_mlx(cf);  // Free resources and exit
	return (0);  // Required return for mlx_hook callbacks
}

int handle_keypress(int keycode, t_config *cf)
{
	if (keycode == ESC_KEY)
		cleanup_mlx(cf);
	return (0);
}

void	setup_mlx(t_mini_rt *rt)
{
	rt->cf.mlx = NULL;
	rt->cf.win = NULL;
	rt->cf.mlx = mlx_init();
	if (!rt->cf.mlx)
		clean_exit(&rt->cf, MEMORY);  // Handle error and exit if mlx_init fails

	rt->cf.win = mlx_new_window(rt->cf.mlx, 800, 600, "42 MinilibX Window");
	if (!rt->cf.win)
		cleanup_mlx(&rt->cf);  // Free resources if window creation fails

	// Correctly pass rt.cf into the hook, do NOT call handle_close directly
	mlx_hook(rt->cf.win, 17, 0, (int (*)(void *))handle_close, &rt->cf);
	mlx_key_hook(rt->cf.win, (int (*)(int, t_config *))handle_keypress, &(rt->cf));
}

int main(int argc, char **argv)
{
	t_mini_rt rt;

	if (argc != 2)
		arg_error(argc);

	open_config(argv[1], &rt.cf);  // Load the configuration

	// Initialize mlx and window
	setup_mlx(&rt);
	// Start the event loop
	mlx_loop(rt.cf.mlx);

	// Cleanup resources before exit
	cleanup_mlx(&rt.cf);

	return (SUCCESS);
}
