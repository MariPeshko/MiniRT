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
	if (check_empt_file(filename) == FAILURE)
	{
		display_error(EMPTY_FILE);
		exit(FAILURE);
	}
	return (fd);
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
		if (parse_delegate(line, cf) != 1)
			printf("%s\n", line);
		free(line);
		line = get_next_line(fd_conf);
	}
	printf("amb.lighting_ratio: %.1f\n", cf->amb.lighting_ratio);
	printf("amb.col.r: %i\n", cf->amb.col.r);
	printf("amb.col.g: %i\n", cf->amb.col.g);
	printf("amb.col.b: %i\n", cf->amb.col.b);
	close(fd_conf);
}
