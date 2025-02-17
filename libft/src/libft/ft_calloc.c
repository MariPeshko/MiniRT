/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:22:05 by sgramsch          #+#    #+#             */
/*   Updated: 2023/11/22 14:50:59 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb > 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
