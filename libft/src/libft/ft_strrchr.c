/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:34:25 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/21 11:41:12 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	pos;

	pos = 0;
	while (c > 127)
		c = c - 128;
	while (s[pos] != '\0')
		pos ++;
	while (pos >= 0)
	{
		if (s[pos] == c)
			return ((char *)s + pos);
		pos --;
	}
	return (0);
}
