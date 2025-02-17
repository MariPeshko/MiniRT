/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:14:15 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/29 13:58:03 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					pos;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	pos = n -1;
	if (!dest && !src)
		return (NULL);
	if (d < s || d > (s + n))
		return (ft_memcpy(dest, src, n));
	while (pos >= 0)
	{
		d[pos] = s[pos];
		pos --;
	}
	return (dest);
}
