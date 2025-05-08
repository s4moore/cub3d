/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:18:01 by samoore           #+#    #+#             */
/*   Updated: 2025/05/08 13:09:14 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64

typedef struct {
    void *mlx;
    void *win;
    void *img;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
    // Add other necessary fields like player position, direction, etc.
} t_game;

int main() {
    t_game game;

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.img_data = mlx_get_data_addr(game.img, &game.bpp, &game.size_line, &game.endian);

    // Load textures, initialize player position and direction, etc.

    // Set up event hooks and the main loop
    mlx_loop(game.mlx);

    return 0;
}
