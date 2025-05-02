/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic_equation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:25:24 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:54:45 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	quadratic_formula_plus(double *args, double *solution, t_mini_rt *rt)
{
	double	discriminant;
	double	res;

	discriminant = args[1] * args[1] - 4 * args[0] * args[2];
	if (isnan(discriminant) || isinf(discriminant))
		clean_exit_rt(rt, CALC_CYL_DIS, NULL);
	res = -1 * args[1] + sqrt(discriminant);
	res /= 2 * args[0];
	if (isnan(res) || isinf(res))
		clean_exit_rt(rt, CALC_CYL_QFP, NULL);
	*solution = res;
	return (SUCCESS);
}

int	quadratic_formula_minus(double *args, double *solution, t_mini_rt *rt)
{
	double	discriminant;
	double	res;

	discriminant = args[1] * args[1] - 4 * args[0]*args[2];
	if (isnan(discriminant) || isinf(discriminant))
		clean_exit_rt(rt, CALC, NULL);
	res = -1 * args[1] - sqrt(discriminant);
	res /= 2*args[0];
	if (isnan(res) || isinf(res))
		clean_exit_rt(rt, CALC, NULL);
	*solution = res;
	return (SUCCESS);
}

int	discriminant_check(double A, double B, double C, t_mini_rt *rt)
{
	double	discriminant;

	discriminant = (B * B) - (4 * A * C);
	if (isnan(discriminant) || isinf(discriminant))
		clean_exit_rt(rt, CALC_CYL_DIS, NULL);
	if (discriminant < 0)
		return (0);
	if (A == 0)
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
		return (FAILURE);
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
