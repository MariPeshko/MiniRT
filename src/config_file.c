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

void check_empt_file(char *filename)
{
	int		fd;
	int		byte;
	char	buff[1];

	fd = open(filename, O_RDONLY);
	byte = read(fd, buff, 1);
	if (byte != 1)
	{
		close(fd);
		display_error(EMPTY_FILE);
		exit(FAILURE);
	}
	close(fd);
}

static int	fd_creator(char *filename)
{
	int		fd;

	fd = 0;
	if (access(filename, F_OK))
	{
		printf("%s: No such file or directory\n", filename);
		exit(FAILURE);
	}
	else if (access(filename, R_OK))
	{
		printf("%s: Permission denied\n", filename);
		exit(FAILURE);
	}
	else
	{
		check_empt_file(filename);
		fd = open(filename, O_RDONLY);
	}
	return (fd);
}

// open a config file
// a scene in format *.rt
void	open_config(char *config)
{
	int fd_conf;
	
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
