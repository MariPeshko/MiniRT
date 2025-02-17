/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:30:46 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/27 15:07:13 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 1;
	while (lst)
	{
		if (lst->next == NULL)
			return (size);
		lst = lst->next;
		size ++;
	}
	return (0);
}
