#include "../inc/miniRT.h"

static void    print_error(error_type type)
{
	printf(RED "Error: " RESET);
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
}

void arg_error(int argc)
{
	if (argc == 1)
		print_error(NO_CONFIG_FILE);
	if (argc > 2)
		print_error(TOO_MANY_ARGS);
	exit(FAILURE);
}

// checking if it is .rt extenstion
static void	check_extention(char *config)
{
	int	i;

	i = 0;
	if (ft_strchr(config, '.') == 0)
	{
		print_error(WRONG_EXTEN);
		exit(FAILURE);
	}
	while (config[i])
	{
		if (config[i] == '.')
		{
			if (!(config[i + 1] == 'r' && config[i + 2] == 't' 
				&& !(config[i + 3])))
				{
					print_error(WRONG_EXTEN);
					exit(FAILURE);
				}
		}
		i++;
	}
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
		fd = open(filename, O_RDONLY);
	return (fd);
}

// open a config file
// a scene in format *.rt
void	open_config(char *config)
{
	int fd_conf;
	
	if (!*config || !config)
	{
		print_error(EMPTY_STRING);
		exit(SUCCESS);
	}
	check_extention(config);
	printf("Extention is correct. The file will be opened.\n");
	fd_conf = fd_creator(config);
	close(fd_conf);
}
