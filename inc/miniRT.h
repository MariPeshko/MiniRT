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

typedef struct s_vector
{
}	t_vector;

typedef struct s_point
{
}	t_point;

//debugging_prints.c
void    print_map(char **map);

//error_handling.c
int	display_error(char *msg);

//whitespaces.c
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);

#endif
