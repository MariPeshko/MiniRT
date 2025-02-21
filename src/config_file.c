#include "../inc/miniRT.h"

/*static void    print_error(error_type type)
{
	printf(RED "Error:\n" RESET);
	if (type == NO_CONFIG_FILE)
	{
		printf("Run a program with a configuration file as follows:\n");
		printf(GREEN "./miniRT [name_of_the_file].rt\n" RESET);
	}
	if (type == TOO_MANY_ARGS)
		printf("Too many arguments.\n");
	if (type == EMPTY_STRING)
	{
		printf("Argument is an empty string.\n");
		printf("Enter the name of the configuration file.\n");
	}
	if (type == WRONG_EXTEN)
		printf("Wrong extention. File must be in .rt format.\n");
	if (type == FILE_ERR)
		printf("Error opening file.\n");
	if (type == EMPTY_FILE)
		printf("Configuration file is empty.\n");
}*/

void arg_error(int argc)
{
	if (argc == 1)
		display_error(NO_CONFIG_FILE);
	if (argc > 2)
		display_error(TOO_MANY_ARGS);
	exit(FAILURE);
}

// checking if it is .rt extenstion
static void	check_extention(char *config)
{
	int	i;

	i = 0;
	if (ft_strchr(config, '.') == 0)
	{
		display_error(WRONG_EXTEN);
		exit(FAILURE);
	}
	while (config[i])
	{
		if (config[i] == '.')
		{
			if (!(config[i + 1] == 'r' && config[i + 2] == 't' 
				&& !(config[i + 3])))
				{
					display_error(WRONG_EXTEN);
					exit(FAILURE);
				}
		}
		i++;
	}
}

int	check_empt_file(char *filename)
{
	int		fd;
	int		byte;
	char	buff[1];

	fd = open(filename, O_RDONLY);
	byte = read(fd, buff, 1);
	if (byte != 1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

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
void	init_config(s_config *cf)
{
	cf->pl = NULL;
	cf->sp = NULL;
	cf->cy = NULL;
	// What about inisialising of int and double? (Maryna)
}

// open a config file
// a scene in format *.rt
void	open_config(char *config, s_config *cf)
{
	int fd_conf;
	
	init_config(cf);
	if (!*config || !config)
	{
		display_error(EMPTY_STRING);
		exit(SUCCESS);
	}
	check_extention(config);
	fd_conf = fd_creator(config);

	char *line = NULL;
	while((line = get_next_line(fd_conf)) != NULL)
	{
		if (ft_spacetabchecker(line))
			trim_out_spaces(&line);

		//// PARSING FUNCTION
		parse_delegate(line);

		printf("%s\n", line);
		free(line);
	}
	close(fd_conf);
}
