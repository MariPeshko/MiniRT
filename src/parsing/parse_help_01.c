/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:33:09 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 20:03:44 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*gets an int from line*/
int	get_int(char *line, int *pos, int *dest)
{
	int	nbr;
	int	neg;

	neg = 1;
	nbr = 0;
	skip_whitespace(line, pos);
	if (line[*pos] == '-')
	{
		(*pos)++;
		neg = -1;
	}
	if (!ft_isdigit(line[*pos]))
		return (display_error(WRONG_CHAR));
	while (ft_isdigit(line[*pos]))
	{
		nbr = nbr * 10 + line[*pos] - '0';
		(*pos)++;
	}
	if (!is_whitespace(line[*pos]))
		return (display_error(WRONG_CHAR));
	*dest = nbr * neg;
	return (SUCCESS);
}

/*checks if the values in the triplet are in scope of [min, max]*/
int	triplet_in_scope(double *triplet, double min, double max)
{
	if (triplet[0] < min || triplet[0] > max)
		return (display_error(NV_SCOPE));
	if (triplet[1] < min || triplet[1] > max)
		return (display_error(NV_SCOPE));
	if (triplet[2] < min || triplet[2] > max)
		return (display_error(NV_SCOPE));
	if (triplet[0] == 0 && triplet[1] == 0 && triplet [2] == 0)
		return (display_error(NV_ZEROS));
	return (SUCCESS);
}
