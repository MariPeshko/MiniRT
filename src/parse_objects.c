#include "../inc/miniRT.h"

/* potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/
/*parses a line starting with A*/
int	parse_ambient_lighting(char *line, t_ambient *amb)
{
	char	**arguments;
	int		pos;
	float	tmp = 0;

	pos = 1;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 3)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//print_map(arguments);
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	amb->lighting_ratio = tmp;
	/*if (!is_whitespace(line[pos]))
	{
		//check if we actually need this.
		display_error(WRONG_CHAR);
	}*/
	t_color	rgb;
	if (get_RGB(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&amb->col, rgb);
	return (SUCCESS);
}

/*parses a line starting with C*/
int	parse_camera(char *line, t_camera *camera)
{
	char **arguments;
	int	pos = 1;
	int	tmp;

	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//get Point (coordinates of View point) and save them
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized orientation vector (3 floats)
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get FOV. Is this an int or float? -> full nbr
	if (get_int(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp > 180 || tmp < 0)
		return (display_error(FOV_SCOPE));
	camera->fov = tmp;
	return (SUCCESS);
}

/*parses a line starting with L*/
int	parse_light(char *line, t_light *light)
{
	char **arguments;
	int	pos;
	float	tmp;

	pos = 1;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//get Point (coordinates of Light point)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get brightness (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	//get RGB? (unused in mandatory, so require it or not?)
	t_color	rgb;
	if (get_RGB(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&light->col, rgb);
	return (SUCCESS);
}


/*parses a line starting with cy*/
int	parse_cylinder(char *line, t_cys **cylinder)
{
	char	**arguments;
	int		pos;
	float	tmp;

	if(!*cylinder)
	{
		*cylinder = ft_calloc(1, sizeof(t_cys));
		(*cylinder)->next = NULL;
	}

	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 6)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//get Point (center of cylinder)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized vector
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get cylinder diameter (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0)
		return (display_error(CY_DIAMETER_SCOPE));
	//get cylinder height (float). can be negative or not?
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	//get RGB color of cylinder
	t_color	rgb;
	if (get_RGB(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&(*cylinder)->col, rgb);
	return (SUCCESS);
}

/*
parses a line starting with pl
*/
int	parse_plane(char *line, t_planes **plane)
{
	char **arguments;
	int	pos;

	if(!*plane)
	{
		*plane = ft_calloc(1, sizeof(t_planes));
		(*plane)->next = NULL;
	}

	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//get Point in the plane
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get normalized vector
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (display_error(NV_SCOPE));
	//get RGB color of plane
	t_color	rgb;
	if (get_RGB(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&(*plane)->col, rgb);
	return (SUCCESS);
}

/*
parses a line starting with sp
*/
int	parse_sphere(char *line, t_spheres **sphere)
{
	char	**arguments;
	int		pos;
	float	tmp;
	//int	rgb[3];make like triplet so that data gets changed out here
	//or make it a struct that get RGB can alter.

	if(!*sphere)
	{
		*sphere = ft_calloc(1, sizeof(t_spheres));
		(*sphere)->next = NULL;
	}
	pos = 2;
	arguments = ft_split(line, ' ');
	if (!arguments)
		return (display_error(MEMORY));
	if (map_len(arguments) != 4)
	{
		display_error(INVALID_NBR_ARG);
		ft_freestr(arguments);
		return (FAILURE);
	}
	ft_freestr(arguments);
	//get Point (center of sphere)
	float triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	//get sphere diameter (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0)
		return (display_error(SP_DIAMETER_SCOPE));
	//get RGB color of sphere
	t_color	rgb;
	if (get_RGB(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&(*sphere)->col, rgb);
	return (SUCCESS);
}
