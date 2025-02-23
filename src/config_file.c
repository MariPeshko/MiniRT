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
	if (is_empt_file(filename) == TRUE)
	{
		display_error(EMPTY_FILE);
		exit(FAILURE);
	}
	return (fd);
}

static void	print_col(t_color *c, const char *msg)
{
	if (msg)
		printf("%s RGB ", msg);
	else
		printf("Undefined element's RGB ");
	printf("%i,", c->r);
	printf("%i,", c->g);
	printf("%i\n", c->b);
}

static void	print_point(t_point *p, const char *msg)
{
	if (msg)
		printf("%s ", msg);
	else
		printf("Undefined element's point ");
	printf("x: %f, ", p->x);
	printf("y: %f, ", p->y);
	printf("z: %f\n", p->y);
}

static void	print_vec(t_vector *vec, const char *msg)
{
	if (msg)
		printf("%s ", msg);
	else
		printf("Undefined element's vector ");
	printf("x: %f, ", vec->x);
	printf("y: %f, ", vec->y);
	printf("z: %f\n", vec->y);
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
void	open_config(char *config, t_config *cf)
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
			printf("%s\n", line);
		free(line);
		line = get_next_line(fd_conf);
	}
	printf("amb.lighting_ratio: %.1f\n", cf->amb.lighting_ratio);
	print_col(&cf->amb.col, "Ambience");
	print_vec(&cf->cam.norm_vec, "Camera norm vector");
	print_point(&cf->cam.point, NULL);
	close(fd_conf);
}
