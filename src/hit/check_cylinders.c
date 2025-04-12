/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:07:45 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/12 14:30:40 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	check_height_two(t_mini_rt *rt, t_ray *ray, t_cys *cy, double *t)
{
	t_point		p;
	double		vertical;
	t_vector	v;

	if (point_plus_vector(&ray->c, &ray->v_dir, *t, &p) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (point_minus_point(&p, &cy->point, &v) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (vector_multiply_vector(&v, &cy->norm_vec, &vertical) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (vertical < 0)
		vertical *= -1;
	if (vertical > cy->height)
		*t = -1;
}

void	check_height(t_mini_rt *rt, t_ray *ray, t_cys *cy)
{
	if (rt->calc.t1 >= 0)
		check_height_two(rt, ray, cy, &rt->calc.t1);
	if (rt->calc.t2 >= 0)
		check_height_two(rt, ray, cy, &rt->calc.t2);
}

/*calcualtes collision of raz and rounded wall of a single cylinder*/
int	get_cys_wall_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	int		solutions;

	rt->calc.t1 = -1;
	rt->calc.t2 = -1;
	cy_calculate_quadratic_arguments(rt->calc.quadratic_args, cy, ray, rt);
	solutions = discriminant_check(rt->calc.quadratic_args[0],
			rt->calc.quadratic_args[1], rt->calc.quadratic_args[2], rt);
	if (solutions == 0)
		return (FAILURE);
	quadratic_formula_plus(rt->calc.quadratic_args, &rt->calc.t1, rt);
	if (solutions == 2)
		quadratic_formula_minus(rt->calc.quadratic_args, &rt->calc.t2, rt);
	check_height(rt, ray, cy);
	if (get_positive_min(rt->calc.t1, rt->calc.t2, &rt->calc.t1) == FAILURE)
		return (FAILURE);
	//catch camera on cys wall
	if (rt->calc.t1 == 0)
		clean_exit_rt(rt, C_IN_CY_W);
	//lowest positive is now in rt->calc.t1
	fill_hit(CYLINDER, rt->calc.t1, ray, new);
	return (SUCCESS);
}

// int	get_cys_top_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
// {
// 	//get top center point
// 	t_point center;
// 	t_vector tmp;

// 	if (point_plus_vector(&cy->point, &cy->norm_vec, cy->height / 2, &center) == FAILURE)
// 		clean_exit_rt(rt, CALC);
// 	//d*v
// 	if (vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &rt->calc.t2) == FAILURE)
// 		clean_exit_rt(rt, CALC);
// 	/*if ray is parallel to plane, we have either 0 hits, so return failure. 
// 	or we have ray in plane. but ray in plane in this case means that we found the closest 
// 	collision on the cylinder top on the wall already, so we can ignore this case, right?*/
// 	//check d*v isnt 0
// 	if (rt->calc.t2 == 0)
// 		return (FAILURE);
// 	//fraction upper part
// 	if (point_minus_point(&center, &ray->c, &tmp) == FAILURE)
// 		clean_exit_rt(rt, CALC);
// 	if (vector_multiply_vector(&tmp, &cy->norm_vec, &rt->calc.t1) == FAILURE)
// 		clean_exit_rt(rt, CALC);

// 	//t = ((c-o) * v) / (d*v) 
// 	rt->calc.t1 = rt->calc.t1 / rt->calc.t2
// 	//fill the hit with it.
// 	return (SUCCESS);
// }

/*saves the closest collision with a single cylinder in got*/
int	get_hit_cys(t_mini_rt *rt, t_cys *cy, t_ray *ray)
{
	t_hit	new;

	init_hit(&new);
	if (get_cys_wall_collision(rt, cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);
	reset_calc(&rt->calc);
	/*if (get_cys_top_collision(cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);
	reset_calc(&rt->calc);
	if (get_cys_bottom_collision(cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);*/
	reset_calc(&rt->calc);
	
		//now got should contain the cloesst collision within the cylinder
	if (rt->calc.got.distance == 0)
		clean_exit_rt(rt, C_IN_CY);
	return (SUCCESS);
}

/*delegates collision check for all cylinders.
saves closest visible one  in rt->calc->min*/
void	check_cys_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_cys	*cy;

	cy = cf->cy;
	while (cy)
	{
		if (get_hit_cys(rt, cy, ray) == SUCCESS)
			update_min(&rt->calc.min, &rt->calc.got);
		cy = cy->next;
	}
}
