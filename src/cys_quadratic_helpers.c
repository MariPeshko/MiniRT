#include "../inc/miniRT.h"

int	get_A_cylinder(t_vector *d_vertical, double *A)
{
	double tmp;

	vector_multiply_vector(d_vertical, d_vertical, &tmp);
	*A = tmp;
	return (SUCCESS);
}

int	get_B_cylinder(t_vector *OC_vertical, t_vector *d_vertical, double *B)
{
	vector_multiply_vector(OC_vertical, d_vertical, B);
	*B *= 2;
	//printf("B = %10f\n", *B);
	return (SUCCESS);
}

int	get_C_cylinder(t_vector *OC_vertical, double radius, double *C)
{
	vector_multiply_vector(OC_vertical, OC_vertical, C);
	*C -= radius * radius;
	//printf("C = %10f\n", *C);
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

int	calculate_quadratic_arguments(double *args, t_cys *cy, t_ray *ray)
{
	t_vector d_vertical;
	t_vector OC_vertical;

	get_vertical_parts(&d_vertical, &OC_vertical, cy, ray);
	get_A_cylinder(&d_vertical, &args[0]);
	get_B_cylinder(&OC_vertical, &d_vertical, &args[1]);
	get_C_cylinder(&OC_vertical, cy->diam / 2, &args[2]);
	return (SUCCESS);
}