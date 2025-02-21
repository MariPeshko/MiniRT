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
typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
}	s_color ;

// Second parameter - 3d normalized orientation vector.
// In range [-1,1] for each x,y,z axis.
typedef struct s_camera
{
	t_point		point;
	t_vector	norm_vec;
	double		fov; 
}	s_camera ;

/*
	Ambient lighting ratio in range [0.0,1.0].
*/
typedef struct s_ambient
{
	double	lighting_ratio;
	s_color	col;
}	s_ambient ;

// the light brightness ratio in range [0.0,1.0]
// (unused in mandatory part)R,G,B colors in range [0-255]
typedef struct s_light
{
	t_point		point;
	double		bright;
	s_color		col;
}	s_light ;

typedef struct s_planes
{
	t_point		point;
	t_vector	norm_vec;
	s_color		col;
	int			id; // identifier
	struct s_planes	*next;
}	s_planes ;

typedef struct s_spheres
{
	t_point		point;
	double		diam;
	s_color		col;
	int			id; // identifier
	struct s_spheres	*next;
}	s_spheres ;

// Cylinder(s)
typedef struct s_cys
{
	t_point		point;
	t_vector	norm_vec;
	double		diam;
	double		height;
	s_color		col;
	int			id; // identifier
	struct s_cys	*next;
}	s_cys ;

// Structure to store all information from a config file .rt
typedef struct s_config
{
	s_ambient	amb;
	s_camera	cam;
	s_light		light;
	s_planes	*pl; // linked list
	s_spheres	*sp; // linked list
	s_cys		*cy; // linked list
	// flags
}	s_config ;

typedef struct mini_rt
{
	s_config	cf;
	// rest of the structs
} mini_rt ;

#endif
