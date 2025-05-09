#include "cub3d.h"

int parse_file(const char *path, t_game *game)
{
	int				fd;
	t_map_parser	map_parser;

	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&map_parser, 0, sizeof(t_map_parser));
	map_parser.capacity = 10;
	map_parser.lines = malloc(sizeof(char *) * map_parser.capacity);
	if (!map_parser.lines)
		exit_error("Error\nMemory allocation failed.");
	fd = open(path, O_RDONLY); 
	if (fd < 0)
		exit_error("Error\nCannot open map file.");
	parse_file_content(fd, game, &map_parser);
	close(fd);
	process_map(game, &map_parser);
	free(map_parser.lines);
	return (0);
}

void	parse_file_content(int fd, t_game *game, t_map_parser *map_parser)
{
	char *line;

	while ((line = get_next_line(fd)))
	{
		line = ft_strtrim(line, "\n");
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		parse_line(line, game, map_parser);
	}
	check_elements(game);
	if (map_parser->row_count == 0)
		exit_error("Error\nMap not found in file.");
}

void	check_elements(t_game *game)
{
	if (!game->tex[TEX_NORTH].path || !game->tex[TEX_SOUTH].path || 
		!game->tex[TEX_WEST].path || !game->tex[TEX_EAST].path ||
		game->floor.r < 0 || game->ceiling.r < 0)
		exit_error("Error\nMissing required elements in the map file.");
}

void	init_map_parser(t_map_parser *map_parser)
{
	ft_memset(map_parser, 0, sizeof(t_map_parser));
	map_parser->capacity = 10; // Начальная вместимость
	map_parser->lines = malloc(sizeof(char *) * map_parser->capacity);
	if (!map_parser->lines)
		exit_error("Error\nMemory allocation failed.");
}

void	add_map_line(t_map_parser *map_parser, char *line)
{
	int		i;
	int		new_capacity;
	char	**new_lines;
	
	if (map_parser->row_count >= map_parser->capacity)
	{
		new_capacity = map_parser->capacity * 2;
		new_lines = malloc(sizeof(char *) * new_capacity);
		if (!new_lines)
			exit_error("Error\nMemory allocation failed.");
		i = 0;
		while (i < map_parser->row_count)
		{
			new_lines[i] = map_parser->lines[i];
			i++;
		}
		free(map_parser->lines);
		map_parser->lines = new_lines;
		map_parser->capacity = new_capacity;
	}
	map_parser->lines[map_parser->row_count] = line;
	map_parser->row_count++;
}

void free_map_parser(t_map_parser *map_parser)
{
	int i;
	
	if (!map_parser->lines)
		return ;
	i = 0;
	while (i < map_parser->row_count)
	{
		free(map_parser->lines[i]);
		i++;
	}
	free(map_parser->lines);
	map_parser->lines = NULL;
}

int resize_map_lines_if_needed(t_map_parser *map_parser)
{
	int		i;
	int		new_capacity;
	char	**new_lines;

	if (map_parser->row_count < map_parser->capacity)
		return (0);
	new_capacity = map_parser->capacity * 2;
	new_lines = malloc(sizeof(char *) * new_capacity);
	if (!new_lines)
		return (1);
	i = 0;
	while (i < map_parser->row_count)
	{
		new_lines[i] = map_parser->lines[i];
		i++;
	}
	free(map_parser->lines);
	map_parser->lines = new_lines;
	map_parser->capacity = new_capacity;
	return (0);
}

int	process_map_line(char *line, t_map_parser *map_parser)
{
	map_parser->map_start = 1;
	if (resize_map_lines_if_needed(map_parser))
		return (1);
	map_parser->lines[map_parser->row_count] = line;
	map_parser->row_count++;
	return (0);
}

int process_element_line(char *line, t_game *game)
{
	if (parse_element(line, game) != 0)
		return (1);
	free(line);
	return (0);
}

void parse_line(char *line, t_game *game, t_map_parser *map_parser)
{
	if (ft_isdigit(line[0]) || line[0] == ' ')
	{
		if (process_map_line(line, map_parser))
		{
			free(line);
			exit_error("Error\nMemory allocation failed.");
		}
	}
	else if (!map_parser->map_start)
	{
		if (process_element_line(line, game))
		{
			free(line);
			exit_error("Error\nInvalid element in map file.");
		}
	}
	else
	{
		free(line);
		exit_error("Error\nMap must be at the end of the file.");
	}
}
