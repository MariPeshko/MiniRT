#include "../inc/miniRT.h"

/*potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/

/*parses a line starting with A*/
int	parse_ambient_lighting(char *line)//+ large struct
{
	char **arguments;
	int	pos;
	float	tmp = 0;

	pos = 1;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 3)
		return (display_error(INVALID_NBR_ARG));
	print_map(arguments);
	//get ambient ratio
	get_float(line, &pos, &tmp);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	if (!is_whitespace(line[pos]))
		return (display_error(WRONG_CHAR));
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with C*/
int	parse_camera(char *line)//+ large struct
{
	char **arguments;
	int	pos = 1;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of View point) and save them
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized orientation vector (3 floats)
	get_three_floats(line, &pos, triplet);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get FOV. Is this an int or float? -> full nbr
	//
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with L*/
int	parse_light(char *line)//+ large struct
{
	char **arguments;
	int	pos;
	float	tmp;

	pos = 1;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of Light point)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get brightness (float)
	get_float(line, &pos, &tmp);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	//get RGB? (unused in mandatory, so require it or not?)
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with cy*/
int	parse_cylinder(char *line)//+ large struct
{
	char **arguments;
	int	pos;
	float	tmp;

	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 6)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of cylinder)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized vector
	get_three_floats(line, &pos, triplet);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get cylinder diameter (float)
	get_float(line, &pos, &tmp);
	if (tmp < 0)
		return (display_error(CY_DIAMETER_SCOPE));
	//get cylinder height (float). can be negative or not?
	//
	get_float(line, &pos, &tmp);
	//get RGB color of cylinder
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}

/*
parses a line starting with pl
*/
int	parse_plane(char *line)//+ large struct
{
	char **arguments;
	int	pos;

	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point in the plane
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized vector
	get_three_floats(line, &pos, triplet);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get RGB color of plane
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}

/*
parses a line starting with sp
*/
int	parse_sphere(char *line)//+ large struct
{
	char **arguments;
	int	pos;
	float	tmp;
	//int	rgb[3];make like triplet so that data gets changed out here
	//or make it a struct that get RGB can alter.

	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of sphere)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get sphere diameter (float)
	get_float(line, &pos, &tmp);
	if (tmp < 0)
		return (display_error(SP_DIAMETER_SCOPE));
	//get RGB color of sphere
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}