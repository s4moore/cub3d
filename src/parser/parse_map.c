#include "cub3d.h"

// Function to set the player's position and direction
static void set_player(t_game *game, int x, int y, char dir)
{
	// Setting the player's position (centered in the tile)
    game->player.x = x + 0.5;
    game->player.y = y + 0.5;

	// Determining the player's direction based on the map symbol
    if (dir == 'N') // North
    {
        game->player.dir_x = 0;
        game->player.dir_y = -1;
    }
    else if (dir == 'S') // South
    {
        game->player.dir_x = 0;
        game->player.dir_y = 1;
    }
    else if (dir == 'E') // East
    {
        game->player.dir_x = 1;
        game->player.dir_y = 0;
    }
    else if (dir == 'W') // West
    {
        game->player.dir_x = -1;
        game->player.dir_y = 0;
    }
}

// Function to parse the map grid and set the player's position
void parse_map_from_grid(t_game *game)
{
    int		x;
	int		y;
    int		player_set;
	char	c;

	y = 0;
	player_set = 0; // Flag to ensure there is only one player
	// Loop through each line of the map grid
    while (game->map.grid[y])
    {
        x = 0;
		// Loop through each character in the line
        while (game->map.grid[y][x])
        {
            c = game->map.grid[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') // Checking for player start symbols (N, S, E, W)
            {
				// If a player is already set, this is an error
                if (player_set)
                    exit_error("Error\nMultiple player start positions");
				// Setting the player position and direction
                set_player(game, x, y, c);
                player_set = 1;
                game->map.grid[y][x] = '0'; // Replacing the player symbol with '0' (empty space)
            }
            x++;
        }
        y++;
    }
    if (!player_set) // Checking if a player was set
        exit_error("Error\nNo player start position found");

    printf("Map parsed successfully!\n");
}
