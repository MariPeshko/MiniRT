#include "../inc/miniRT.h"

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