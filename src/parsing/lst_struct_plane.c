/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_struct_plane.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:32:18 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:32:23 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/* Getting a pointer to the last cylinder. */
t_plane	*get_ptr_lst_pl(t_plane **plane)
{
	t_plane	*new;

	new = NULL;
	new = ft_lstnew_pl(new);
	if (new == NULL)
	{
		display_error(MEMORY);
		return (NULL);
	}
	ft_lstadd_back_pl(plane, new);
	return (new);
}

t_plane	*ft_lstnew_pl(t_plane *new)
{
	new = (t_plane *)malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/* Adds the given element ‘new’ to the end of the linked list 
pointed to by ‘lst’. If ‘lst’ is an empty list, ‘new’ becomes 
the first element. */
void	ft_lstadd_back_pl(t_plane **lst, t_plane *new)
{
	t_plane	*temp;
	int		id;

	id = 1;
	temp = *lst;
	if (*lst == NULL)
	{
		new->id = id;
		*lst = new;
		return ;
	}
	while (temp)
	{
		id++;
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	new->id = id;
	temp->next = new;
}
