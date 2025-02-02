/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:43:07 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:09:01 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*substr;
	long unsigned int	pos;

	pos = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	while (s[start + pos] && pos < len)
		pos ++;
	len = pos;
	substr = (char *) malloc((1 + len) * sizeof (char));
	if (substr == 0)
		return (0);
	pos = 0;
	while (pos < len && s[start + pos] != '\0')
	{
		substr[pos] = s[start + pos];
		pos ++;
	}
	substr[pos] = '\0';
	return (substr);
}
