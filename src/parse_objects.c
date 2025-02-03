#include "../inc/miniRT.h"

/*potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/

/*parses a line starting with A*/
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

/*parses a line starting with C*/
int	parse_camera(char *line)//+ large struct
{
	char **arguments;
	//int	pos;

	//pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of View point)
	//get normalized orientation vector (3 floats)
	//get FOV
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with L*/
int	parse_light(char *line)//+ large struct
{
	char **arguments;
	//int	pos;

	//pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of Light point)
	//get brightness (float)
	//get RGB? (unused in mandatory, so require it or not?)
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with cy*/
int	parse_cylinder(char *line)//+ large struct
{
	char **arguments;
	//int	pos;

	//pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 6)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of cylinder)
	//get normalized vector
	//get cylinder diameter (float)
	//get cylinder height (float)
	//get RGB color of cylinder
	free(arguments);
	return (SUCCESS);
}

/*
parses a line starting with pl
*/
int	parse_plane(char *line)//+ large struct
{
	char **arguments;
	//int	pos;

	//pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point in the plane
	//get normalized vector
	//get RGB color of plane
	free(arguments);
	return (SUCCESS);
}

/*
parses a line starting with sp
*/
int	parse_sphere(char *line)//+ large struct
{
	char **arguments;
	//int	pos;

	//pos = 5;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of sphere)
	//get sphere diameter (float)
	//get RGB color of sphere
	free(arguments);
	return (SUCCESS);
}