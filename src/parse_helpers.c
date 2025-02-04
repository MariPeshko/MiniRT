#include "../inc/miniRT.h"

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
	while (ft_isdigit(line[*pos]))
	{
		fractional = fractional + ((line[*pos] - '0') / divisor);
		divisor *= 10;
		(*pos)++;
	}
	*dest = (full_nbr + fractional) * neg;
	//printf("FLOAT: %f\n", *dest);
	return (SUCCESS);
}

/*gets the next three floats from line, starting at pos and saves them in triplet*/
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

/*
line: input line starting with an Identifier
*pos: position at which we expect the start of RGB values
function checks if the next set of values starting
line[*pos] is a valid RGB triplet
later: adds foudn values to the needed struct.
maybe make this edit a triplet like three floats function? 
*/
int	get_RGB(char *line, int *pos)
{
	int	value;
	int	i;

	i = 0;
	skip_whitespace(line, pos);
	//printf("\nGetting RGB [");
	while (i < 3)
	{
		value = 0;
		//printf("%c", line[*pos]);
		if (!ft_isdigit(line[*pos]))
			return (display_error(WRONG_CHAR));
		while (ft_isdigit(line[*pos]))
		{
			value = value * 10 + line[*pos] - '0';
			if (value > 255)
				return (display_error(RGB_SCOPE));
			(*pos)++;
		}
		if (i < 2 && line[*pos] != ',')
			return (display_error(WRONG_CHAR));
		//add Value to struct
		//if (i == 2)
		//	printf("%d]\n", value);
		//else
		//	printf("%d,", value);
		(*pos)++;
		i ++;
	}
	//printf("\n");
	return (SUCCESS);
}