#include "cub3d.h"

void	validate_map(t_game *game) // initiates the map validation process.
{
	validate_map_characters(game);
	find_player_position(game);
	check_map_surrounded_by_walls(game);
}

void validate_map_characters(t_game *game)
{
	int	y;
	int	x;
	int	player_count;
    
	y = 0;
	player_count = 0;
	while (y < game->map.height) //iterates through each character in the map
	{
		x = 0;
		while (x < game->map.width)
		{
			validate_character(game->map.grid[y][x], &player_count);
			x++;
		}
		y++;
	}
	validate_player_count(player_count);
}

void	validate_character(char c, int *player_count) //Verifies that each character is valid
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ')
		exit_error("Error\nInvalid character in map.");
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*player_count)++;
}

void	validate_player_count(int player_count)
{
	if (player_count == 0)
		exit_error("Error\nNo player starting position found.");
	if (player_count > 1)
		exit_error("Error\nMultiple player starting positions found.");
}

void	find_player_position(t_game *game)
{
	int	y;
    int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (is_player_position(game, y, x))
				return ;
			x++;
		}
		y++;
	}
}

int	is_player_position(t_game *game, int y, int x)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		set_player_position(game, y, x, c);
		game->map.grid[y][x] = '0';
		return (1);
	}
	return (0);
}

void	set_player_position(t_game *game, int y, int x, char direction)
{
	game->player.x = x + 0.5;
	game->player.y = y + 0.5;
	if (direction == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
	}
	else if (direction == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
	}
}
