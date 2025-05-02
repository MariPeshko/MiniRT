/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:55:03 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:55:11 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_mini_rt	rt;

	if (argc != 2)
		arg_error(argc);
	if (open_config(argv[1], &rt.cf) == FAILURE)
		clean_exit(&(rt.cf), NULL);
	setup_mlx(&rt);
	if (viewport_calculation(&rt.cf, &rt) == FAILURE)
		clean_exit(&(rt.cf), NULL);
	rays_loop(&rt);
	mlx_put_image_to_window(rt.visual.mlx, rt.visual.win, \
							rt.visual.img.img_ptr, 0, 0);
	mlx_loop(rt.visual.mlx);
	cleanup_mlx(&rt);
	cleanup_cf(&rt.cf);
	return (SUCCESS);
}
