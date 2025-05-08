/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:18:01 by samoore           #+#    #+#             */
/*   Updated: 2025/05/08 14:22:14 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_game*	init(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->img_data = mlx_get_data_addr(
			game->img, &game->bpp, &game->size_line, &game->endian
			);
	return game;
}

void	free_game(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
}

int	main(void)
{
	t_game	*game;

	game = init();
	free_game(game);
	// mlx_loop(game->mlx);
	return (0);
}
