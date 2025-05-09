#include "cub3d.h"

void check_map_surrounded_by_walls(t_game *game)
{
	t_visited	visited;

	init_visited(&visited, game);
	flood_fill(game, &visited, (int)game->player.x, (int)game->player.y);
	check_visited_cells(game, &visited);
	check_map_edges(game);
	check_empty_space_borders(game);
	free_visited(&visited);
}

void	init_visited(t_visited *visited, t_game *game)
{
	int	y;
	int	x;

	visited->height = game->map.height;
	visited->width = game->map.width;
	visited->array = malloc(sizeof(int *) * visited->height);
	if (!visited->array)
		exit_error("Error\nMemory allocation failed.");
	y = 0;
	while (y < visited->height)
	{
		visited->array[y] = malloc(sizeof(int) * visited->width);
		if (!visited->array[y])
			exit_error("Error\nMemory allocation failed.");
		x = 0;
		while (x < visited->width)
		{
			visited->array[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	flood_fill(t_game *game, t_visited *visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= visited->width || y >= visited->height)
		return ;
	if (visited->array[y][x] || game->map.grid[y][x] == '1' || game->map.grid[y][x] == ' ')
		return ;
	visited->array[y][x] = 1;
	flood_fill(game, visited, x + 1, y);
	flood_fill(game, visited, x - 1, y);
	flood_fill(game, visited, x, y + 1);
	flood_fill(game, visited, x, y - 1);
}

void	check_visited_cells(t_game *game, t_visited *visited)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '0' && !visited->array[y][x])
				exit_error("Error\nMap must be surrounded by walls.");
			x++;
		}
		y++;
	}
}

void	check_map_edges(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		if (y == 0 || y == game->map.height - 1)
		{
			x = 0;
			while (x < game->map.width)
			{
				if (game->map.grid[y][x] == '0')
					exit_error("Error\nMap must be surrounded by walls.");
				x++;
			}
		}
		else
		{
			if (game->map.grid[y][0] == '0' || game->map.grid[y][game->map.width - 1] == '0')
				exit_error("Error\nMap must be surrounded by walls.");
		}
		y++;
	}
}

void	check_empty_space_borders(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == '0')
				check_cell_borders(game, y, x);
			x++;
		}
		y++;
	}
}

void	check_cell_borders(t_game *game, int y, int x)
{
	if ((y > 0 && game->map.grid[y-1][x] == ' ') ||
		(y < game->map.height - 1 && game->map.grid[y+1][x] == ' ') ||
		(x > 0 && game->map.grid[y][x-1] == ' ') ||
		(x < game->map.width - 1 && game->map.grid[y][x+1] == ' '))
		exit_error("Error\nEmpty space must be surrounded by walls.");
}

void	free_visited(t_visited *visited)
{
	int	y;
	
	y = 0;
	while (y < visited->height)
	{
		free(visited->array[y]);
		y++;
	}
	free(visited->array);
}
