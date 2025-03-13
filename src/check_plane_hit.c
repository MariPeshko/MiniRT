#include "../inc/miniRT.h"

int	get_hit_plane(t_plane *pl, t_hit *got, t_ray *ray)
{
	if (pl && got && ray)
		return (SUCCESS);
	return (SUCCESS);
}

void	check_plane_hit(t_config *cf, t_col *calc, t_ray *ray)
{
	t_plane *pl;
	
	pl = cf->pl;
	while (pl)
	{
		if (get_hit_plane(pl, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		pl = pl->next;
	}
}
