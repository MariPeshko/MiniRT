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
	if (get_positive_min(rt->calc.t1, rt->calc.t2, &rt->calc.t1) == FAILURE)
		return (FAILURE);
	//lowest positive is now in rt->calc.t1
	fill_hit(SPHERE, rt->calc.t1, ray, &rt->calc.got);
	return (SUCCESS);
}

/*delegates collision check for all cylinders.
saves closest visible one  in rt->calc->min*/
void	check_sphere_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_spher	*sp;

	sp = cf->sp;
	while (sp)
	{
		if (get_hit_sphere(rt, sp, ray) == SUCCESS)
			update_min(&rt->calc.min, &rt->calc.got);
		sp = sp->next;
	}
}
