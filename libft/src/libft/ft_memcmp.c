/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:22:25 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 10:22:25 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			m;
	unsigned char	*fi;
	unsigned char	*se;

	fi = (unsigned char *)s1;
	se = (unsigned char *)s2;
	m = 0;
	while (m < n)
	{
		if (*(fi + m) != *(se + m))
			return (*(fi + m) - *(se + m));
		m ++;
	}
	return (0);
}
