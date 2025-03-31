#include "../inc/miniRT.h"

int	get_cys_wall_collision(t_cys *cy, t_hit *new, t_ray *ray)
{
	double args[3];
	int solutions;

	calculate_quadratic_arguments(args, cy, ray);
	solutions = discriminant_check(args[0], args[1], args[2]);
	if (new)
		printf("Solutions: %d\n", solutions);
	if (solutions == 0)
		return (FAILURE);
	//if solutions == ^1; calcualte quadratic_plus,
	// check relevance of solution, and return
	//if solutions == 2; calculate quadratic plus and minus; get positive min, 
	//check relevance of solution, and return 
	//return failure if no relevant hits. 
	return (SUCCESS);
}

int	get_hit_cys(t_cys *cy, t_hit *got, t_ray *ray)
{
	t_hit new;
	if (get_cys_wall_collision(cy, &new, ray) == SUCCESS)
		update_min(got, &new);
	/*if (get_cys_top_collision(cy, &new, ray) == SUCCESS)
		update_min(got, &new);
	if (get_cys_bottom_collision(cy, &new, ray) == SUCCESS)
		update_min(got, &new);*/
	//now got should contain the cloesst collision within the cylinder
	return (SUCCESS);
}

void	check_cys_hit(t_config *cf, t_col *calc, t_ray *ray)
{
	t_cys *cy;
	
	cy = cf->cy;
	while (cy)
	{
		if (get_hit_cys(cy, &calc->got, ray) == SUCCESS)
			update_min(&calc->min, &calc->got);
		cy = cy->next;
	}
}