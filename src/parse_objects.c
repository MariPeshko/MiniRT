#include "../inc/miniRT.h"

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

/*potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/

/*parses a line starting with A*/
int	parse_ambient_lighting(char *line)//+ large struct
{
	printf("ambient\n");
	char **arguments;
	int	pos;
	float	tmp = 0;

	pos = 1;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	//print_map(arguments);
	if (map_len(arguments) != 3)
		return (display_error(INVALID_NBR_ARG));
	get_float(line, &pos, &tmp);
	printf("ambient light ratio: %f\n", tmp);
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
	printf("camera\n");
	char **arguments;
	int	pos = 1;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of View point) and save them
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	printf("Point: ");
	print_triplet(triplet);
	//get normalized orientation vector (3 floats)
	get_three_floats(line, &pos, triplet);
	printf("normalized orientation Vector: ");
	print_triplet(triplet);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get FOV. Is this an int or float?
	//
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with L*/
int	parse_light(char *line)//+ large struct
{
	printf("light\n");
	char **arguments;
	int	pos;
	float	tmp;

	pos = 1;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	//print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of Light point)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	printf("Point: ");
	print_triplet(triplet);
	//get brightness (float)
	get_float(line, &pos, &tmp);
	printf("brightness: %f\n", tmp);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	//get RGB? (unused in mandatory, so require it or not?)
	//
	free(arguments);
	return (SUCCESS);
}

/*parses a line starting with cy*/
int	parse_cylinder(char *line)//+ large struct
{
	printf("cylinder\n");
	char **arguments;
	int	pos;
	float	tmp;

	pos = 1;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	//print_map(arguments);
	if (map_len(arguments) != 6)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of cylinder)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	printf("Point: ");
	print_triplet(triplet);
	//get normalized vector
	get_three_floats(line, &pos, triplet);
	printf("normalized orientation Vector: ");
	print_triplet(triplet);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get cylinder diameter (float)
	get_float(line, &pos, &tmp);
	printf("cylinder diameter: %f\n", tmp);
	//get cylinder height (float)
	get_float(line, &pos, &tmp);
	printf("cylinder height: %f\n", tmp);
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
	printf("plane:\n");
	char **arguments;
	int	pos;

	pos = 1;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	//print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point in the plane
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	printf("Point: ");
	print_triplet(triplet);
	//get normalized vector
	get_three_floats(line, &pos, triplet);
	printf("normalized orientation Vector: ");
	print_triplet(triplet);
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
	printf("\nsphere\n");
	char **arguments;
	int	pos;
	float	tmp;
	//int	rgb[3];make like triplet so that data gets changed out here

	pos = 1;//position at which RGB starts in tests
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	//print_map(arguments);
	if (map_len(arguments) != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (center of sphere)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	printf("Point on plane: ");
	print_triplet(triplet);
	//get sphere diameter (float)
	get_float(line, &pos, &tmp);
	printf("Sphere diameter: %f\n", tmp);
	//get RGB color of sphere
	if (get_RGB(line, &pos) == FAILURE)
		return (FAILURE);
	free(arguments);
	return (SUCCESS);
}