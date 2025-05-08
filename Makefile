NAME = cub3D

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCL_DIR = include
LIBFT_DIR = lib/libft
MLX_DIR_MACOS = lib/mlx_opengl
MLX_DIR_LINUX = lib/mlx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Sources and objects
SRCS = src/parser/main.c src/parser/parse_file.c src/parser/parse_map.c src/parser/parse_elements.c src/utils/exit.c
OBJS = $(SRCS:src/%.c=$(OBJ_DIR)/%.o)

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCL_DIR) -I$(LIBFT_DIR)/include -I$(MLX_DIR)

# Platform detection
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLX_DIR = lib/mlx_opengl
	MLX = $(MLX_DIR)/libmlx.a -framework OpenGL -framework AppKit
else
	MLX_DIR = lib/mlx-linux
	MLX = $(MLX_DIR)/libmlx.a -lXext -lX11 -lm -lz
endif

# Build object files
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@mkdir -p $(OBJ_DIR)/parser $(OBJ_DIR)/utils
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) re

$(MLX):
	make -C $(MLX_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
