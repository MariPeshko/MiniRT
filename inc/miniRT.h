#ifndef MINIRT_H
# define MINIRT_H

//unistd.h is included in libft.h
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

# include <float.h>  // For DBL_MAX and DBL_MIN. these are macros, no functions, and therefor allowed
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
# include <mlx.h>//minilibx-linux
# include <X11/keysym.h>//keysyms 

# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"

# define SUCCESS 0
# define FAILURE 1
# define ESC_KEY 65307// Keycode for ESC key on Linux with MinilibX
# define WIN_WIDTH 800
# define WIN_HEIGHT 450
# define VIEWPORT_RATIO (16.0 / 9.0)
# define VIEWPORT_RATIO_REVERSE (9.0 / 16.0)

# define NONE "NONE"
# define PLANE "PLANE"
# define SPHERE "SPHERE"
# define CYLINDER "CYLINDER"

void	print_vec(t_vector *vec, const char *msg);


// check_initial.c
void	arg_error(int argc);
void	check_filename(char *config);
int		is_empt_file(char *filename);

//check_cylinders_hit.c
int	get_hit_cys(t_cys *cy, t_hit *got, t_ray *ray);
void	check_cys_hit(t_config *cf, t_col *calc, t_ray *ray);

//check_sphere_hit.c
int	get_hit_sphere(t_spher *sp, t_hit *got, t_ray *ray);
void	check_sphere_hit(t_config *cf, t_col *calc, t_ray *ray);

//check_plane_hit.c
int	get_hit_plane(t_plane *pl, t_hit *got, t_ray *ray);
void	check_plane_hit(t_config *cf, t_col *calc, t_ray *ray);

// config_file.c
int		open_config(char *config, t_config *cf);
void	init_point(t_point *p, double *triplet);
void	init_vec(t_vector *vec, double *triplet);

//debugging_prints.c
void	print_test_config(t_config *cf);
void	print_map(char **map);
void	print_triplet(float *triplet);
void	print_viewport(t_vp *vp);
void	print_collision(t_col calc);

//error_handling.c
int		display_error(char *msg);

//get_hit.c
int	get_hit(t_config *cf, t_mini_rt *rt, t_ray *ray);
int	rays_loop(t_mini_rt *rt);

//parse_objects.c
int		full_parse_ambient(char *line, t_ambient *amb);
int		full_parse_camera(char *line, t_camera *camera);
int		full_parse_light(char *line, t_light *light);
int		parse_cylinder(char *line, t_cys **cylinder);
int		parse_plane(char *line, t_plane **plane);
int		parse_sphere(char *line, t_spher **sphere);

//parse_delegate.c
int		parse_delegate(char *line, t_config *cf);
int		calc_nmb_args(char *line);

//parse_helpers.c
int		get_int(char *line, int *pos, int *dest);
int		triplet_in_scope(double *triplet, double min, double max);
int		get_float(char *line, int *pos, float *dest);
int		get_three_floats(char *line, int *pos, double triplet[3]);

// parse_helpers.c
int		get_rgb(char *line, int *pos, t_color *result_rgb);
void	assign_rgb(t_color *in_struct, t_color result_rgb);

// str_utils.c
void	ft_freestr(char **lst);
void	trim_out_spaces(char **str);
int		ft_spacetabchecker(char *input);

//lst_hit.c
void	init_hit(t_hit *hit);
void	update_min(t_hit *min, t_hit *got);

// lst_struct_plane.c
t_plane	*get_ptr_lst_pl(t_plane **plane);
t_plane	*ft_lstnew_pl(t_plane *new);
void	ft_lstadd_back_pl(t_plane **lst, t_plane *new);

// lst_struct_sphere.c
t_spher	*get_ptr_lst_sph(t_spher **sphere);
t_spher	*ft_lstnew_sph(t_spher *new);
void	ft_lstadd_back_sph(t_spher **lst, t_spher *new);

// lst_struct_cylinder.c
t_cys	*get_ptr_lst_cyl(t_cys	**cylinder);
t_cys	*ft_lstnew_cy(t_cys *new);
void	ft_lstadd_back_cy(t_cys **lst, t_cys *new);
// might be unused
t_cys	*ft_lstlast_cy(t_cys *lst);

//mlx.c
void	setup_mlx(t_mini_rt *rt);
int handle_close(t_config *cf);
int handle_keypress(int keycode, t_config *cf);

//unsorted
int		map_len(char **map);
void	init_viewport(t_vp *vp);

//vector_calc.c
int	cross_product(t_vector *a, t_vector *b, t_vector *result);
int	normalize_vector(t_vector *v);
int	point_plus_vector(t_point *point, t_vector *vector, double factor, t_point *result);

//viewport_calc.c
int	calculate_viewport_orientation(t_config *cf);
int	calculate_height(t_config *cf);
int	calculate_width(t_config *cf);
int calculate_upper_left_corner(t_vp *viewp);
int	viewport_calculation(t_config *cf);


//whitespaces.c
void	whitespace_to_space(char *line);
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);

//cleanup.c
int		cleanup(t_config *cf);
void	clean_exit(t_config *cf, char *er_msg);
#endif
