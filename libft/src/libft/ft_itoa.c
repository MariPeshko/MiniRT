/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:32:47 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 10:32:47 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	find_base(long n)
{
	int	i;
	int	tens;

	i = 1;
	tens = 1;
	if (n == 0)
		return (1);
	while (i < 10)
	{
		tens = tens * 10;
		if (n < tens)
			break ;
		i ++;
	}
	return (i);
}

static void	copy(char *str, long nbr)
{
	if (nbr / 10 > 0)
		copy(str - 1, nbr / 10);
	*str = (nbr % 10) + '0';
	return ;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		space;
	int		neg;
	long	nbr;

	neg = 0;
	nbr = n;
	if (n < 0)
	{
		neg = 1;
		nbr = nbr * -1;
	}
	space = find_base(nbr);
	str = (char *)malloc((1 + neg + space) * sizeof(char));
	if (!str)
		return (NULL);
	str[space + neg] = '\0';
	copy(str + space - 1 + neg, nbr);
	if (neg == 1)
		str[0] = '-';
	return (str);
}
