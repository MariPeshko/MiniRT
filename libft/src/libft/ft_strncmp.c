/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:22:47 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/23 11:10:50 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	pos;
	int					a;

	pos = 0;
	while ((s1[pos] || s2[pos]) && pos < n)
	{
		if (s1[pos] != s2[pos])
		{
			a = (unsigned char)s1[pos] - (unsigned char)s2[pos];
			return (a);
		}
		pos ++;
	}
	return (0);
}
