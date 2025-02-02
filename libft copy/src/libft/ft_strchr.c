/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:11:08 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/23 11:17:49 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	c = (unsigned char)c;
	while (s[pos] != '\0')
	{
		if (s[pos] == c)
			return ((char *)s + pos);
		pos ++;
	}
	if (s[pos] == c)
		return ((char *)s + pos);
	return (0);
}
