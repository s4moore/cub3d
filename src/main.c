#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D map.cub", 2);
		return (1);
	}
	if (parse_file(argv[1], &game) != 0)
	{
		ft_putendl_fd("Failed to parse .cub file", 2);
		return (1);
	}
    // MLX initialization, rendering, and game loop will be here
	ft_putendl_fd("Map parsed successfully!", 1);
    free_game(&game);
    return (0);
}
