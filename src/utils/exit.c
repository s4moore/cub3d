#include "cub3d.h"
#include <stdlib.h>

void	exit_error(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	exit(EXIT_FAILURE);
}

void free_game(t_game *game)
{
    free_textures(game);
    free_map_grid(game);
}

void free_textures(t_game *game)
{
    if (game->tex[TEX_NORTH].path)
        free(game->tex[TEX_NORTH].path);
    if (game->tex[TEX_SOUTH].path)
        free(game->tex[TEX_SOUTH].path);
    if (game->tex[TEX_WEST].path)
        free(game->tex[TEX_WEST].path);
    if (game->tex[TEX_EAST].path)
        free(game->tex[TEX_EAST].path);
}

void free_map_grid(t_game *game)
{
    int i;
    
    i = 0;
    if (game->map.grid)
    {
        while (game->map.grid[i])
        {
            free(game->map.grid[i]);
            i++;
        }
        free(game->map.grid);
    }
}
