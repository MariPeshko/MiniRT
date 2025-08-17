/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calc_bon.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:53:47 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 18:32:14 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	vector_length_light(t_vector *v, t_mini_rt *rt)
{
	double	length;

	length = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (length < EPSILON)
	{
		printf(GREEN "Message: " RESET);
		printf("The light spot is on the object.\n");
	}
	if (isinf(length))
	{
		clean_exit_rt(rt, CALC, V_L_ISINF);
	}
	if (isnan(length))
	{
		clean_exit_rt(rt, CALC, V_L_ISNAN);
	}
	return (length);
}
