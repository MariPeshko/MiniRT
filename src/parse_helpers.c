#include "../inc/miniRT.h"

void	assign_rgb(t_color *in_struct, t_color result_rgb)
{
	in_struct->r = result_rgb.r;
	in_struct->g = result_rgb.g;
	in_struct->b = result_rgb.b;
}

/*gets an int from line*/
int	get_int(char *line, int *pos, int *dest)
{
	int	nbr = 0;
	int	neg = 1;
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
int	triplet_in_scope(float *triplet, float min, float max)
{
	if (triplet[0] < min || triplet[0] > max)
		return (FAILURE);
	if (triplet[1] < min || triplet[1] > max)
		return (FAILURE);
	if (triplet[2] < min || triplet[2] > max)
		return (FAILURE);
	return (SUCCESS);
}

/*function that extracts the next float in from a string.
line: input line starting with Identifier
*pos: position in string
*dest: where to save the extracted float upon success*/
/*issue: after the whole number part, check for . , or whitespace. . means get fractional part
, means finished number and another follows
whitespace means finfished number and last number*/
int	get_float(char *line, int *pos, float *dest)
{
	float	full_nbr = 0;
	float	fractional = 0;
	float	divisor = 10.0;// Used to handle the fractional part
	float	neg = 1;
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
		//printf("FLOAT: %f\n", *dest);
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
	//printf("FLOAT: %f\n", *dest);
	return (SUCCESS);
}

/* Gets the next three floats from line, starting at pos and saves 
them in triplet */
int	get_three_floats(char *line, int *pos, float triplet[3])
{
	int i = 0;
	while (i < 3)
	{
		float	tmp = 0;
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

// 0 - r, 1 - g, 2 - b
static void add_color(t_color *color, int identifier, int value)
{
	if (identifier == 0)
		color->r = value;
	else if (identifier == 1)
		color->g = value;
	else if (identifier == 2)
		color->b = value;
}

/*
line: input line starting with an Identifier
*pos: position at which we expect the start of RGB values
function checks if the next set of values starting
line[*pos] is a valid RGB triplet
*/
int	get_RGB(char *line, int *pos, t_color *result_rgb)
{
	int	value;
	int	i;

	i = 0;
	skip_whitespace(line, pos);
	while (i < 3)
	{
		value = 0;
		if (!ft_isdigit(line[*pos]))
			return (display_error(RGB_WRONG_CHAR));
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
