/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:51:34 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:51:34 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		pos;
	int		pos2;
	char	*a;

	pos = 0;
	pos2 = 0;
	a = (char *)malloc((1 + ft_strlen(s1) + ft_strlen(s2)) * sizeof(char));
	if (a == 0)
		return (0);
	while (s1[pos])
	{
		a[pos] = s1[pos];
		pos ++;
	}
	while (s2[pos2])
	{
		a[pos] = s2[pos2];
		pos ++;
		pos2 ++;
	}
	a[pos] = 0;
	return (a);
}
