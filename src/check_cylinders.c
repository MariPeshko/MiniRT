#include "../inc/miniRT.h"
int	point_minus_point(t_point *a, t_point *b, t_vector *result)
{
	if (!a || !b || !result)
		return (FAILURE);
	result->x = a->x - b->x;
	result->y = a->y - b->y;
	result->z = a->z - b->z;
	return (SUCCESS);
}

int	get_A_cylinder(t_vector *d_vertical, double *A)//(t_cys *cy, t_ray *ray, double *A)
{
	/*A = ray direction vertical part ^2*/
	/*ray direction vertical part = d - (d*v)*v */
	double tmp;
	//t_vector v_tmp;
	/*vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &tmp);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&ray->v_dir, &v_tmp, &v_tmp);*/
	//vector_multiply_vector(&v_tmp, &v_tmp, &tmp);
	vector_multiply_vector(d_vertical, d_vertical, &tmp);
	printf("A = %10f \n", tmp);
	*A = tmp;
	return (SUCCESS);
}

int	get_B_cylinder(t_vector *OC_vertical, t_vector *d_vertical, double *B)
{
	vector_multiply_vector(OC_vertical, d_vertical, B);
	*B *= 2;
	printf("B = %10f\n", *B);
	return (SUCCESS);
}

int	get_vertical_parts(t_vector *d_vertical, t_vector *OC_vertical, t_cys *cy, t_ray *ray)
{
	double tmp;
	t_vector v_tmp;
	t_vector CO;
	//d_vertical
	vector_multiply_vector(&ray->v_dir, &cy->norm_vec, &tmp);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&ray->v_dir, &v_tmp, &v_tmp);
	d_vertical->x = v_tmp.x;
	d_vertical->y = v_tmp.y;
	d_vertical->z = v_tmp.z;
	//OC_vertical
	point_minus_point(&ray->c, &cy->point, &CO);
	vector_multiply_vector(&CO, &cy->norm_vec, &tmp);
	scalar_multiply_vector(tmp, &cy->norm_vec, &v_tmp);
	subtract_vectors(&CO, &v_tmp, &v_tmp);
	OC_vertical->x = v_tmp.x;
	OC_vertical->y = v_tmp.y;
	OC_vertical->z = v_tmp.z;
	return (SUCCESS);
}

int	get_C_cylinder(t_vector *OC_vertical, double radius, double *C)
{
	vector_multiply_vector(OC_vertical, OC_vertical, C);
	*C -= radius * radius;
	printf("C = %10f\n", *C);
	return (SUCCESS);
}

int	get_cys_wall_collision(t_cys *cy, t_hit *got, t_ray *ray)
{
	double A;
	double B;
	double C;
	t_vector d_vertical;
	t_vector OC_vertical;
	get_vertical_parts(&d_vertical, &OC_vertical, cy, ray);
	get_A_cylinder(&d_vertical, &A);//(cy, ray, &A);
	get_B_cylinder(&OC_vertical, &d_vertical, &B);
	get_C_cylinder(&OC_vertical, cy->diam / 2, &C);
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