#include "../inc/miniRT.h"

/* Getting a pointer to the last cylinder. */
t_spher	*get_ptr_lst_sph(t_spher **sphere)
{
	t_spher	*new;

	new = NULL;
	new = ft_lstnew_sph(new);
	if (new == NULL)
	{
		display_error(MEMORY);
		return (NULL);
	}
	ft_lstadd_back_sph(sphere, new);
	return (new);
}

t_spher	*ft_lstnew_sph(t_spher *new)
{
	new = (t_spher *)malloc(sizeof(t_spher));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

/* Adds the given element ‘new’ to the end of the linked list 
pointed to by ‘lst’. If ‘lst’ is an empty list, ‘new’ becomes 
the first element. */
void	ft_lstadd_back_sph(t_spher **lst, t_spher *new)
{
	t_spher	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp)
	{
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	temp->next = new;
}
