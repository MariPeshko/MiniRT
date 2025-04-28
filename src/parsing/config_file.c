#include "../inc/miniRT.h"

/*opens given file and returns id upon it being a
file worth reading from. otherwise exits*/
static int	fd_creator(char *filename)
{
	int		fd;

	fd = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		display_error(strerror(errno));
		exit(FAILURE);
	}
	if (is_empt_file(filename) == true)
	{
		display_error(EMPTY_FILE);
		exit(FAILURE);
	}
	return (fd);
}

static void	init_col(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	init_point(t_point *p, double *triplet)
{
    if (p != NULL)
	{
        p->x = triplet[0];
        p->y = triplet[1];
        p->z = triplet[2];
    }
}

void	init_vec(t_vector *vec, double *triplet)
{
	if (vec != NULL)
	{
		vec->x = triplet[0];
		vec->y = triplet[1];
		vec->z = triplet[2];
	}
}

/*It initialises all linked list to NULL.
What about inisialising of int and double? (Maryna)
Yes, valgrind complaining when I print uninitialised
values (it is conditional jump or move) (S: thanks for the warning)*/
void	init_config(t_config *cf)
{
	double triplet[3];

    triplet[0] = 0.0;
    triplet[1] = 0.0;
    triplet[2] = 0.0;
	cf->valid = true;
	cf->one_amb = false;
	cf->one_cam = false;
	cf->one_lit = false;
	cf->amb.lighting_ratio = 0;
	init_col(&cf->amb.col, 0, 0, 0);
	cf->cam.fov = 0;
	init_vec(&cf->cam.norm_vec,triplet);
	init_point(&cf->cam.point, triplet);
	cf->light.bright = 0;
	init_col(&cf->light.col, 0, 0, 0);
	init_point(&cf->light.point, triplet);
	cf->pl = NULL;
	cf->sp = NULL;
	cf->cy = NULL;
}

int	check_final_config(t_config *cf)
{
	if (cf->one_amb == false)
	{
		display_error(MUST_ONE_AMB);
		cf->valid = false;
	}
	if (cf->one_cam == false)
	{
		display_error(MUST_ONE_CAM);
		cf->valid = false;
	}
	if (cf->one_lit == false)
	{
		display_error(MUST_ONE_LIT);
		cf->valid = false;
	}
	if (cf->valid == false)
		return (FAILURE);
	return (SUCCESS);
}

static void check_camera_inside_sphere(t_point camera_pos, t_point sphere_center, double diametr)
{
	double radius;

	radius = diametr / 2;
    double dx = camera_pos.x - sphere_center.x;
    double dy = camera_pos.y - sphere_center.y;
    double dz = camera_pos.z - sphere_center.z;
    double distance_squared = dx * dx + dy * dy + dz * dz;
    if (distance_squared < radius * radius)
	{
		printf(GREEN "Message: " RESET);
        printf("Camera is inside the sphere!\n");
	}
}

static void cam_inside_sphere(t_config *cf)
{
	t_spher	*sp;

	sp = cf->sp;
	while (sp)
	{
		check_camera_inside_sphere(cf->cam.point, sp->point, sp->diam);
		sp = sp->next;
	}
}

double vec3_dot(t_vector a, t_vector b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_point vec3_sub(t_vector a, t_point b)
{
    t_point result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return (result);
}

int check_camera_inside_cylinder(t_point camera_pos, t_cys cyl)
{
    t_vector v;
	double radius = cyl.diam / 2;
	
	point_minus_point(&camera_pos, &cyl.point, &v);
    double projection_length; // = vec3_dot(v, cyl.norm_vec);
	dot_product(&v, &cyl.norm_vec, &projection_length);
    
    // Projected vector along the cylinder axis
    t_vector proj;

    proj.x = projection_length * cyl.norm_vec.x;
    proj.y = projection_length * cyl.norm_vec.y;
    proj.z = projection_length * cyl.norm_vec.z;
    
    // Perpendicular vector
    t_vector v_perp; // = vec3_sub(v, proj);
	subtract_vectors(&v, &proj, &v_perp);

    double distance_squared = vec3_dot(v_perp, v_perp);

    if (distance_squared < radius * radius)
		return (FAILURE);
	return (SUCCESS);
        printf("Cyl inside\n");
}

static int cam_inside_cyl(t_config *cf)
{
	t_cys	*cy;

	cy = cf->cy;
	while (cy)
	{
		if (check_camera_inside_cylinder(cf->cam.point, *cy) == FAILURE)
		{
			display_error(CAM_INS_CY);
			return (FAILURE);
		}
		cy = cy->next;
	}
	return (SUCCESS);
}

/*open a config file
a scene in format *.rt*/
int	open_config(char *config, t_config *cf)
{
	int		fd_conf;
	char	*line;

	check_filename(config);
	init_config(cf);
	fd_conf = fd_creator(config);
	line = get_next_line(fd_conf);
	while (line != NULL)
	{
		if (ft_spacetabchecker(line))
			trim_out_spaces(&line);
		if (parse_delegate(line, cf) == FAILURE)
			cf->valid = false;
		/* {
			if (line[0] && (line[0] != '\n') && cf->valid == true)
				printf("%s\n", line);
		}
		else */
		//	cf->valid = false;
		free(line);
		line = get_next_line(fd_conf);
	}
	close(fd_conf);
	cam_inside_sphere(cf);
	if (cam_inside_cyl(cf) == FAILURE)
		return (FAILURE);
	if (check_final_config(cf) == SUCCESS)
	{
		// assigning an id for each element.
		// it might be convenient 
		print_test_config(cf);
		return (SUCCESS);
	}
	return (FAILURE);
}
