#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3

typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

typedef struct s_texture {
	char *path;
	void *img;
	char *addr;
	int width;
	int height;
	int bpp;
	int line_len;
	int endian;
} t_texture;

typedef struct s_map {
	char **grid;
	int width;
	int height;
} t_map;

typedef struct s_player {
	double x;
	double y;
	double dir_x;
	double dir_y;
} t_player;

typedef struct s_game {
	void *mlx;
	void *win;
	t_texture tex[4];
	t_color floor;
	t_color ceiling;
	t_map map;
	t_player player;
} t_game;

int parse_file(const char *path, t_game *game);
void free_game(t_game *game);
void exit_error(const char *msg);
int parse_element(char *line, t_game *game);
int	parse_map(int fd, t_game *game);
int parse_color(const char *line, t_color *color);
void parse_map_from_grid(t_game *game);

#endif
