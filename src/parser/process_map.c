#include "cub3d.h"

void	process_map(t_game *game, t_map_parser *map_parser)
{
	int max_width;

	max_width = find_max_width(map_parser);
	game->map.width = max_width;
	game->map.height = map_parser->row_count;
	allocate_map_grid(game);
	fill_map_grid(game, map_parser, max_width);
	validate_map(game);
}

int	find_max_width(t_map_parser *map_parser)
{
	int	i;
	int	len;
	int max_width;

	i = 0;
	max_width = 0;
	while (i < map_parser->row_count)
	{
		len = ft_strlen(map_parser->lines[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

void	allocate_map_grid(t_game *game)
{
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		exit_error("Error\nMemory allocation failed.");
}

void	fill_map_grid(t_game *game, t_map_parser *map_parser, int max_width)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(max_width + 1);
		if (!game->map.grid[i])
			exit_error("Error\nMemory allocation failed.");
		ft_memset(game->map.grid[i], ' ', max_width);
		ft_memcpy(game->map.grid[i], map_parser->lines[i], ft_strlen(map_parser->lines[i]));
		game->map.grid[i][max_width] = '\0';
		free(map_parser->lines[i]);
		i++;
	}
	game->map.grid[game->map.height] = NULL;
}
