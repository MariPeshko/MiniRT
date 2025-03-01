/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:42:47 by mpeshko           #+#    #+#             */
/*   Updated: 2025/03/01 20:58:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	handle_close(t_config *cf)
{
	cleanup(cf);// Free resources and exit
	exit(SUCCESS);
	return (0);// Required return for mlx_hook callbacks
}

int	handle_keypress(int keycode, t_config *cf)
{
	if (keycode == ESC_KEY)
		cleanup(cf);
	exit(SUCCESS);
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
	rt->cf.mlx = NULL;
	rt->cf.win = NULL;
	rt->cf.mlx = mlx_init();
	if (!rt->cf.mlx)
		clean_exit(&rt->cf, MEMORY);
	rt->cf.win = mlx_new_window(rt->cf.mlx, 800, 600, "42 MinilibX Window");
	if (!rt->cf.win)
		clean_exit(&rt->cf, MEMORY);
	// Correctly pass rt.cf into the hook, do NOT call handle_close directly
	mlx_hook(rt->cf.win, DestroyNotify, 0, \
		(int (*)(void *))handle_close, &rt->cf);
	mlx_key_hook(rt->cf.win, (int (*)(int, t_config *))handle_keypress, \
		&(rt->cf));
}
