/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:07:52 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/12 16:17:04 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_color	adjusted; // color * light_ratio
}	t_ambient;

/*the light brightness ratio in range [0.0,1.0]
(unused in mandatory part)R,G,B colors in range [0-255]*/
typedef struct s_light
{
	t_point		point;
	double		bright;
	t_color		col;
}	t_light;

// Plane Normal is a vector that is perpendicular to the entire plane 
// id strts from 1
typedef struct s_plane
{
	t_point			point;
	t_vector		pl_normal;
	t_color			col;
	int				id;
	struct s_plane	*next;
}	t_plane;

// Sphere(s)
// id strts from 1
typedef struct t_spher
{
	t_point				point;
	double				diam;
	t_color				col;
	int					id;
	struct t_spher	*next;
}	t_spher;

// Cylinder(s)
// id strts from 1
typedef struct s_cys
{
	t_point			point;
	t_vector		norm_vec;
	double			diam;
	double			height;
	t_color			col;
	int				id;
	struct s_cys	*next;
}	t_cys;

/**
 * view port
 * horizontal - pointing right from the camera's perspective
 * @param upperleft - upper-left corner aka first pixel
*/
typedef struct s_vp
{
	t_point		upperleft;
	t_vector	horizontal;//from one pixel to next in row
	t_vector	vertical;//from one pixel to next in column
	double		width;
	double		height;
	t_point		vp_center;
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
	t_vp		viewp;
	//void		*mlx;
	//void		*win;
	bool		valid;
	bool		one_amb;
	bool		one_cam;
	bool		one_lit;
}	t_config;

/*
struct that saves a single instance of a collision (intersection).
type: Object type (e.g., "NONE", "PLANE", "CYLINDER", "SPHERE")
distance: Distance from the ray origin to the intersection point.
Purpose: Finding the closest intersection and not only this.
point: Coordinates of the intersection point.
*/
typedef struct	s_hit
{
	char	*type;
	int		id;
	double	distance;
	t_point	point;
}	t_hit;

// c - camera position as the origin of the ray
typedef struct s_ray
{
	t_vector	v_dir;
	t_point		c;
}	t_ray;

// This struct tracks the intersection data for a single ray.
// Col refers to the collision calculations
//
// min - The closest intersection (hit) found so far. At 
// 		  the end of calculations,the one that is visible 
//		  at this pixel.
// got - Current intersection being processed. This is 
// 		 a temporary variable used to compare intersections.
// pixel - Pixel on the screen corresponding to this ray
// t1 	 - the closest distance from cam to a hit
// t2    - same for second hit (spheres, cylinders)
typedef struct s_col
{
	t_hit	min;
	t_hit	got;
	t_ray	ray;
	t_point	pixel;
	double	quadratic_args[3];
	double	t1;
	double	t2;
	t_color	hit_color;
}	t_col;//col = collisions calculations

// a pointer to the image (returned by mlx_new_image)
// a pointer to the image data buffer (from mlx_get_data_addr)
// some metadata to help you access pixels properly 
// (like bits per pixel, endian, line size)
// line_len - size of a line in bytes, Each row of image 
// memory may have padding, 
// this tells you the actual byte width.
// endian - Controls how to write multi-byte colors correctly.
// 0: little endian, 1: big endian
// width and height (to help your raytracer with resolution)
typedef struct s_img
{
	void	*img_ptr;   // pointer to MLX image (from mlx_new_image)
	char	*data;      // address of image data (from mlx_get_data_addr)
	int		width;      // image width
	int		height;     // image height
	int		bpp;        // bits per pixel. Needed to calculate how to write a pixel.
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_color_calc
{
	t_plane *pl;
	t_spher *sp;
	t_cys	*cy;
	t_ambient	A;
	t_light	L;
	t_vector	hit_n;
	t_ray	r_shadow;
	double		tmp;
}	t_color_calc;

typedef struct s_visual
{
	void		*mlx;
	void		*win;
	t_img		img;
	int			width;
	int			height;
	//t_viewp 	vp?
}	t_visual;

typedef struct s_mini_rt
{
	t_config	cf;
	t_col		calc;
	t_color_calc coca;
	t_visual	visual;
	// rest of the structs
}	t_mini_rt;

#endif
