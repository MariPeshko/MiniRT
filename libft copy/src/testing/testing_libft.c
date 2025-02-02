/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_libft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:14:35 by sgramsch          #+#    #+#             */
/*   Updated: 2024/04/07 11:57:43 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../../inc/libft_gnl_printf.h"
#include <stdio.h>
#include <stdlib.h>

// int	main(void)
// {
// 	//printf("%s\n", ft_strtrim("abcdba", "acb"));
// 	ft_split("lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse", ' ');
// 	return (0);
// }


int main(void)
{
	int fd = open("try.txt", O_RDONLY);
	printf("\nfd = %d\n", fd);
	char	*a;
	a = get_next_line(fd);
	while (a != NULL)
	{
		printf("result:%s", a);
		free(a); //this missing causes the leaks
		a = get_next_line(fd);
	}
	free(a);
	close(fd);
	printf("finished");
	return (0);
}
