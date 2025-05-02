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
