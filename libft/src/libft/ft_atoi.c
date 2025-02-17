/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:26:22 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 16:39:58 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_isspace(char a)
{
	if (a == ' ' || (a >= 9 && a <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	pos;
	int	res;
	int	neg;

	pos = 0;
	res = 0;
	neg = 1;
	while (ft_isspace(nptr[pos]))
		pos ++;
	if (nptr[pos] == '-' || nptr[pos] == '+')
	{
		if (nptr[pos] == '-')
			neg = -1;
		pos ++;
	}
	while (ft_isdigit(nptr[pos]))
	{
		res = res * 10 + (nptr[pos] - '0');
		pos ++;
	}
	return (res * neg);
}
