/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:29:03 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/21 15:16:15 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	long unsigned int	pos;
	size_t				dend;
	size_t				slen;

	pos = 0;
	dend = ft_strlen(dst);
	slen = ft_strlen(src);
	while ((dend + pos) < (size -1) && size != 0 && pos < slen)
	{
		dst[dend + pos] = src[pos];
		if (src[pos] == '\0')
			break ;
		pos ++;
	}
	if (dend + pos < size)
	{
		dst[dend + pos] = '\0';
	}
	if (dend > size)
		return (slen + size);
	return (slen + dend);
}
