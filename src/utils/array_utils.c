/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:01:50 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:01:51 by sgramsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*returns the length of the two dimensional character array map*/
int	map_len(char **map)
{
	int	pos;

	pos = 0;
	while (map && map[pos])
		pos++;
	return (pos);
}
