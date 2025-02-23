#include "../inc/miniRT.h"

/*displays the correct error if argc isn't 2*/
void	arg_error(int argc)
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

//checks for empty string as filename argument
void	check_filename(char *config)
{
	if (!config || !*config)
	{
		display_error(EMPTY_STRING);
		exit(SUCCESS);
	}
	check_extention(config);
}

int	is_empt_file(char *filename)
{
	int		fd;
	int		byte;
	char	buff[1];

	fd = open(filename, O_RDONLY);
	byte = read(fd, buff, 1);
	if (byte != 1)
	{
		close(fd);
		return (TRUE);
	}
	close(fd);
	return (FALSE);
}
