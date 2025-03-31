#include "../inc/miniRT.h"

/*calcualtes collision of raz and rounded wall of a single cylinder*/
int	get_cys_wall_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray)
{
	double args[3];
	int solutions;
	double	t1;
	double	t2;

	t1 = -1;
	t2 = -1;
	if (rt)//only for unused arguemnt error rn
		calculate_quadratic_arguments(args, cy, ray);
	solutions = discriminant_check(args[0], args[1], args[2]);
	//printf("Solutions: %d\n", solutions);
	if (solutions == 0)
		return (FAILURE);
	//if solutions == ^1; calcualte quadratic_plus,
	quadratic_formula_plus(args, &t1);
	//if solutions == 2; calculate quadratic minus;
	if (solutions == 2)
		quadratic_formula_minus(args, &t2);
	// check relevance of solution, and return if no relevant one
	if (get_positive_min(t1, t2, &t1) == FAILURE)
		return (FAILURE);
	//lowest positive is now in t1
	fill_hit(CYLINDER, t1, ray, new);
	return (SUCCESS);
}

/*saves the closest collision with a single cylinder in got*/
int	get_hit_cys(t_mini_rt *rt, t_cys *cy, t_ray *ray)
{
	t_hit new;
	if (get_cys_wall_collision(rt, cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);
	/*if (get_cys_top_collision(cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);
	if (get_cys_bottom_collision(cy, &new, ray) == SUCCESS)
		update_min(&rt->calc.got, &new);*/
	//now got should contain the cloesst collision within the cylinder
	return (SUCCESS);
}

/*delegates collision check for all cylinders.
saves closest visible one  in rt->calc->min*/
void	check_cys_hit(t_config *cf, t_mini_rt *rt, t_ray *ray)
{
	t_cys *cy;

	cy = cf->cy;
	while (cy)
	{
		if (get_hit_cys(rt, cy, ray) == SUCCESS)
			update_min(&rt->calc.min, &rt->calc.got);
		cy = cy->next;
	}
}
