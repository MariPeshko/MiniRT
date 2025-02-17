/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:12:28 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/29 13:56:23 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	long unsigned int	pos;

	pos = 0;
	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	while (pos < n)
	{
		d[pos] = s[pos];
		pos++;
	}
	return (dest);
}
