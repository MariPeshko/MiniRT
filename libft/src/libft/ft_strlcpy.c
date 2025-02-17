/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:29:23 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 12:47:20 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	long unsigned int	pos;
	long unsigned int	ret;

	pos = 0;
	ret = 0;
	while (pos < (size -1) && src[pos] != '\0' && size != 0)
	{
		dst[pos] = src[pos];
		pos ++;
	}
	if (size != 0)
		dst[pos] = '\0';
	while (src[ret])
		ret ++;
	return (ret);
}
