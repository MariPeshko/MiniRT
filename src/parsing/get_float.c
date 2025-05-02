/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_float.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:03:13 by mpeshko           #+#    #+#             */
/*   Updated: 2025/05/02 20:07:28 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	get_f_before_dot(int *pos, char *line, float *neg, float *full_nbr)
{
	skip_whitespace(line, pos);
	if (line[*pos] == '-')
	{
		(*pos)++;
		*neg = -1;
	}
	if (!ft_isdigit(line[*pos]))
		return (display_error(WRONG_CHAR));
	while (ft_isdigit(line[*pos]))
	{
		*full_nbr = *full_nbr * 10 + line[*pos] - '0';
		(*pos)++;
	}
	return (SUCCESS);
}

static int	get_f_after_dot(int *pos, char *line, float	*fractional)
{
	float	divisor;

	divisor = 10.0;
	(*pos)++;
	if (!ft_isdigit(line[*pos]))
		return (display_error(WRONG_CHAR));
	while (ft_isdigit(line[*pos]))
	{
		*fractional = *fractional + ((line[*pos] - '0') / divisor);
		divisor *= 10;
		(*pos)++;
	}
	return (SUCCESS);
}

/* function that extracts the next float in from a string.
line: input line starting with Identifier
*pos: position in string
*dest: where to save the extracted float upon success */
int	get_float(char *line, int *pos, float *dest)
{
	float	full_nbr;
	float	fractional;
	float	neg;

	full_nbr = 0;
	fractional = 0;
	neg = 1;
	if (get_f_before_dot(pos, line, &neg, &full_nbr) == FAILURE)
		return (FAILURE);
	if (line[*pos] == ',' || is_whitespace(line[*pos]))
	{
		*dest = full_nbr * neg;
		return (SUCCESS);
	}
	if (line[*pos] != '.')
		return (display_error(WRONG_CHAR));
	get_f_after_dot(pos, line, &fractional);
	if (!(line[*pos] == ',' || is_whitespace(line[*pos])))
		return (display_error(WRONG_CHAR));
	*dest = (full_nbr + fractional) * neg;
	return (SUCCESS);
}

/* Gets the next three floats from line, starting at pos and saves 
them in triplet */
int	get_three_floats(char *line, int *pos, double triplet[3])
{
	int		i;
	float	tmp;

	i = 0;
	while (i < 3)
	{
		tmp = 0;
		if (get_float(line, pos, &tmp) == FAILURE)
			return (FAILURE);
		if (i < 2)
		{
			if (line[*pos] != ',')
				return (display_error(WRONG_CHAR));
		}
		triplet[i] = tmp;
		if (i == 2)
			break ;
		(*pos)++;
		i++;
	}
	if (!is_whitespace(line[*pos]))
		return (FAILURE);
	return (SUCCESS);
}
