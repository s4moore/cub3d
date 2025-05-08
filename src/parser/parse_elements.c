#include "cub3d.h"

// Function to parse a color value (R,G,B)
int	parse_color(const char *line, t_color *color)
{
	char **rgb;

	rgb = ft_split(line, ','); // Splitting the line into three values (R, G, B) using a comma as a delimiter
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		return (1); // Error: invalid color format

	// Converting the string values to integers
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	// Freeing the split strings
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);

	// Validating the color values (must be between 0 and 255)
	if (color->r < 0 || color->r > 255 ||
		color->g < 0 || color->g > 255 ||
		color->b < 0 || color->b > 255)
	return (1); // Error: color values out of range
	return (0);
}

// Function to parse an element (texture or color) in the .cub file
int	parse_element(char *line, t_game *game)
{
	// Skipping leading spaces
	while (*line == ' ')
		line++;

	// Checking for texture identifiers
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->tex[TEX_NORTH].path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->tex[TEX_SOUTH].path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->tex[TEX_WEST].path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->tex[TEX_EAST].path = ft_strdup(line + 3);
	// Checking for floor and ceiling colors
	else if (ft_strncmp(line, "F ", 2) == 0)
		return parse_color(line + 2, &game->floor); // Parsing floor color
	else if (ft_strncmp(line, "C ", 2) == 0)
		return parse_color(line + 2, &game->ceiling); // Parsing ceiling color
	// If none of the above, it is an invalid element
	else
		return (1); // Error: unknown element
	return (0);
}
