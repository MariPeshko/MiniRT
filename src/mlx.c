#include "../inc/miniRT.h"

int handle_close(t_config *cf)
{
	cleanup(cf);// Free resources and exit
	return (0);// Required return for mlx_hook callbacks
}

int handle_keypress(int keycode, t_config *cf)
{
	if (keycode == ESC_KEY)
		cleanup(cf);
	exit(SUCCESS);
}

void	setup_mlx(t_mini_rt *rt)
{
	rt->cf.mlx = mlx_init();
	if (!rt->cf.mlx)
		clean_exit(&rt->cf, MEMORY);

	rt->cf.win = mlx_new_window(rt->cf.mlx, 800, 600, "42 MinilibX Window");
	if (!rt->cf.win)
		clean_exit(&rt->cf, MEMORY);

	// Correctly pass rt.cf into the hook, do NOT call handle_close directly
	mlx_hook(rt->cf.win, 17, 0, (int (*)(void *))handle_close, &rt->cf);
	mlx_key_hook(rt->cf.win, (int (*)(int, t_config *))handle_keypress, &(rt->cf));
}