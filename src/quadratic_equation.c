#include "../inc/miniRT.h"

int	quadratic_formula_plus(double *args, double *solution)
{
	double	discriminant;
	double	res;

	discriminant = args[1] * args[1] - 4 * args[0]*args[2];
	res = -1 * args[1] + sqrt(discriminant);
	res /= 2*args[0];
	*solution = res;
	return (SUCCESS);
}

int	quadratic_formula_minus(double *args, double *solution)
{
	double	discriminant;
	double	res;

	discriminant = args[1] * args[1] - 4 * args[0]*args[2];
	res = -1 * args[1] - sqrt(discriminant);
	res /= 2*args[0];
	*solution = res;
	return (SUCCESS);
}

int	discriminant_check(double A, double B, double C)
{
	/*discriminant = sqrt(B^2 - 4AC)*/
	double	discriminant;
	
	discriminant = B * B - 4 * A*C;
	if (discriminant < 0)
		return (0);
	if (discriminant == 0)
		return (1);
	return (2);
}

/*takes two doubles and a pointer to one. 
assigns the lowest positive vlaue of a and b to c.
returns failure if a and b are negative.*/
int get_positive_min(double a, double b, double *c)
{
	if (c == NULL)
		return (FAILURE); // Handle null pointer case
	if (a < 0 && b < 0)
		return (FAILURE);
	if (a < 0 || b < 0)
	{
		if (a > b)
			*c = a;
		else
			*c = b;
		return (SUCCESS);
	}
	if (a < b)
		*c = a;
	else
		*c = b;
	return (SUCCESS);
}
