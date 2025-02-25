#include "../inc/miniRT.h"

/*
line: Input line starting with an Identifier.
Function checks which identifier the line has
and passes it on to the respective parsing function.
*/
int	parse_delegate(char *line, t_config *cf)
{
	if (ft_strncmp(line, "\n", 1) == SUCCESS)
		return (SUCCESS);
	whitespace_to_space(line);
	if (ft_strncmp(line, "A", 1) == SUCCESS)
		return (parse_ambient_lighting(line, &cf->amb));
	else if (ft_strncmp(line, "C", 1) == SUCCESS)
		return (parse_camera(line, &cf->cam));
	else if (ft_strncmp(line, "L", 1) == SUCCESS)
		return (parse_light(line, &cf->light));
	else if (ft_strncmp(line, "pl", 2) == SUCCESS)
		return (parse_plane(line, &cf->pl));
	else if (ft_strncmp(line, "sp", 2) == SUCCESS)
		return (parse_sphere(line, &cf->sp));
	else if (ft_strncmp(line, "cy", 2) == SUCCESS)
		return (parse_cylinder(line, &cf->cy));
	else if (line[0] != '\0')
	{
		free(line);
		clean_exit(cf,WRONG_IDENTIFIER);
	}
	return (SUCCESS);
}
