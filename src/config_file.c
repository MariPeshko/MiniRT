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

static void	init_point(t_point *p, double x, double y, double z)
{
	p->x = x;
	p->y = y;
	p->z = z;
}

static void	init_vec(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

static void	init_col(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

/*It initialises all linked list to NULL.
What about inisialising of int and double? (Maryna)
Yes, valgrind complaining when I print uninitialised
values (it is conditional jump or move) (S: thanks for the warning)*/
void	init_config(t_config *cf)
{
	cf->valid = true;
	cf->amb.lighting_ratio = 0;
	init_col(&cf->amb.col, 0, 0, 0);
	cf->cam.fov = 0;
	init_vec(&cf->cam.norm_vec, 0, 0, 0);
	init_point(&cf->cam.point, 0, 0, 0);
	cf->light.bright = 0;
	init_col(&cf->light.col, 0, 0, 0);
	init_point(&cf->light.point, 0, 0, 0);
	cf->pl = NULL;
	cf->sp = NULL;
	cf->cy = NULL;
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
		if (parse_delegate(line, cf) == SUCCESS)
		{
			if (line[0] && (line[0] != '\n') && cf->valid == true)
				printf("%s\n", line);
		}
		else
			cf->valid = false;
		free(line);
		line = get_next_line(fd_conf);
	}
	close(fd_conf);
	if (cf->valid == true)
	{
		print_test_config(cf);
		return (SUCCESS);
	}
	return (FAILURE);
}
