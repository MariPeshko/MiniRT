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

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif
# define EPSILON 1e-6

# define RESET   "\033[0m"
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"

# define SUCCESS 0
# define FAILURE 1
# define ESC_KEY 65307// Keycode for ESC key on Linux with MinilibX
# define DestroyNotify 17
# define WIN_WIDTH 320
# define WIN_HEIGHT 180
/* # define WIN_WIDTH 1280
# define WIN_HEIGHT 720 */
# define VIEWPORT_RATIO (16.0 / 9.0)
# define VIEWPORT_RATIO_REVERSE (9.0 / 16.0)

# define NONE "NONE"
# define PLANE "PLANE"
# define SPHERE "SPHERE"
# define CYLINDER "CYLINDER"

# define DestroyNotify 17

//parsing
//parsing/check_initial.c
void	arg_error(int argc);
void	check_filename(char *config);
int		is_empt_file(char *filename);
//parsing/config_file.c
int		open_config(char *config, t_config *cf);
void	init_point(t_point *p, double *triplet);
void	init_vec(t_vector *vec, double *triplet);
//parsing/parse_delegate.c
int		parse_delegate(char *line, t_config *cf);
int		calc_nmb_args(char *line);
//parsing/parse_objects.c
int		full_parse_ambient(char *line, t_ambient *amb);
int		full_parse_camera(char *line, t_camera *camera);
int		full_parse_light(char *line, t_light *light);
int		parse_cylinder(char *line, t_cys **cylinder);
int		parse_plane(char *line, t_plane **plane);
int		parse_sphere(char *line, t_spher **sphere);
//parsing/parse_rgb.c
int		get_rgb(char *line, int *pos, t_color *result_rgb);
void	assign_rgb(t_color *in_struct, t_color result_rgb);
//parsing/parse_helpers.c
int		get_int(char *line, int *pos, int *dest);
int		triplet_in_scope(double *triplet, double min, double max);
int		get_float(char *line, int *pos, float *dest);
int		get_three_floats(char *line, int *pos, double triplet[3]);
//parsing/test_parse_delegate.c
t_plane	*get_ptr_lst_pl(t_plane **plane);
t_plane	*ft_lstnew_pl(t_plane *new);
void	ft_lstadd_back_pl(t_plane **lst, t_plane *new);
//parsing/lst_struct_sphere.c
t_spher	*get_ptr_lst_sph(t_spher **sphere);
t_spher	*ft_lstnew_sph(t_spher *new);
void	ft_lstadd_back_sph(t_spher **lst, t_spher *new);
//parsing/lst_struct_cylinder.c
t_cys	*get_ptr_lst_cyl(t_cys	**cylinder);
t_cys	*ft_lstnew_cy(t_cys *new);
void	ft_lstadd_back_cy(t_cys **lst, t_cys *new);
// might be unused
t_cys	*ft_lstlast_cy(t_cys *lst);

//image/
//image/mlx.c
void	setup_mlx(t_mini_rt *rt);
int		handle_close(void *param);
int		handle_keypress(int keycode, void *param);
//image/viewport_00.c
int     viewport_calculation(t_config *cf, t_mini_rt *rt);
void    init_viewport(t_vp *vp);
int	calculate_height(t_config *cf);
int	calculate_width(t_config *cf);
//image/viewport_01.c
int     calculate_viewport_orientation(t_config *cf);
int     calculate_upper_left_corner(t_vp *viewp);
void	get_up_vector(t_config *cf, t_vector *up);
//image/image.c
void	put_pixel(t_img *img, int x, int y, t_color rgb_color);
int		color_map_1(t_visual *vis, t_config *cf, int w, int h);

//hit/
//hit/get_hit.c
int	get_hit(t_config *cf, t_mini_rt *rt, t_ray *ray);
int	rays_loop(t_mini_rt *rt);
//hit/lst_hit.c
void	init_hit(t_hit *hit);
void	update_min(t_hit *min, t_hit *got);
int		fill_hit(char *object, double t, t_ray *ray, t_hit *hit);
//hit/check_plane_00.c
void	check_plane_hit(t_config *cf, t_mini_rt *rt, t_ray *ray);
int	ray_paral_plane(t_ray *ray, t_plane *pl, double *denom, t_mini_rt *rt);
//hit/check_plane_01.c
int	camera_on_the_plane(t_config *cf, t_plane *pl, t_mini_rt *rt);
int	cam_dir_in_plane(t_vector cam_dir, t_vector pl_normal);
//hit/check_sphere_hit.c
void	check_sphere_hit(t_config *cf, t_mini_rt *rt, t_ray *ray);
//hit/check_cylinders_hit.c
int	get_cys_wall_collision(t_mini_rt *rt, t_cys *cy, t_hit *new, t_ray *ray);
int	get_hit_cys(t_mini_rt *rt, t_cys *cy, t_ray *ray);
void	check_cys_hit(t_config *cf, t_mini_rt *rt, t_ray *ray);

//vector_calc.c
int	cross_product(t_vector *a, t_vector *b, t_vector *result);
int	normalize_vector(t_vector *v);
int	point_plus_vector(t_point *point, t_vector *vector, double scalar, t_point *result);
int	scalar_multiply_vector(double scalar, t_vector *vector, t_vector *result);
int	vector_multiply_vector(t_vector *a, t_vector *b, double *result);
int	dot_product(t_vector *a, t_vector *b, double *result); // shorter version of a function above
int	subtract_vectors(t_vector *a, t_vector *b, t_vector *result);
int	point_minus_point(t_point *a, t_point *b, t_vector *result);
int	get_normal(t_vector *v, t_vector *n);

//quadratic_equation.c
int	quadratic_formula_plus(double *args, double *solution, t_mini_rt *rt);
int	quadratic_formula_minus(double *args, double *solution, t_mini_rt *rt);
int	discriminant_check(double A, double B, double C, t_mini_rt *rt);
int get_positive_min(double a, double b, double *c);

//quadratic_cys_helpers.c
int get_A_cylinder(t_vector *d_vertical, double *A, t_mini_rt *rt);
int get_B_cylinder(t_vector *OC_vertical, t_vector *d_vertical, double *B, t_mini_rt *rt);
int get_C_cylinder(t_vector *OC_vertical, double radius, double *C, t_mini_rt *rt);
int get_vertical_parts(t_vector *d_vertical, t_vector *OC_vertical, t_cys *cy, t_ray *ray, t_mini_rt *rt);
int cy_calculate_quadratic_arguments(double *args, t_cys *cy, t_ray *ray, t_mini_rt *rt);

//utils
//utils/cleanup.c
void	clean_exit(t_config *cf, char *er_msg);
void	clean_exit_rt(t_mini_rt *rt, char *er_msg);
int     cleanup_mlx(t_mini_rt *rt);
int     cleanup_cf(t_config *cf);
void	*free_pls(t_plane *pls);
void	*free_sps(t_spher *sps);
void	*free_cys(t_cys *cys);
//utils/error_handling.c
int	display_error(char *msg);
//utils/debugging_prints.c
void	print_triplet(float *triplet);
void	print_vec(t_vector *vec, const char *msg);
void	print_point(t_point *p, const char *msg);
void    print_map(char **map);
void	print_test_config(t_config *cf);
void	print_all_cylider(t_config *cf);
void	print_all_spheres(t_config *cf);
void	print_all_planes(t_config *cf);
void	print_collision(t_col calc);
void	print_viewport(t_vp *vp);
//utils/str_utils.c
void	ft_freestr(char **lst);
int		ft_spacetabchecker(char *input);
void	trim_out_spaces(char **str);
//utils//whitespaces.c
void	whitespace_to_space(char *line);
bool	is_whitespace(char c);
void	skip_whitespace(char *str, int *pos);
//utils/array_utils.c
int		map_len(char **map);

#endif
