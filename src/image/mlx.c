/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 19:04:37 by mpeshko           #+#    #+#             */
/*   Updated: 2025/04/11 22:52:36 by mpeshko          ###   ########.fr       */
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

static int	setup_img(t_mini_rt *rt)
{
	t_img *image;

	// &(rt->visual.img) = ft_calloc(1, sizeof(t_img));
	// if (!rt->visual.img)
	// 	return (FAILURE);
	image = &rt->visual.img;
	image->width = rt->visual.width;
	image->height = rt->visual.height;
	image->img_ptr = mlx_new_image(rt->visual.mlx, image->width, image->height);
	if (!image->img_ptr)
		return (FAILURE);
	image->data = mlx_get_data_addr(image->img_ptr, &image->bpp, \
									&image->line_len, &image->endian);
	return (SUCCESS);
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
	int	x;
	int	y;
	
	rt->visual.mlx = NULL;
	rt->visual.mlx = mlx_init();
	if (!rt->visual.mlx)
		clean_exit_rt(rt, MLX_INIT);
	mlx_get_screen_size(rt->visual.mlx, &x, &y);
	if (x > 0 && y > 0 && MAN == false)
	{
		rt->visual.width = x * 0.8;
		rt->visual.height = y * 0.8;
	}
	else
	{
		rt->visual.width = WIN_WIDTH;
		rt->visual.height = WIN_HEIGHT;
	}
	rt->visual.win = NULL;
	rt->visual.win = mlx_new_window(rt->visual.mlx, rt->visual.width, \
								rt->visual.height, "42MiniRT");
	if (!rt->visual.win)
		clean_exit_rt(rt, MLX_WIN_INIT);
	if (setup_img(rt) == FAILURE)
		clean_exit_rt(rt, MLX_IMG_INIT);
	mlx_hook(rt->visual.win, DestroyNotify, 0, handle_close, rt);
	mlx_key_hook(rt->visual.win, handle_keypress, rt);
}
