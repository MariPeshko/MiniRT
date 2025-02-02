/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:52:23 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:52:23 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	pos;
	char			*a;

	a = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (a == 0)
		return (0);
	pos = 0;
	while (s[pos] != 0)
	{
		a[pos] = (*f)(pos, s[pos]);
		pos ++;
	}
	a[pos] = 0;
	return (a);
}
