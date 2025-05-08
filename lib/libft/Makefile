# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssukhova <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 17:24:33 by ssukhova          #+#    #+#              #
#    Updated: 2023/11/20 20:23:54 by ssukhova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = libft.a

BUILD_DIR = obj
SRC_DIR = src
INCLUDE_DIR = include

INCLUDE_FLAGS = -I./$(INCLUDE_DIR)
COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -fPIC -fPIE $(INCLUDE_FLAGS) -g3 -gdwarf-3

SRC_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
  ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
  ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
  ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
  ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
  ft_substr.c ft_tolower.c ft_toupper.c ft_printf.c ft_printf_utils1.c \
  ft_printf_utils2.c get_next_line.c

SOURCES = $(SRC_FILES:%.c=$(SRC_DIR)/%.c)
BUILD_OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(BUILD_DIR):
	mkdir -pv $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(BUILD_OBJS)
	ar rc $(NAME) $(BUILD_OBJS)

$(NAME): $(BUILD_DIR) $(BUILD_OBJS)
	ar rc $(NAME) $(BUILD_OBJS)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
