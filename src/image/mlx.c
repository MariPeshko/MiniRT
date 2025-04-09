/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:04:37 by mpeshko           #+#    #+#             */
/*   Updated: 2025/04/09 19:04:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	handle_close(void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
	cleanup_cf(&rt->cf);
	cleanup_mlx(rt);
	exit(SUCCESS);
	return (0);
}

int	handle_keypress(int keycode, void *param)
{
	t_mini_rt	*rt;

	rt = (t_mini_rt *)param;
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
*/
void	setup_mlx(t_mini_rt *rt)
{
	rt->visual.mlx = mlx_init();
	if (!rt->visual.mlx)
		clean_exit_rt(rt, MEMORY);
	rt->visual.win = mlx_new_window(rt->visual.mlx, WIN_WIDTH, \
								WIN_HEIGHT, "42MiniRT");
	if (!rt->visual.win)
		clean_exit_rt(rt, MEMORY);
	mlx_hook(rt->visual.win, DestroyNotify, 0, handle_close, rt);
	mlx_key_hook(rt->visual.win, handle_keypress, rt);
}
