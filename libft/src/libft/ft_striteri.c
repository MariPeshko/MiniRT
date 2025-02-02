/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:51:22 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/20 15:51:22 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	pos;

	pos = 0;
	while (s[pos] != 0)
	{
		(*f)(pos, &s[pos]);
		pos ++;
	}
}
