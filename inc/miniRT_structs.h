#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

typedef struct s_vector
{
}	t_vector;

typedef struct s_point
{
}	t_point;

typedef struct s_camera
{

} s_camera ;

/*
	Ambient lighting ratio in range [0.0,1.0].
*/
typedef struct s_ambient
{
	double	lighting_ratio;
}	s_ambient ;

typedef struct s_light
{
	/* data */
}	s_light ;

typedef struct s_planes
{
	struct s_planes	*next;
}	s_planes ;

typedef struct s_spheres
{
	/* data */
	struct s_spheres	*next;
}	s_spheres ;

typedef struct s_cylinders
{
	struct s_cylinders	*next;
}	s_cylinders ;

// Structure to store all information from a config file .rt
typedef struct s_config
{
	s_ambient	amb;
	s_camera	cam;
	s_light		light;
	s_planes	*pl;
	s_spheres	*sp; // linked list
	s_cylinders	*cy; // linked list
}	s_config ;

typedef struct mini_rt
{
	s_config	cf;
	// rest of the structs
} mini_rt ;

#endif
