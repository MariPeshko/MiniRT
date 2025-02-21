/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:29:04 by sgramsch          #+#    #+#             */
/*   Updated: 2025/02/21 17:14:38 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/libft_gnl_printf.h"
# include "../../inc/libft.h"
# include "../../inc/get_next_line.h"

int	end_of_line(char *safetycopy)
{
	int	pos;

	pos = 0;
	if (!safetycopy)
		return (-1);
	while (safetycopy[pos])
	{
		if (safetycopy[pos] == '\n')
			return (pos);
		pos ++;
	}
	return (-1);
}

size_t	gnl_strlen(char *s)
{
	size_t	pos;

	pos = 0;
	while (s[pos])
		pos ++;
	return (pos);
}

char	*gnl_free(char *a)
{
	if (a)
	{
		free(a);
		a = NULL;
	}
	return (NULL);
}
