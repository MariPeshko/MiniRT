/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:13:20 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 12:13:23 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	d_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	d_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
