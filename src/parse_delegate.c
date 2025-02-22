#include "../inc/miniRT.h"

/*
line: Input line starting with an Identifier.
Function checks which identifier the line has
and passes it on to the respective parsing function.
*/
int	parse_delegate(char *line, t_config *cf)
{
	if (ft_strncmp(line, "\n", 1) == SUCCESS)
		return (FAILURE);//empty line
	whitespace_to_space(line);
	if (ft_strncmp(line, "A", 1) == SUCCESS)
		return (parse_ambient_lighting(line, cf));
	else if (ft_strncmp(line, "C", 1) == SUCCESS)
		return (parse_camera(line, cf));
	else if (ft_strncmp(line, "L", 1) == SUCCESS)
		return (parse_light(line, cf));
	else if (ft_strncmp(line, "cy", 2) == SUCCESS)
		return (parse_cylinder(line, cf));
	else if (ft_strncmp(line, "pl", 2) == SUCCESS)
		return (parse_plane(line, cf));
	else if (ft_strncmp(line, "sp", 2) == SUCCESS)
		return (parse_sphere(line, cf));
	else if (line[0] != '\0')
		return (display_error(WRONG_IDENTIFIER));
	return (SUCCESS);
}
