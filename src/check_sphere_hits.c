#include "../inc/miniRT.h"

int	get_hit_sphere(t_spher *sp, t_hit *got, t_ray *ray)
{
	if (sp && got && ray)
		return (SUCCESS);
	return (SUCCESS);
}

void	check_sphere_hit(t_config *cf, t_col *calc, t_ray *ray)
{
	t_spher *sp;

	sp = cf->sp;
	while (sp)
	{
		if (get_hit_sphere(sp, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		sp = sp->next;
	}
}
