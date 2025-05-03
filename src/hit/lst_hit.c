/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:50:10 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:50:19 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*sets min to got, if got is closer than min*/
void	update_min(t_hit *min, t_hit *got)
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
	hit->id = -1;
	hit->cy_bottom = 0;
	hit->cy_top = 0;
}

/* fills hit struct with data with a got hit, got means current hit.
- type of the object
- distanse from camera to a hit point
- id of the objects (starts from 1) */
int	fill_hit(char *object, t_col *calc, int id, t_hit *got)
{
	t_ray	*ray;

	ray = &calc->ray;
	got->type = object;
	got->distance = calc->t1;
	got->id = id;
	if (point_plus_vector(&ray->c, &ray->v_dir, got->distance,
			&got->point) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	save_color(t_col *calc, t_color col)
{
	calc->hit_color.r = col.r;
	calc->hit_color.g = col.g;
	calc->hit_color.b = col.b;
}

void	reset_calc(t_col *calc)
{
	calc->t1 = -1;
	calc->t2 = -1;
	calc->quadratic_args[0] = 0;
	calc->quadratic_args[1] = 0;
	calc->quadratic_args[2] = 0;
}
