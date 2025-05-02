/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:33:09 by sgramsch          #+#    #+#             */
/*   Updated: 2025/05/02 13:35:00 by sgramsch         ###   ########.fr       */
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

/*function that extracts the next float in from a string.
line: input line starting with Identifier
*pos: position in string
*dest: where to save the extracted float upon success*/
/*issue: after the whole number part, check for . , or whitespace.
means get fractional part
, means finished number and another follows
whitespace means finfished number and last number*/
int	get_float(char *line, int *pos, float *dest)
{
	float	full_nbr;
	float	fractional;
	float	divisor;
	float	neg;

	full_nbr = 0;
	fractional = 0;
	divisor = 10.0;
	neg = 1;
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
		full_nbr = full_nbr * 10 + line[*pos] - '0';
		(*pos)++;
	}
	if (line[*pos] == ',' || is_whitespace(line[*pos]))
	{
		*dest = full_nbr * neg;
		return (SUCCESS);
	}
	if (line[*pos] != '.')
		return (display_error(WRONG_CHAR));
	(*pos)++;
	if (!ft_isdigit(line[*pos]))
		return (display_error(WRONG_CHAR));
	while (ft_isdigit(line[*pos]))
	{
		fractional = fractional + ((line[*pos] - '0') / divisor);
		divisor *= 10;
		(*pos)++;
	}
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
