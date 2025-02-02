/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:44:05 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/17 13:22:06 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	long unsigned int	pos;
	long unsigned int	pos2;

	pos = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[pos] != '\0' && pos < len)
	{
		pos2 = 0;
		while (big[pos + pos2] == little[pos2] && (pos + pos2) < len)
		{
			if (little[pos2 +1] == '\0')
				return (&((char *)big)[pos]);
			pos2 ++;
		}
		pos ++;
	}
	return (0);
}
