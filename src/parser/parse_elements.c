#include "cub3d.h"

int parse_element(char *line, t_game *game)
{
	while (*line == ' ')
		line++;
	if(ft_strncmp(line, "F ", 2) == 0)
		return parse_color(line + 2, &game->floor);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return parse_color(line + 2, &game->ceiling);
	if (parse_texture(line, game) == 0)
		return (0);
	if (parse_color_element(line, game) == 0)
		return (0);
	return (1); // Error: unknown element
}

int	parse_texture(char *line, t_game *game)
{
	if(ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->tex[TEX_NORTH].path)
			return (1); // Error: doubled texture
		game->tex[TEX_NORTH].path = ft_strtrim(line + 3, " \t");
		return (0);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->tex[TEX_SOUTH].path)
			return (1); // Error: doubled texture
		game->tex[TEX_SOUTH].path = ft_strtrim(line + 3, " \t");
		return (0);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if(game->tex[TEX_WEST].path)
			return (1); // Error: doubled texture
		game->tex[TEX_WEST].path = ft_strtrim(line + 3, " \t");
		return (0);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if(game->tex[TEX_EAST].path)
			return (1); // Error: doubled texture
		game->tex[TEX_EAST].path = ft_strtrim(line + 3, " \t");
		return (0);
	}
	return (1); // not a texture
}

int parse_color_element(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor.r >= 0)
			return (1); // Error: doubled color
		if (parse_color(line + 2, &game->floor) != 0)
			return (1); // Error: doubled color
		return (0);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceiling.r >= 0)
			return (1); // Error: doubled color
		if (parse_color(line + 2, &game->ceiling) != 0)
			return (1); // Error: doubled color
		return (0);
	}
	return (1); // not a color
}

int	parse_color(const char *line, t_color *color)
{
	char	**rgb;
	int		count;
	int		i;

	while (*line == ' ' || *line == '\t') // skipping spaces
		line++;
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	count = 0; //checking count of elements
	while (rgb[count])
		count++;
	if (count != 3)
	{
		i = 0; // free memory
		while (i < count)
		{
			free(rgb[i]);
			i++;
		}
		free(rgb);
		return (1);
	}
	// Проверка на числа и преобразование
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	// Освобождение памяти
	i = 0;
	while (i < count)
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
	// Проверка диапазона
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 || color->b < 0 || color->b > 255)
		return (1);
	return (0);
}

int	check_rgb_parts(t_rgb_parser *rgb_parser)
{
	if (!rgb_parser->parts || !rgb_parser->parts[0] || !rgb_parser->parts[1] || 
		!rgb_parser->parts[2] || rgb_parser->parts[3])
	{
		free_rgb_parts(rgb_parser);
		return (0);
	}
	return (1);
}

int	parse_rgb_values(t_rgb_parser *rgb_parser, t_color *color)
{
	rgb_parser->r_str = ft_strtrim(rgb_parser->parts[0], " \t");
	rgb_parser->g_str = ft_strtrim(rgb_parser->parts[1], " \t");
	rgb_parser->b_str = ft_strtrim(rgb_parser->parts[2], " \t");
	if (!validate_digit_string(rgb_parser->r_str) || 
		!validate_digit_string(rgb_parser->g_str) || 
		!validate_digit_string(rgb_parser->b_str))
	{
		free(rgb_parser->r_str);
		free(rgb_parser->g_str);
		free(rgb_parser->b_str);
		return (0);
	}
	color->r = ft_atoi(rgb_parser->r_str);
	color->g = ft_atoi(rgb_parser->g_str);
	color->b = ft_atoi(rgb_parser->b_str);
	free(rgb_parser->r_str);
	free(rgb_parser->g_str);
	free(rgb_parser->b_str);
	return (1);
}

int	validate_digit_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_rgb_parts(t_rgb_parser *rgb_parser)
{
	int	i;

	if (!rgb_parser->parts)
		return ;

	i = 0;
	while (rgb_parser->parts[i])
	{
		free(rgb_parser->parts[i]);
		i++;
	}
	free(rgb_parser->parts);
}

int	validate_color_range(t_color *color)
{
	if (color->r < 0 || color->r > 255 || 
		color->g < 0 || color->g > 255 || 
		color->b < 0 || color->b > 255)
		return (0);
	return (1);
}
