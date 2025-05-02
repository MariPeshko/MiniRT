BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
RESET   = \033[0m

CC = cc
FLAGS = -Wall -Wextra -Werror -g -Iinc -I./minilibx-linux
OPTIONS = -c

MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L/usr/lib/X11 -lXext -lX11

SRC_DIR = ./src
#add *.c files here
SRC = $(addprefix $(SRC_DIR)/,\
		main.c				\
		/parsing/check_initial.c \
		/parsing/config_file.c \
		/parsing/parse_delegate.c	\
		/parsing/parse_objects.c 	\
		/parsing/parse_rgb.c	\
		/parsing/parse_helpers.c 	\
		/parsing/lst_struct_plane.c \
		/parsing/lst_struct_sphere.c \
		/parsing/lst_struct_cylinder.c \
		/hit/get_hit.c	\
		/hit/lst_hit.c	\
		/hit/check_cylinders.c 	\
		/hit/check_plane_00.c 	\
		/hit/check_plane_01.c 	\
		/hit/check_sphere_hits.c \
		/hit/cylinder_wall.c\
		/color/color.c \
		/color/color_pl.c\
		/color/color_sp.c\
		/color/color_helpers.c\
		/color/color_cy.c\
		/image/image.c	\
		/image/mlx.c \
		/image/viewport_00.c \
		/image/viewport_01.c \
		/utils/cleanup.c \
		/utils/str_utils.c	\
		/utils/whitespaces.c	\
		/utils/debugging_prints.c \
		/utils/error_handling.c \
		/utils/array_utils.c \
		vector_calc.c 		\
		vector_calc_bon.c	\
		quadratic_equation.c \
		cys_quadratic_helpers.c\
		)

INCLUDES = inc/miniRT.h inc/miniRT_structs.h inc/miniRT_error_macro.h
LIBFT_INC = libft/inc/get_next_line.h \
	libft/inc/libft.h

OBJ_DIR = ./obj
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = libft
LIBFT_SRC_DIR = libft/src
LIBFT = libft.a
LIBFT_SRC = $(addprefix $(LIBFT_SRC_DIR)/, \
	libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c \
	libft/ft_isdigit.c libft/ft_isprint.c libft/ft_itoa.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_memcpy.c \
	libft/ft_memmove.c libft/ft_memset.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putstr_fd.c \
	libft/ft_putnbr_fd.c libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlcat.c \
	libft/ft_strlcpy.c libft/ft_strlen.c libft/ft_strmapi.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strrchr.c \
	libft/ft_striteri.c libft/ft_strtrim.c libft/ft_substr.c libft/ft_tolower.c libft/ft_toupper.c \
	libft/ft_lstnew_bonus.c libft/ft_lstadd_front_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c \
	libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstclear_bonus.c \
	libft/ft_lstiter_bonus.c libft/ft_lstmap_bonus.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c)


NAME = miniRT

all: $(MLX_LIB) $(NAME) 

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ) $(MLX_LIB) $(INCLUDES)
	@echo "$(GREEN)Compiling $(NAME)... $(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(MLX_LIB) $(MLX_FLAGS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME) -lm

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_SRC) $(LIBFT_INC)
	@echo "$(GREEN)Building $(LIBFT)... $(RESET)"
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: src/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@$(CC) -g $(FLAGS) $(OPTIONS) $< -o $@
	@echo "$(BLUE)Compiling... $(CYAN)$<$(RESET)"

# The mkdir -p $(OBJ_DIR) command in your Makefile only 
# creates the obj/ directory, but not its subdirectories.

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
#	@mkdir -p $(OBJ_DIR)
#	@$(CC) -g $(FLAGS) $(OPTIONS) $< -o $@
#	@echo "$(BLUE)Compiling... $(CYAN)$<$(RESET)"

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	@printf "$(MAGENTA)"
	@$(MAKE) -C $(MLX_DIR) clean
	@make clean -s -C $(LIBFT_DIR)
	@echo "$(RED)Deleting Objects... $(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(RESET)"

fclean: clean
	@printf "$(MAGENTA)"
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Deleting $(NAME)... $(RESET)"
	@rm -f $(NAME)
	@printf "$(RESET)"

re: fclean all

.PHONY: all re clean fclean libs debug
