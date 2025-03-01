#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

// x,y,z coordinates
typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

// R,G,B colors in range [0-255]: 255, 255, 255
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

// Second parameter - 3d normalized orientation vector.
// In range [-1,1] for each x,y,z axis.
typedef struct s_camera
{
	t_point		point;
	t_vector	norm_vec;
	double		fov;
}	t_camera;

/*Ambient lighting ratio in range [0.0,1.0].*/
typedef struct s_ambient
{
	double	lighting_ratio;
	t_color	col;
}	t_ambient;

/*the light brightness ratio in range [0.0,1.0]
(unused in mandatory part)R,G,B colors in range [0-255]*/
typedef struct s_light
{
	t_point		point;
	double		bright;
	t_color		col;
}	t_light;

typedef struct s_plane
{
	t_point			point;
	t_vector		norm_vec;
	t_color			col;
	int				id; // identifier
	struct s_plane	*next;
}	t_plane;

typedef struct t_spher
{
	t_point				point;
	double				diam;
	t_color				col;
	int					id; // identifier
	struct t_spher	*next;
}	t_spher;

// Cylinder(s)
typedef struct s_cys
{
	t_point			point;
	t_vector		norm_vec;
	double			diam;
	double			height;
	t_color			col;
	int				id; // identifier
	struct s_cys	*next;
}	t_cys;

typedef struct s_vp//view port
{
	t_point	point;
	t_vector	horizontal;
	t_vector	vertical;
	int			width;
	int			height;//both in pixel
	t_point		c_point;//easier access to C point?
}	t_vp;

// Structure to store all information from a config file .rt
typedef struct s_config
{
	t_ambient	amb;
	t_camera	cam;
	t_light		light;
	t_plane		*pl;
	t_spher		*sp;
	t_cys		*cy;
	void	*mlx;
	void	*win;
	bool		valid;
	bool		one_amb;
	bool		one_cam;
	bool		one_lit;
}	t_config;

typedef struct s_mini_rt
{
	t_config	cf;
	
	// rest of the structs
}	t_mini_rt;

#endif
