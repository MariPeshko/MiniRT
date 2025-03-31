#include "../inc/miniRT.h"

/*sets min to got, if got is closer than min*/
void	update_min(t_hit *min, t_hit *got)
{
	if (got->distance < min->distance)
		min = got;
}

void	init_hit(t_hit *hit)
{
	hit->type = NONE;
	hit->distance = -1;
}

/*fills hit struct with data*/
void	fill_hit(char	*object, double t, t_ray *ray, t_hit *hit)
{
	if (!object || !ray || !hit)
		return ;
	hit->type = object;
	hit->distance = t;
	point_plus_vector(&ray->c, &ray->v_dir, t, &hit->point);
}
