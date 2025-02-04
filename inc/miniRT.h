#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>
# include "../libft/inc/libft_gnl_printf.h"//libft, gnl and fr_printf by sgramsch
# define SUCCESS 0
# define FAILURE 1
# define MEMORY "Memory allocation failed."
# define INVALID_NBR_ARG "Invalid number of Arguments."
# define WRONG_CHAR "unexpected character."
# define RGB_SCOPE "RGB value out of scope."
# define WRONG_IDENTIFIER "Invalid Idetifier."
# define A_SCOPE "Ambient light ratio out of scope."
# define NV_SCOPE "normalized Vector out of Scope [0.0, 1.0]"
# define SP_DIAMETER_SCOPE "Sphere diameter out of scope."
# define CY_DIAMETER_SCOPE "Cylinder diameter out of scope."

typedef struct s_vector
{
}	t_vector;

typedef struct s_point
{
}	t_point;

//debugging_prints.c
void    print_map(char **map);
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
int	get_three_floats(char *line, int *pos, float *triplet);
int	get_RGB(char *line, int *pos);

//unsorted
int	map_len(char **map);

//whitespaces.c
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);

#endif
