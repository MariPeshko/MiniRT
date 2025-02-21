#ifndef MINIRT_H
# define MINIRT_H

//unistd.h is included in libft.h
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

# include <stdio.h>
# include <fcntl.h> // open
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <math.h>
# include <stdbool.h> //boolean
# include <string.h> //strerror
# include <errno.h> //errno, perror
# include "../libft/inc/libft_gnl_printf.h"//libft, gnl and fr_printf by sgramsch
# include "miniRT_error_macro.h"
# include "miniRT_structs.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"

/*typedef enum 
{
    NO_CONFIG_FILE = 1,
    TOO_MANY_ARGS = 2,
	EMPTY_STRING = 3,
	WRONG_EXTEN = 4,
    FILE_ERR = 5,
    EMPTY_FILE = 6
} error_type ;*/

# define SUCCESS 0
# define FAILURE 1

// config_file.c
void	arg_error(int argc);
void	open_config(char *config, s_config *cf);

//debugging_prints.c
void	print_map(char **map);
void	print_triplet(float *triplet);

//error_handling.c
int	display_error(char *msg);

//parse_objects.c
int	parse_ambient_lighting(char *line);
int	parse_camera(char *line);
int	parse_light(char *line);
int	parse_cylinder(char *line);
int	parse_plane(char *line);
int	parse_sphere(char *line);

//parse_delegate.c
int	parse_delegate(char *line);

//parse_helpers.c
int	triplet_in_scope(float *triplet, float min, float max);
int	get_float(char *line, int *pos, float *dest);
int	get_three_floats(char *line, int *pos, float triplet[3]);
int	get_RGB(char *line, int *pos);

// str_utils.c
void	trim_out_spaces(char **str);
int		ft_spacetabchecker(char *input);

//unsorted
int	map_len(char **map);

//whitespaces.c
void	whitespace_to_space(char *line);
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);

#endif
