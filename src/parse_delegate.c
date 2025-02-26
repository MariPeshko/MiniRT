#include "../inc/miniRT.h"

int	parse_ambient(char *line, t_config *cf)
{
	if (cf->one_amb == true)
		return(display_error(TOO_MANY_AMB));
	else
		cf->one_amb = true;
	return (full_parse_ambient(line, &cf->amb));
}

int	parse_camera(char *line, t_config *cf)
{
	if (cf->one_cam == true)
		return(display_error(TOO_MANY_CAM));
	else
		cf->one_cam = true;
	return (full_parse_camera(line, &cf->cam));
}

int	parse_light(char *line, t_config *cf)
{
	if (cf->one_lit == true)
		return(display_error(TOO_MANY_LIT));
	else
		cf->one_lit = true;
	return (full_parse_light(line, &cf->light));
}

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
		return(parse_ambient(line, cf));
	else if (ft_strncmp(line, "C", 1) == SUCCESS)
		return(parse_camera(line, cf));
	else if (ft_strncmp(line, "L", 1) == SUCCESS)
		return(parse_light(line, cf));
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

/**
 * Calculates the number of arguments in the line
 * of the configuration file '.rt'.
*/
int	calc_nmb_args(char *line)
{
	char	**arguments;
	int		nmb_args;

	nmb_args = 0;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	nmb_args = map_len(arguments);
	ft_freestr(arguments);
	return(nmb_args);
}
