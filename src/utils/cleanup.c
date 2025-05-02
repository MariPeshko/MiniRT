/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:01:59 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:03:42 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	*free_cys(t_cys *cys)
{
	t_cys	*tmp;
	t_cys	*tmp2;

	tmp = cys->next;
	free(cys);
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	*free_sps(t_spher *sps)
{
	t_spher	*tmp;
	t_spher	*tmp2;

	tmp = sps->next;
	free(sps);
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

void	*free_pls(t_plane *pls)
{
	t_plane	*tmp;
	t_plane	*tmp2;

	tmp = pls->next;
	free(pls);
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
	return (NULL);
}

/* takes the main struct and error macro
displays error macro
frees all heap memory
exits
*/
int	cleanup_cf(t_config *cf)
{
	if (cf->cy)
		cf->cy = free_cys(cf->cy);
	if (cf->sp)
		cf->sp = free_sps(cf->sp);
	if (cf->pl)
		cf->pl = free_pls(cf->pl);
	return (SUCCESS);
}

int	cleanup_mlx(t_mini_rt *rt)
{
	if (rt->visual.img.img_ptr)
		mlx_destroy_image(rt->visual.mlx, rt->visual.img.img_ptr);
	if (rt->visual.win)
		mlx_destroy_window(rt->visual.mlx, rt->visual.win);
	if (rt->visual.mlx)
	{
		mlx_destroy_display(rt->visual.mlx);
		free(rt->visual.mlx);
	}
	return (SUCCESS);
}

void	clean_exit(t_config *cf, char *er_msg)
{
	cleanup_cf(cf);
	if (er_msg)
		display_error(er_msg);
	exit(FAILURE);
}

void	clean_exit_rt(t_mini_rt *rt, char *er_msg, char *place)
{
	cleanup_cf(&rt->cf);
	cleanup_mlx(rt);
	if (er_msg)
		display_error(er_msg);
	if (place)
		printf(RED "%s\n" RESET, place);
	exit(FAILURE);
}
