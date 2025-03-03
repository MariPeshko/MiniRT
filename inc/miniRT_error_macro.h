#ifndef MINIRT_ERROR_MACRO_H
# define MINIRT_ERROR_MACRO_H

# define VIEWPORT_RATIO (16.0 / 9.0)
# define VIEWPORT_RATIO_REVERSE (9.0 / 16.0)

# define MEMORY "Memory allocation failed"
# define INVALID_NBR_ARG "Invalid number of Arguments"
# define INVALID_NBR_ARG_CY "Invalid number of Arguments in cylinder"
# define INVALID_NBR_ARG_PL "Invalid number of Arguments in plane"
# define INVALID_NBR_ARG_SP "Invalid number of Arguments in sphere"
# define TOO_MANY_AMB "Must be maximum one ambient light"
# define TOO_MANY_CAM "Must be maximum one camera"
# define TOO_MANY_LIT "Must be maximum one light spot in mandatory part"
# define MUST_ONE_AMB "There must be an ambient light"
# define MUST_ONE_CAM "There must be a camera"
# define MUST_ONE_LIT "There must be a lighting spot"
# define WRONG_CHAR "unexpected character"
# define RGB_WRONG_CHAR "unexpected character in RGB"
# define RGB_NEG "RGB value must be a positive integer"
# define RGB_SCOPE "RGB value out of scope"
# define WRONG_IDENTIFIER "Invalid Identifier"
# define A_SCOPE "Ambient light ratio out of scope"
# define NV_SCOPE "Normalized Vector out of Scope [0.0, 1.0]"
# define NV_ZEROS "A direction vector could not be 0,0,0"
# define SP_DIAMETER_SCOPE "Sphere diameter out of scope"
# define CY_DIAMETER_SCOPE "Cylinder diameter out of scope"
# define CALLOC "Calloc: Memory allocation error"

# define NO_CONFIG_FILE "Run a program with a configuration \
file as follows:\n./miniRT [name_of_the_file].rt"
# define TOO_MANY_ARGS "Too many arguments"
# define EMPTY_STRING "Argument is an empty string\nEnter the \
name of the configuration file"
# define WRONG_EXTEN "Wrong extention. File must be in .rt format"
# define FILE_ERR "Error opening file"
# define EMPTY_FILE "Configuration file is empty"
# define FOV_SCOPE "Field of View out of scope [0, 180]"

# define VIEWP_C "Viewport Center calculation failed."

#endif
