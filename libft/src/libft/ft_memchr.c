/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:21:47 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/23 11:22:29 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	pos;
	unsigned char	*a;

	a = (unsigned char *)s;
	pos = 0;
	c = (unsigned char)c;
	while (pos < n)
	{
		if (a[pos] == c)
			return (a + pos);
		pos ++;
	}
	return (0);
}
