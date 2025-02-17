/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:55:31 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/15 13:05:07 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int				pos;
	unsigned char	*a;

	a = s;
	pos = n - 1;
	while (pos >= 0)
	{
		a[pos] = c;
		pos --;
	}
	return (s);
}
