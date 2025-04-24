#include "../inc/miniRT.h"

double	vector_length_cy(t_vector *v, t_mini_rt *rt)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (isnan(length) || isinf(length))
		clean_exit_rt(rt, CALC, V_L_CY);
	return (length);
}

int	get_cys_top_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	//get top center point
	t_point center;
	t_vector tmp;

	if (point_plus_vector(&cy->point, &cy->norm_vec, cy->height / 2, &center) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_P_V);
	//d*v
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	/*if ray is parallel to plane, we have either 0 hits, so return failure. 
	or we have ray in plane. but ray in plane in this case means that we found the closest 
	collision on the cylinder top on the wall already, so we can ignore this case, right?*/
	//check d*v isnt 0
	if (rt->calc.t2 == 0)
		return (FAILURE);
	//fraction upper part
	if (point_minus_point(&center, &ray->c, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_multiply_vector(&tmp, &cy->norm_vec, &rt->calc.t1) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);

	//t = ((c-o) * v) / (d*v) 
	rt->calc.t1 = rt->calc.t1 / rt->calc.t2;
	if (isnan(rt->calc.t1) || isinf(rt->calc.t1))
		clean_exit_rt(rt, CALC_CT, NULL);
	fill_hit(CYLINDER, &rt->calc, cy->id, new);
	//check collision point is relevant
	if (point_minus_point(&new->point, &center, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	//cy diameter must be > 0 due to parsing rules so
	//print_vec(&tmp);
	if (vector_length_cy(&tmp, rt) > (cy->diam / 2))
		return (FAILURE);
	//fill the hit with it.
	return (SUCCESS);
}

int	get_cys_bottom_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	//get top center point
	t_point center;
	t_vector tmp;

	if (point_plus_vector(&cy->point, &cy->norm_vec, ((cy->height / 2) * -1), &center) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_P_V);
	//d*v
	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);
	/*if ray is parallel to plane, we have either 0 hits, so return failure. 
	or we have ray in plane. but ray in plane in this case means that we found the closest 
	collision on the cylinder top on the wall already, so we can ignore this case, right?*/
	//check d*v isnt 0
	if (rt->calc.t2 == 0)
		return (FAILURE);
	//fraction upper part
	if (point_minus_point(&center, &ray->c, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	if (vector_multiply_vector(&tmp, &cy->norm_vec, &rt->calc.t1) == FAILURE)
		clean_exit_rt(rt, CALC_CT, V_M_V);

	//t = ((c-o) * v) / (d*v) 
	rt->calc.t1 = rt->calc.t1 / rt->calc.t2;
	if (isnan(rt->calc.t1) || isinf(rt->calc.t1))
		clean_exit_rt(rt, CALC_CT, NULL);
	fill_hit(CYLINDER, &rt->calc, cy->id, new);
	//check collision point is relevant
	if (point_minus_point(&new->point, &center, &tmp) == FAILURE)
		clean_exit_rt(rt, CALC_CT, P_M_P);
	//cy diameter must be > 0 due to parsing rules so
	if (vector_length_cy(&tmp, rt) > (cy->diam / 2))
		return (FAILURE);
	//fill the hit with it.
	return (SUCCESS);
}

/*saves the closest collision with a single cylinder in got*/
int	get_hit_cys(t_mini_rt *rt, t_cys *cy, t_ray *ray)
{
	t_hit	new;

	init_hit(&new);
	reset_calc(&rt->calc);
	if (get_cys_wall_collision(rt, cy, &new, ray) == SUCCESS)
	{
		update_min(&rt->calc.got, &new);
		//printf("got type = %s\n", rt->calc.got.type);
	}
	if (get_cys_top_collision(rt, cy, &new, ray) == SUCCESS)
	{
		new.cy_top = 1;
		update_min(&rt->calc.got, &new);
	}
	if (get_cys_bottom_collision(rt, cy, &new, ray) == SUCCESS)
	{
		new.cy_bottom = 1;
		update_min(&rt->calc.got, &new);
	}
	if (rt->calc.got.distance == 0)
		clean_exit_rt(rt, C_IN_CY, G_H_C);
	if (rt->calc.got.distance == -1)
		return (FAILURE);
	return (SUCCESS);
}

/*sets min to got, if got is closer than min*/
void update_min_cy(t_hit *min, t_hit *got, t_cys *cy, t_col *calc)
{
	if (!min || !got)
		return ;
	if (got->distance == -1)
		return ;
	if (min->distance == -1 && got->distance > 0)
	{
		*min = *got;
		save_color(calc, cy->col);
	}
	else if (got->distance < min->distance)
	{
		*min = *got;
		save_color(calc, cy->col);
	}
}

/*delegates collision check for all cylinders.
saves closest visible one  in rt->calc->min*/
void	check_cys_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_cys	*cy;
	t_col	*calc;

	calc = &rt->calc;
	cy = cf->cy;
	while (cy)
	{
		init_hit(&calc->got);
		if (get_hit_cys(rt, cy, ray) == SUCCESS)
		{
			update_min_cy(&calc->min, &calc->got, cy, calc);
			printf("got / min id %d / %d\n", calc->got.id, calc->min.id);
		}
			
		cy = cy->next;
	}
}
