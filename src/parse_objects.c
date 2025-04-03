#include "../inc/miniRT.h"

/* potentially later split up into parse lights (A and L)
parse View (C) and parse objects (cy, pl, sp)*/
/*parses a line starting with A*/
int	full_parse_ambient(char *line, t_ambient *amb)
{
	int		pos;
	float	tmp = 0;
	int		nmb_args;
	t_color	rgb;

	pos = 1;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 3)
		return (display_error(INVALID_NBR_ARG));
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
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&amb->col, rgb);
	return (SUCCESS);
}

/*parses a line starting with C*/
int	full_parse_camera(char *line, t_camera *camera)
{
	int	pos;
	int	tmp;
	int	nmb_args;

	pos = 1;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of View point) and save them
	double	triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&camera->point, triplet);
	//get normalized orientation vector (3 floats)
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&camera->norm_vec, triplet);
	//get FOV. Is this an int or float? -> full nbr
	if (get_int(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp > 180 || tmp < 0)
		return (display_error(FOV_SCOPE));
	camera->fov = tmp;
	return (SUCCESS);
}

/*parses a line starting with L*/
int	full_parse_light(char *line, t_light *light)
{
	int		pos;
	float	tmp;
	int		nmb_args;

	pos = 1;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG));
	//get Point (coordinates of Light point)
	double triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&light->point, triplet);
	//get brightness (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp < 0.0 || tmp > 1.0)
		return (display_error(A_SCOPE));
	light->bright = tmp;
	//get RGB? (unused in mandatory, so require it or not?)
	t_color	rgb;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&light->col, rgb);
	return (SUCCESS);
}

int	assign_value_plane(char *line, t_plane *lst_pl)
{
	int			pos;
	//get Point in the plane
	double		triplet[3];
	t_color		rgb;

	pos = 2;
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&lst_pl->point, triplet);
	//get normalized vector
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&lst_pl->pl_normal, triplet);
	//get RGB color of plane
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&lst_pl->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with pl */
int	parse_plane(char *line, t_plane **plane)
{
	int			nmb_args;
	t_plane	*lst_pl;

	lst_pl = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG_PL));
	lst_pl = get_ptr_lst_pl(plane);
	if (lst_pl == NULL)
		return (FAILURE);
	if (assign_value_plane(line, lst_pl) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	assign_value_cyl(char *line, t_cys *cylinder)
{
	int		pos;
	float	tmp;

	pos = 2;
	//get Point (center of cylinder)
	double	triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&cylinder->point, triplet);
	//get normalized vector
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	if (triplet_in_scope(triplet, -1.0, 1.0) == FAILURE)
		return (FAILURE);
	init_vec(&cylinder->norm_vec, triplet);
	//get cylinder diameter (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp <= 0)
		return (display_error(CY_DIAMETER_SCOPE));
	cylinder->diam = tmp;
	//get cylinder height (float). can be negative or not?
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	cylinder->height = tmp;
	//get RGB color of cylinder
	t_color	rgb;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&cylinder->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with cy*/
int	parse_cylinder(char *line, t_cys **cylinder)
{
	int		nmb_args;
	t_cys	*lst_cyl;

	lst_cyl = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 6)
		return (display_error(INVALID_NBR_ARG_CY));
	lst_cyl = get_ptr_lst_cyl(cylinder);
	if (lst_cyl == NULL)
		return (FAILURE);
	if (assign_value_cyl(line, lst_cyl) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	assign_value_sphere(char *line, t_spher *lst_sph)
{
	int		pos;
	float	tmp;

	pos = 2;
	//get Point (center of sphere)
	double triplet[3];
	if (get_three_floats(line, &pos, triplet) == FAILURE)
		return (FAILURE);
	init_point(&lst_sph->point, triplet);
	//get sphere diameter (float)
	if (get_float(line, &pos, &tmp) == FAILURE)
		return (FAILURE);
	if (tmp <= 0)
		return (display_error(SP_DIAMETER_SCOPE));
	lst_sph->diam = tmp;
	//get RGB color of sphere
	t_color	rgb;
	if (get_rgb(line, &pos, &rgb) == FAILURE)
		return (FAILURE);
	assign_rgb(&lst_sph->col, rgb);
	return (SUCCESS);
}

/* parses a line starting with sp */
int	parse_sphere(char *line, t_spher **sphere)
{
	int			nmb_args;
	t_spher	*lst_sph;
	
	lst_sph = NULL;
	nmb_args = calc_nmb_args(line);
	if (nmb_args != 4)
		return (display_error(INVALID_NBR_ARG_SP));
	lst_sph = get_ptr_lst_sph(sphere);
	if (lst_sph == NULL)
		return (FAILURE);
	if (assign_value_sphere(line, lst_sph) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
