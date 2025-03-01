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
}//set cys to NULL

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
int	cleanup(t_config *cf)//rename cleanup and exit
{
	if (cf->cy)
		cf->cy = free_cys(cf->cy);
	if (cf->sp)
		cf->sp = free_sps(cf->sp);
	if (cf->pl)
		cf->pl = free_pls(cf->pl);
	if (cf->win)
		mlx_destroy_window(cf->mlx, cf->win);// Free the window
	if (cf->mlx)
		mlx_destroy_display(cf->mlx);// Destroy the mlx display
	free(cf->mlx);
	return (SUCCESS);
}

void	clean_exit(t_config *cf, char *er_msg)
{
	cleanup(cf);
	if (er_msg)
		display_error(er_msg);
	exit(FAILURE);
}

void	clean_exit_from_parsing(t_config *cf, char *er_msg, char *line)
{
	if (line)
		free(line);
	clean_exit(cf, er_msg);
}