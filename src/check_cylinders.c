#include "../inc/miniRT.h"

int	get_A(t_cys *cy, t_ray *ray)
{
	/*A = ray direction vertical part ^2*/
	/*ray direction vertical part = d - (d*v)*v */
	double tmp;
	t_vector v_tmp;
	vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &tmp);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&ray->v_dir, &v_tmp, &v_tmp);
	vector_multiply_vector(&v_tmp, &v_tmp, &tmp);
	printf("A = %10f \n", tmp);
	return (SUCCESS);
}

int	get_cys_wall_collision(t_cys *cy, t_hit *got, t_ray *ray)
{
	/*double A;
	double B;
	double C;*/

	get_A(cy, ray);
	if (cy && got && ray)
		return (SUCCESS);
	return (SUCCESS);
}

int	get_hit_cys(t_cys *cy, t_hit *got, t_ray *ray)
{

	if (cy && got && ray)
		get_cys_wall_collision(cy, got, ray);
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