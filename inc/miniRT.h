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
//# include "../libft/inc/libft_gnl_printf.h"
//libft, gnl and fr_printf by sgramsch
# include "miniRT_error_macro.h"
# include "miniRT_structs.h"

# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"

# define SUCCESS 0
# define FAILURE 1

// check_initial.c
void	arg_error(int argc);
void	check_filename(char *config);
int		is_empt_file(char *filename);

// config_file.c
int		open_config(char *config, t_config *cf);
void	init_point(t_point *p, double *triplet);
void	init_vec(t_vector *vec, double *triplet);

//debugging_prints.c
void	print_test_config(t_config *cf);
void	print_map(char **map);
void	print_triplet(float *triplet);

//error_handling.c
int		display_error(char *msg);

//parse_objects.c
int		parse_ambient_lighting(char *line, t_ambient *amb);
int		parse_camera(char *line, t_camera *camera);
int		parse_light(char *line, t_light *light);
t_cys	*ft_lstlast_cy(t_cys *lst);
int		parse_cylinder(char *line, t_cys **cylinder);
int		parse_plane(char *line, t_planes **plane);
int		parse_sphere(char *line, t_spheres **sphere);

//parse_delegate.c
int		parse_delegate(char *line, t_config *cf);
int		calc_nmb_args(char *line);

//parse_helpers.c
void	assign_rgb(t_color *in_struct, t_color result_rgb);
int		get_int(char *line, int *pos, int *dest);
int		triplet_in_scope(double *triplet, double min, double max);
int		get_float(char *line, int *pos, float *dest);
int		get_three_floats(char *line, int *pos, double triplet[3]);
int		get_RGB(char *line, int *pos, t_color *result_rgb);

// str_utils.c
void	ft_freestr(char **lst);
void	trim_out_spaces(char **str);
int		ft_spacetabchecker(char *input);

//unsorted
int		map_len(char **map);

//whitespaces.c
void	whitespace_to_space(char *line);
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);

//cleanup.c
int	cleanup(t_config *cf);
void	clean_exit(t_config *cf, char *er_msg);
#endif
