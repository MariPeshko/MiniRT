/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_error_macro.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeshko <mpeshko@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:15:50 by sgramsch          #+#    #+#             */
/*   Updated: 2025/04/28 14:39:32 by mpeshko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_ERROR_MACRO_H
# define MINIRT_ERROR_MACRO_H

//memory
# define MEMORY "Memory allocation failed"
# define CALLOC "Calloc: Memory allocation error"

//MLX related
# define MLX_INIT "Mlx init failed"
# define MLX_WIN_INIT "Mlx window init failed"
# define MLX_IMG_INIT "Mlx image init failed"

//config file given
# define NO_CONFIG_FILE "Run a program with a configuration \
file as follows:\n./miniRT [name_of_the_file].rt"
# define TOO_MANY_ARGS "Too many arguments"
# define EMPTY_STRING "Argument is an empty string\nEnter the \
name of the configuration file"
# define WRONG_EXTEN "Wrong extention. File must be in .rt format"
# define FILE_ERR "Error opening file"

//config file content
# define EMPTY_FILE "Configuration file is empty"

# define TOO_MANY_AMB "Must be maximum one ambient light"
# define TOO_MANY_CAM "Must be maximum one camera"
# define TOO_MANY_LIT "Must be maximum one light spot in mandatory part"
# define MUST_ONE_AMB "There must be an ambient light"
# define MUST_ONE_CAM "There must be a camera"
# define MUST_ONE_LIT "There must be a lighting spot"
# define WRONG_IDENTIFIER "Invalid Identifier"

# define INVALID_NBR_ARG "Invalid number of Arguments"
# define INVALID_NBR_ARG_CY "Invalid number of Arguments in cylinder"
# define INVALID_NBR_ARG_PL "Invalid number of Arguments in plane"
# define INVALID_NBR_ARG_SP "Invalid number of Arguments in sphere"

# define WRONG_CHAR "unexpected character"
# define RGB_WRONG_CHAR "unexpected character in RGB"
# define RGB_NEG "RGB value must be a positive integer"
# define RGB_SCOPE "RGB value out of scope"
# define A_SCOPE "Ambient light ratio out of scope"
# define NV_SCOPE "Normalized Vector out of Scope [0.0, 1.0]"
# define NV_ZEROS "A direction vector cannot be 0,0,0"
# define SP_DIAMETER_SCOPE "Sphere diameter out of scope"
# define CY_DIAMETER_SCOPE "Cylinder diameter out of scope"
# define FOV_SCOPE "Field of View out of scope [0, 180]"

// calculation
# define CALC "Calculations failed."//over and underflow, isnan and isinf. 
# define CALC_CYL_PMP "Cylinder calculation failed. Point minus point."
# define CALC_CYL_PPV "Cylinder calculation failed. Point plus vector."
# define CALC_CYL_VMV "Cylinder calculation failed. Vector multiply vector."
# define CALC_CYL_QU "Cylinder calculation failed. Calculate_quadratic_arguments()."
# define CALC_CYL_DIS "Cylinder calculation failed. Discriminant()."
# define CALC_CYL_QFP "Cylinder calculation failed. Quadratic_formula_plus. line: isnan(res) || isinf(res)"
# define VIEWP_C "Viewport Center calculation failed."

//errors for camera at invalid position
# define C_IN_SP "Camera in the surphace of a Sphere."
# define C_IN_CY_W "Camera in the Wall of a Cylinder."
# define C_IN_CY "Camera in the surphace of a Cylinder."
# define CAM_ON_PLANE "Camera is embedded in the plane."
# define CAM_DIR_ON_PLANE "Warning! The camera's direction \
is exactly in the plane."

//new
# define CALC_CB "Cylinder Bottom Hit calculation failed."
# define CALC_CT "Cylinder top Hit calculation failed."
# define CALC_CW "Cylinder WALL Hit calculation failed."

//Places
# define V_L_CY "vector_length_cy"
# define P_P_V "point_plus_vector"
# define V_M_V "vector_multiply_vector"
# define P_M_P "point_minus_point"
# define G_H_C "get_hit_cys"
# define D_P "dot_product"
# define G_H_P "get_hit_plane"
# define G_P_N "get_plane_numerator"
# define F_H "fill_hit"
# define C_P_H ""
# define G_H_S "get_hit_sphere"
# define G_R "get_ray"
# define C_O_P "collision_on_plane"
# define G_C_P "get_colors_plane"
# define G_C_S "get_colors_sphere"
# define G_C_C "get_colors_cylinder"
# define I_L "in_light"
# define G_R_C "get_ray_color"
# define C_H_N "calculate_hit_normal"
#endif
