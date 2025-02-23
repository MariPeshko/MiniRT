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

void	print_point(t_point *p, const char *msg)
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

/*It initialises all linked list to NULL.
What about inisialising of int and double? (Maryna)
Yes, valgrind complaining when I print uninitialised
values (it is conditional jump or move) (S: thanks for the warning)*/
void	init_config(t_config *cf)
{
	cf->pl = NULL;
	cf->sp = NULL;
	cf->cy = NULL;
	cf->amb.col.r = 0;
	cf->amb.col.g = 0;
	cf->amb.col.b = 0;
	cf->amb.lighting_ratio = 0;
	cf->cam.fov = 0;
	init_vec(&cf->cam.norm_vec, 0, 0, 0);
	init_point(&cf->cam.point, 0, 0, 0);
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
	printf("amb.col.r: %i\n", cf->amb.col.r);
	printf("amb.col.g: %i\n", cf->amb.col.g);
	printf("amb.col.b: %i\n", cf->amb.col.b);
	print_vec(&cf->cam.norm_vec, "Camera norm vector");
	print_point(&cf->cam.point, NULL);
	close(fd_conf);
}
