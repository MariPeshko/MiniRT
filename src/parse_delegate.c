#include "../inc/miniRT.h"

/*
line: input line starting with an Identifier
*pos: position at which we expect the start of RGB values
function checks if the next set of values starting
line[*pos] is a valid RGB triplet
later: adds foudn values to the needed struct. 
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

/*
parses a line starting with A
*/
int	parse_ambient_lighting(char *line)//+ large struct
{
	char **arguments;
	int	pos;

	pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 3)
		return (display_error(INVALID_NBR_ARG));
	//get ambient light ratio from arguments[1]
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}

int	parse_specific(char *line)
{
	printf("recognized [%c]\n", line[0]);
	return (SUCCESS);
}

/*
line: Input line starting with an Identifier
Function checks which identifier the line has
and passes it on to the respective parsing function
*/
int	parse_delegate(char *line)//+ largest struct
{
	if (ft_strncmp(line, "A", 1) == SUCCESS)
		return (parse_ambient_lighting(line));//+ largest struct
	else if (ft_strncmp(line, "C", 1) == SUCCESS)
		return (parse_specific(line));//+ largest struct
	else if (ft_strncmp(line, "L", 1) == SUCCESS)
		return (parse_specific(line));//+ largest struct
	else if (ft_strncmp(line, "cy", 2) == SUCCESS)
		return (parse_specific(line));//+ largest struct
	else if (ft_strncmp(line, "pl", 2) == SUCCESS)
		return (parse_specific(line));//+ largest struct
	else if (ft_strncmp(line, "sp", 2) == SUCCESS)
		return (parse_specific(line));//+ largest struct
	else if (line[0] != '\0')
		return (display_error(WRONG_IDENTIFIER));
	return (SUCCESS);
}
