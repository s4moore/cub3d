#include "cub3d.h"

// Parses the .cub file and loads textures, colors, and the map
int parse_file(const char *path, t_game *game)
{
    int		fd;
    char	*line;
    int		map_start = 0;
    char	*map_lines[1000]; // Temporary buffer for map lines
    int		map_row = 0;
	int		i;

	 // Opening the .cub file for reading
    fd = open(path, O_RDONLY);
    if (fd < 0)
        exit_error("Error\nCannot open map file.");

	// Reading the file line by line
    while ((line = get_next_line(fd)))
    {
        if (ft_strlen(line) > 1) // If the line is not empty
        {
            if (ft_isdigit(line[0]) || line[0] == ' ')  // If the line starts with a digit or space, it is part of the map
            {
                map_lines[map_row++] = ft_strdup(line);
                map_start = 1;
            }
            else if (!map_start) // If it's not a map line, it should be a texture or color element
            {
                if (parse_element(line, game) != 0)
                {
                    free(line);
                    exit_error("Error\nInvalid element in map file.");
                }
            }
        }
        free(line);
    }
    close(fd);

    if (map_row == 0) // Checking if the map was found
        exit_error("Error\nMap not found in file.");

    // Transferring map lines to game->map.grid
    game->map.grid = malloc(sizeof(char *) * (map_row + 1));
    if (!game->map.grid)
        exit_error("Error\nmalloc failed");

	// Copying map lines, trimming newline characters
    i = 0;
	while (i < map_row)
	{
		game->map.grid[i] = ft_strtrim(map_lines[i], "\n");
		i++;
	}
	game->map.grid[map_row] = NULL;

    parse_map_from_grid(game); // Calling parse_map to process the loaded map grid

    // Debug output: displaying loaded textures and colors
    printf("TEXTURES:\n");
    printf("  NO: %s\n", game->tex[TEX_NORTH].path);
    printf("  SO: %s\n", game->tex[TEX_SOUTH].path);
    printf("  WE: %s\n", game->tex[TEX_WEST].path);
    printf("  EA: %s\n", game->tex[TEX_EAST].path);

    printf("COLORS:\n");
    printf("  Floor: R%d G%d B%d\n", game->floor.r, game->floor.g, game->floor.b);
    printf("  Ceil : R%d G%d B%d\n", game->ceiling.r, game->ceiling.g, game->ceiling.b);

    printf("Map parsed successfully!\n");

    return 0;
}
