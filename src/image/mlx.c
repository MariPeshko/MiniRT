#include "../inc/miniRT.h"

int	handle_close(t_mini_rt *rt)
{
	cleanup_cf(&rt->cf);
	cleanup_mlx(rt);// Free resources and exit
	exit(SUCCESS);
	return (0);// Required return for mlx_hook callbacks
}

int	handle_keypress(int keycode, t_mini_rt *rt)
{
	if (keycode == ESC_KEY)
	{
		cleanup_cf(&rt->cf);
		cleanup_mlx(rt);
		exit(SUCCESS);
	}
	return (0);
}

/**
 * @brief 
 * 
 * mlx_new_window() creates a new window instance.
 * 
 * mlx_hook() — registers events. Allows you to listen for native X11 
 * events, such as mouse movements, key presses, window interaction, and more.
 * @param DestroyNotify (17) — an event,  indicates a window destruction
 * event. When the window is about to be destroyed (for example, when 
 * the user clicks the close button), this event is triggered.
 * 
 * mlx_key_hook() registers a function (handle_keypress) to be called 
 * when a key is released.
 * @cite int (*)(int, t_config *) is a function pointer type.
 * @cite int (*funct)() — a pointer to a function that takes unspecified 
 * parameters and returns an int.
 * @param (int (*)(int, t_config *))handle_keypress — this casts handle_keypress
 *  to match the expected function pointer type.
*/
void	setup_mlx(t_mini_rt *rt)
{
	rt->visual.mlx = mlx_init();

	if (!rt->visual.mlx)
		clean_exit_rt(rt, MEMORY);
	
	rt->visual.win = mlx_new_window(rt->visual.mlx, WIN_WIDTH, WIN_HEIGHT, "42 MinilibX Window");
	if (!rt->visual.win)
		clean_exit_rt(rt, MEMORY);
	// Correctly pass rt.cf into the hook, do NOT call handle_close directly
	mlx_hook(rt->visual.win, DestroyNotify, 0, \
		(int (*)(void *))handle_close, rt);
	mlx_key_hook(rt->visual.win, (int (*)(int, t_config *))handle_keypress, \
		rt);
}
