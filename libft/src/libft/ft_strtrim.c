/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:56:14 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:56:14 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	ft_remove(char a, char const *set)
{
	int	pos;

	pos = 0;
	while (set[pos])
	{
		if (set[pos] == a)
			return (1);
		pos ++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		pos;
	int		start;
	int		end;
	char	*str;

	start = 0;
	while (s1[start] && ft_remove(s1[start], set))
		start ++;
	end = ft_strlen(s1) -1;
	while (s1[end] && ft_remove(s1[end], set))
		end --;
	if (end - start < 0)
		return (ft_strdup(""));
	str = (char *) malloc ((2 + end - start) * sizeof (char));
	if (str == 0)
		return (NULL);
	pos = 0;
	while (start + pos <= end)
	{
		str[pos] = s1[start + pos];
		pos ++;
	}
	str[pos] = 0;
	return (str);
}
