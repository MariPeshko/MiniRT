/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sphere_hits.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:43:40 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/14 13:37:40 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*calcualtes collision of raz and rounded wall of a single cylinder*/
int	sp_calculate_quadratic_arguments(double *args, t_spher *sp, t_ray *ray, t_mini_rt *rt)
{
	t_vector	v;

	//A = ray direction vector ^2
	if (vector_multiply_vector(&ray->v_dir, &ray->v_dir, &args[0]) == FAILURE)
		clean_exit_rt(rt, CALC);
	//B = 2 * (Camera-center) * ray direction vector
	if (point_minus_point(&ray->c, &sp->point, &v) == FAILURE)
		clean_exit_rt(rt, CALC);
	if (vector_multiply_vector(&v, &ray->v_dir, &args[1]) == FAILURE)
		clean_exit_rt(rt, CALC);
	args[1] *= 2;
	if (isnan(args[1]) || isinf(args[1]))
		clean_exit_rt(rt, CALC);
	//C = (Camera-center)^2 - radius^2
	if (vector_multiply_vector(&v, &v, &args[2]) == FAILURE)
		clean_exit_rt(rt, CALC);
	args[2] -= (sp->diam/2) * (sp->diam/2);
	if (isnan(args[2]) || isinf(args[2]))
		clean_exit_rt(rt, CALC);
	return (SUCCESS);
}

void	reset_calc(t_col *calc)
{
	calc->t1 = -1;
	calc->t2 = -1;
	calc->quadratic_args[0] = 0;
	calc->quadratic_args[1] = 0;
	calc->quadratic_args[2] = 0;
}

int	block_relevant(t_mini_rt *rt, t_spher *sp)
{
	double	min;
	//printf("t1 t2 %10f   %10f\n", rt->calc.t1, rt->calc.t2);
	if (get_positive_min(rt->calc.t1, rt->calc.t2, &min) == FAILURE)
		return (FAILURE);
	if (fabs(min) < EPSILON && sp->id == rt->coca.sp->id)
		return (FAILURE);
	//printf("min %10f\n", min);
	return (SUCCESS);
}

int	get_hit_sphere(t_mini_rt *rt, t_spher *sp, t_ray *ray)
{
	int		solutions;

	reset_calc(&rt->calc);
	init_hit(&rt->calc.got);
	sp_calculate_quadratic_arguments(rt->calc.quadratic_args, sp, ray, rt);
	solutions = discriminant_check(rt->calc.quadratic_args[0],
			rt->calc.quadratic_args[1], rt->calc.quadratic_args[2], rt);
	if (solutions == 0)
		return (FAILURE);
	quadratic_formula_plus(rt->calc.quadratic_args, &rt->calc.t1, rt);
	if (solutions == 2)
		quadratic_formula_minus(rt->calc.quadratic_args, &rt->calc.t2, rt);
	if (rt->coca.sp != NULL)
		return (block_relevant(rt, sp));
	if (get_positive_min(rt->calc.t1, rt->calc.t2, &rt->calc.t1) == FAILURE)
		return (FAILURE);
	//catch camera in sphere surface
	if (rt->calc.t1 == 0)
		clean_exit_rt(rt, C_IN_SP);
	//lowest positive is now in rt->calc.t1
	fill_hit(SPHERE, &rt->calc, sp->id, &rt->calc.got);
	return (SUCCESS);
}

/*sets min to got, if got is closer than min*/
void update_min_sph(t_hit *min, t_hit *got, t_spher	*sp, t_col *calc)
{
	if (!min || !got)
		return ;
	if (min->distance == -1 && got->distance > 0)
	{
		*min = *got;
		save_color(calc, sp->col);
	}
	else if (got->distance < min->distance)
	{
		*min = *got;
		save_color(calc, sp->col);
	}
}

/*delegates collision check for all cylinders.
saves closest visible one  in rt->calc->min*/
void	check_sphere_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_spher	*sp;
	t_col	*calc;

	calc = &rt->calc;
	sp = cf->sp;
	while (sp)
	{
		if (get_hit_sphere(rt, sp, ray) == SUCCESS)
		{
			//update_min(&rt->calc.min, &rt->calc.got);
			update_min_sph(&calc->min, &calc->got, sp, calc);
		}
		sp = sp->next;
	}
}
