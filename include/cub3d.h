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

#ifdef __APPLE__
    #define MLX_MACOS
    #include <mlx.h>
#elif defined(__linux__)
    #define MLX_LINUX
    #include <mlx.h>
#endif

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

#ifdef MLX_MACOS
    // macOS keycodes
    #define KEY_W 13
    #define KEY_A 0
    #define KEY_S 1
    #define KEY_D 2
    #define KEY_ESC 53
#else
    // Linux keycodes
    #define KEY_W 119
    #define KEY_A 97
    #define KEY_S 115
    #define KEY_D 100
    #define KEY_ESC 65307
#endif

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3

// Структура для хранения строк карты во время парсинга
typedef struct s_map_parser {
    char    **lines;      // массив строк карты
    int     row_count;    // количество строк
    int     map_start;    // флаг начала карты
	int     capacity;
} t_map_parser;

// Структура для посещенных клеток при алгоритме flood fill
typedef struct s_visited {
    int     **array;      // двумерный массив посещенных клеток
    int     height;       // высота массива
    int     width;        // ширина массива
} t_visited;

// Структура для обработки цвета RGB при парсинге
typedef struct s_rgb_parser {
    char    **parts;      // массив частей RGB
    char    *r_str;       // строка для красного компонента
    char    *g_str;       // строка для зеленого компонента
    char    *b_str;       // строка для синего компонента
} t_rgb_parser;

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

/*int parse_file(const char *path, t_game *game);
void free_game(t_game *game);
void exit_error(const char *msg);
int parse_element(char *line, t_game *game);
int	parse_map(int fd, t_game *game);
int parse_color(const char *line, t_color *color);
void parse_map_from_grid(t_game *game);
int is_wall_line(char *line);
void check_map_surrounded_by_walls(t_game *game);
void validate_map_characters(t_game *game);
//void validate_map_walls(t_game *game);
void validate_map_walls_dfs(t_game *game);
void dfs_check(t_game *game, int **visited, int x, int y);
int dfs_player_area(t_game *game, int **visited, int x, int y);
void validate_player_enclosed(t_game *game);*/

// Функции для парсинга файла
void parse_file_content(int fd, t_game *game, t_map_parser *map_parser);
void parse_line(char *line, t_game *game, t_map_parser *map_parser);
void check_elements(t_game *game);
int parse_file(const char *path, t_game *game);
void init_map_parser(t_map_parser *map_parser);
void add_map_line(t_map_parser *map_parser, char *line);

// Функции для обработки карты
void process_map(t_game *game, t_map_parser *map_parser);
int find_max_width(t_map_parser *map_parser);
void fill_map_grid(t_game *game, t_map_parser *map_parser, int max_width);
void allocate_map_grid(t_game *game);

// Функции для валидации карты
void validate_map(t_game *game);
void validate_character(char c, int *player_count);
void validate_player_count(int player_count);
int is_player_position(t_game *game, int y, int x);
void set_player_position(t_game *game, int y, int x, char direction);
void validate_map_characters(t_game *game);
void find_player_position(t_game *game);

// Функции для проверки окружения карты стенами
void init_visited(t_visited *visited, t_game *game);
void check_visited_cells(t_game *game, t_visited *visited);
void check_map_edges(t_game *game);
void check_empty_space_borders(t_game *game);
void check_cell_borders(t_game *game, int y, int x);
void free_visited(t_visited *visited);
void flood_fill(t_game *game, t_visited *visited, int x, int y);
void check_map_surrounded_by_walls(t_game *game);

// Функции для парсинга элементов
int parse_texture(char *line, t_game *game);
int parse_color_element(char *line, t_game *game);
int check_rgb_parts(t_rgb_parser *rgb_parser);
int parse_rgb_values(t_rgb_parser *rgb_parser, t_color *color);
int validate_digit_string(char *str);
void free_rgb_parts(t_rgb_parser *rgb_parser);
int validate_color_range(t_color *color);
int parse_element(char *line, t_game *game);
int parse_color(const char *line, t_color *color);

// Вспомогательные функции
void free_textures(t_game *game);
void free_map_grid(t_game *game);
void free_game(t_game *game);
void exit_error(const char *msg);


#endif
