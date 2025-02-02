#ifndef MINIRT_H
# define MINIRT_H

//unistd.h is included in libft.h
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"

typedef enum 
{
    NO_CONFIG_FILE = 1,
    TOO_MANY_ARGS = 2,
	EMPTY_STRING = 3,
	WRONG_EXTEN = 4
} error_type ;

# define SUCCESS 0
# define FAILURE 1

typedef struct s_vector
{
}	t_vector;

typedef struct s_point
{
}	t_point;

// config_file.c
void    arg_error(int argc);
void	open_config(char *config);

#endif
