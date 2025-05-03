/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:02:40 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:02:41 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
msg: Macro defined Error message
prints Error message given as Argument
*/
int	display_error(char *msg)
{
	printf(RED "Error\n%s" RESET, msg);
	printf("\n");
	return (FAILURE);
}

void	clean_exit(t_config *cf, char *er_msg)
{
	cleanup_cf(cf);
	if (er_msg)
		display_error(er_msg);
	exit(FAILURE);
}

void	clean_exit_rt(t_mini_rt *rt, char *er_msg, char *place)
{
	cleanup_cf(&rt->cf);
	cleanup_mlx(rt);
	if (er_msg)
		display_error(er_msg);
	if (place)
		printf(RED "%s\n" RESET, place);
	exit(FAILURE);
}
