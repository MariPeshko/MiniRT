#include "../inc/miniRT.h"

/*sets min to got, if got is closer than min*/
void update_min(t_hit *min, t_hit *got)
{
	if (!min || !got)
		return ;
	if (min->distance == -1 && got->distance > 0)
		*min = *got;
	else if (got->distance < min->distance)
		*min = *got;
}

void	init_hit(t_hit *hit)
{
	hit->type = NONE;
	hit->distance = -1;
}

/*fills hit struct with data*/
int	fill_hit(char *object, double t, t_ray *ray, t_hit *hit)
{
	if (!object || !ray || !hit)
		return (FAILURE);
	hit->type = object;
	hit->distance = t;
	if (point_plus_vector(&ray->c, &ray->v_dir, t, &hit->point) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
