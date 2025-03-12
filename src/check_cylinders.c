#include "../inc/miniRT.h"

int	get_hit_cys(t_cys *cy, t_hit *got, t_ray *ray)
{

	if (cy && got && ray)
		return (SUCCESS);
	return (SUCCESS);
}

void	check_cys_hit(t_config *cf, t_col *calc, t_ray *ray)
{
	t_cys *cy;
	
	cy = cf->cy;
	while (cy)
	{
		if (get_hit_cys(cy, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		cy = cy->next;
	}
}