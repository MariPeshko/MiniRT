#ifndef MINIRT_ERRROR_MACRO_H
# define MINIRT_ERRROR_MACRO_H

# define MEMORY "Memory allocation failed."
# define INVALID_NBR_ARG "Invalid number of Arguments."
# define WRONG_CHAR "unexpected character."
# define RGB_SCOPE "RGB value out of scope."
# define WRONG_IDENTIFIER "Invalid Identifier."
# define A_SCOPE "Ambient light ratio out of scope."
# define NV_SCOPE "normalized Vector out of Scope [0.0, 1.0]"
# define SP_DIAMETER_SCOPE "Sphere diameter out of scope."
# define CY_DIAMETER_SCOPE "Cylinder diameter out of scope."
# define CALLOC "Calloc: Memory allocation error."

# define NO_CONFIG_FILE "Run a program with a configuration file as follows:\n./miniRT [name_of_the_file].rt\n"
# define TOO_MANY_ARGS "Too many arguments.\n"
# define EMPTY_STRING "Argument is an empty string.\nEnter the name of the configuration file.\n"
# define WRONG_EXTEN "Wrong extention. File must be in .rt format.\n"
# define FILE_ERR "Error opening file.\n"
# define EMPTY_FILE "Configuration file is empty.\n"
# define FOV_SCOPE "Field of View out of scope [0, 180]."

#endif