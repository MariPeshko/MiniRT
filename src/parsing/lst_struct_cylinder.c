/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_struct_cylinder.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:31:57 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:32:14 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/* Getting a pointer to the last cylinder. */
t_cys	*get_ptr_lst_cyl(t_cys **cylinder)
{
	t_cys	*new;

	new = NULL;
	new = ft_lstnew_cy(new);
	if (new == NULL)
	{
		display_error(MEMORY);
		return (NULL);
	}
	ft_lstadd_back_cy(cylinder, new);
	return (new);
}

/* This function creates and returns a new node for
the linked list. */
t_cys	*ft_lstnew_cy(t_cys *new)
{
	new = (t_cys *)malloc(sizeof(t_cys));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/* Adds the given element ‘new’ to the end of the linked list 
pointed to by ‘lst’. If ‘lst’ is an empty list, ‘new’ becomes 
the first element. */
void	ft_lstadd_back_cy(t_cys **lst, t_cys *new)
{
	t_cys	*temp;
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

t_cys	*ft_lstlast_cy(t_cys *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
