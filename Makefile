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
		check_initial.c		\
		config_file.c		\
		debugging_prints.c	\
		error_handling.c 	\
		main.c				\
		parse_delegate.c	\
		parse_helpers.c 	\
		parse_objects.c 	\
		str_utils.c			\
		test_parse_delegate.c 	\
		whitespaces.c 		\
		cleanup.c 			\
		unsorted.c 			\
		lst_struct_cylinder.c \
		lst_struct_plane.c \
		lst_struct_sphere.c )

INCLUDES = inc/miniRT.h
LIBFT_INC = libft/inc/get_next_line.h \
	libft/inc/libft.h

OBJ_DIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT_DIR = libft
LIBFT = libft.a
LIBFT_SRC = $(shell find $(LIBFT_DIR) -name "*.c")#is this allowed cause wildcard?

NAME = miniRT

all: $(MLX_LIB) $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ) $(MLX_LIB)
	@echo "$(GREEN)Compiling $(NAME)... $(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(MLX_LIB)  $(MLX_FLAGS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_SRC) $(LIBFT_INC)
	@echo "$(GREEN)Building $(LIBFT)... $(RESET)"
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(FLAGS) $(OPTIONS) $< -o $@
	@echo "$(BLUE)Compiling... $(CYAN)$<$(RESET)"

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
