# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgramsch <sgramsch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 10:34:54 by sgramsch          #+#    #+#              #
#    Updated: 2024/03/28 11:06:46 by sgramsch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
CFLAGS = -Wall -Wextra -Werror -g3
OPTIONS = -c
#-g3 makes debugging easier

GNL_DIR = get_next_line
GNL_SRC = $(addprefix $(GNL_DIR)/, \
		get_next_line.c get_next_line_utils.c)

FT_PRINTF_DIR = ft_printf
FT_PRINTF_SRC = $(addprefix $(FT_PRINTF_DIR)/, \
		ft_printf.c ft_printf_put.c)

LIBFT_DIR = libft
LIBFT_SRC = $(addprefix $(LIBFT_DIR)/, \
		ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
		ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
		ft_putnbr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_striteri.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c )

SRC_DIR = ./src
TOTAL_SRC = $(addprefix $(SRC_DIR)/, \
		$(LIBFT_SRC) $(GNL_SRC) $(FT_PRINTF_SRC))

OBJ_DIR = ./obj
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(TOTAL_SRC))

INCLUDES = inc/libft_gnl_printf.h inc/ft_printf.h inc/get_next_line.h  inc/libft.h

NAME = libft.a

##############################

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@printf "$(GREEN)$(NAME) created$(RESET)\n"
	@printf "$(MAGENTA)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/$(GNL_DIR)
	@mkdir -p $(OBJ_DIR)/$(FT_PRINTF_DIR)
	@mkdir -p $(OBJ_DIR)/$(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OPTIONS) $< -o $@
	@printf "$(BLUE)Compiling...$(CYAN) $<$(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)Libft Objects removed$(RESET)\n"
	@printf "$(MAGENTA)"
	
fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)$(NAME) removed$(RESET)\n"
	@printf "$(MAGENTA)"

re: fclean all

.PHONY: all clean fclean re bonus
