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
	if (check_final_config(cf) == SUCCESS)
	{
		// assigning an id for each element.
		// it might be convenient 
		//print_test_config(cf);
		return (SUCCESS);
	}
	return (FAILURE);
}
