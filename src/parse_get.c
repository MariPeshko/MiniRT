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