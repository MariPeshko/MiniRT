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
FLAGS = -Wall -Wextra -Werror -g
OPTIONS = -c

SRC_DIR = ./src
#add *.c files here
SRC = $(addprefix $(SRC_DIR)/,\
	main.c				\
	config_file.c		\
	str_utils.c	)

##SRC_DIR = ./src
##SRC_FILES = empty_one.c empty_two.c

INCLUDES = inc/miniRT.h

OBJ_DIR = ./obj
#OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT_DIR = libft
LIBFT = libft.a
LIBFT_SRC = $(shell find $(LIBFT_DIR) -name "*.c")

NAME = miniRT

all:  $(NAME)

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJ) 
	@echo "$(GREEN)Compiling $(NAME)... $(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_SRC)
	@echo "$(GREEN)Building $(LIBFT)... $(RESET)"
	@make -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(FLAGS) $(OPTIONS) $< -o $@
	@echo "$(BLUE)Compiling... $(CYAN)$<$(RESET)"

clean:
	@printf "$(MAGENTA)"
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
