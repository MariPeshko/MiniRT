#include "../inc/miniRT.h"

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
	if (check_empt_file(filename) < 0)
	{
		display_error(EMPTY_FILE);
		exit(FAILURE);
	}
	return (fd);
}

// It initialises all linked list to NULL.
// What about inisialising of int and double? (Maryna)
void	init_config(t_config *cf)
{
	cf->pl = NULL;
	cf->sp = NULL;
	cf->cy = NULL;
}

// open a config file
// a scene in format *.rt
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
		if (parse_delegate(line) != 1)
			printf("%s\n", line);
		free(line);
		line = get_next_line(fd_conf);
	}
	close(fd_conf);
}
