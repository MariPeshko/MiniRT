/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:46:08 by mpeshko           #+#    #+#             */
/*   Updated: 2025/02/28 15:47:14 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	assign_rgb(t_color *in_struct, t_color result_rgb)
{
	in_struct->r = result_rgb.r;
	in_struct->g = result_rgb.g;
	in_struct->b = result_rgb.b;
}

// 0 - r, 1 - g, 2 - b
static void	add_color(t_color *color, int identifier, int value)
{
	if (identifier == 0)
		color->r = value;
	else if (identifier == 1)
		color->g = value;
	else if (identifier == 2)
		color->b = value;
}

static int	is_positive_digit(const char c)
{
	if (!ft_isdigit(c))
	{
		if (c == '-')
			return (display_error(RGB_NEG));
		else
			return (display_error(RGB_WRONG_CHAR));
	}
	else
		return (SUCCESS);
}

/*
line: input line starting with an Identifier
*pos: position at which we expect the start of RGB values
function checks if the next set of values starting
line[*pos] is a valid RGB triplet
*/
int	get_rgb(char *line, int *pos, t_color *result_rgb)
{
	int	value;
	int	i;

	i = 0;
	skip_whitespace(line, pos);
	while (i < 3)
	{
		value = 0;
		if (is_positive_digit(line[*pos]) == FAILURE)
			return (FAILURE);
		while (ft_isdigit(line[*pos]))
		{
			value = value * 10 + line[*pos] - '0';
			if (value > 255)
				return (display_error(RGB_SCOPE));
			(*pos)++;
		}
		if (i < 2 && line[*pos] != ',')
			return (display_error(RGB_WRONG_CHAR));
		add_color(result_rgb, i, value);
		(*pos)++;
		i++;
	}
	return (SUCCESS);
}
