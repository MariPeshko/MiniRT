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