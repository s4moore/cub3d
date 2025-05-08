# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samoore <samoore@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 12:24:04 by samoore           #+#    #+#              #
#    Updated: 2025/05/08 13:36:11 by samoore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


INC_DIR = includes/
SRC_DIR = src/
OBJ_DIR = objects/

SRC_FILES = main.c
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_FILES))

CC = gcc
CC_COMP_FLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -g3 -Imlx
CC_LINK_FLAGS = -L$(INC_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz
NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $^ $(CC_LINK_FLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CC_COMP_FLAGS) -c $< -o $@

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re