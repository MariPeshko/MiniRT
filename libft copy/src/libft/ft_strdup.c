/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:24:06 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:19:37 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*a;

	a = (char *)malloc ((1 + ft_strlen(s)) * sizeof(char));
	if (a == 0)
		return (0);
	ft_strlcpy(a, s, ft_strlen(s) + 1);
	return (a);
}
