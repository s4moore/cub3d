# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samoore <samoore@student.42london.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 12:24:04 by samoore           #+#    #+#              #
#    Updated: 2025/05/09 11:19:28 by samoore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


INC_DIR = includes/
SRC_DIR = src/
OBJ_DIR = objects/

SRC_FILES = main.c
OBJ_FILES = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_FILES))

CC = gcc
CC_COMP_FLAGS = -w -Wall -Werror -Wextra -I$(INC_DIR) -Imlx -g3
CC_LINK_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CC_LINK_FLAGS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CC_COMP_FLAGS) -c $< -o $@

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re