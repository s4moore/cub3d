/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:18:01 by samoore           #+#    #+#             */
/*   Updated: 2025/05/08 20:38:55 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 960
#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

t_game*	init(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->addr = mlx_get_data_addr(
			game->img, &game->bpp, &game->line_len, &game->endian
			);
	return game;
}

void	exit_program(t_game *game)
{
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free(game);
	exit(0);
}

static inline int pixel_pos(int x, int y, int size_line, int bpp) {
	return y * size_line + x * (bpp / 8);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int*)dst = color;
}

typedef unsigned int Uint32;

Uint32 buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
Uint32* texture[8];


#include <sys/time.h>

unsigned int getTicks() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned int)(tv.tv_sec * 1000 + tv.tv_usec / 1000); // ms
}

void	ray_caster_init(t_game *game)
{
	game->posX = 22.0, game->posY = 11.5;
    game->dirX = -1.0, game->dirY = 0.0;
    game->planeX = 0.0, game->planeY = 0.66;

    game->time = 0;
    game->oldTime = 0;

	
    for(int i = 0; i < 8; i++) {
        texture[i] = (Uint32*)malloc(sizeof(Uint32) * texWidth * texHeight);
    }

    // screen(SCREEN_WIDTH, SCREEN_HEIGHT, 0, "Raycaster");

// #if 0
//     // Generate procedural textures
//     for(int x = 0; x < texWidth; x++)
//     for(int y = 0; y < texHeight; y++) {
//         int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
//         int ycolor = y * 256 / texHeight;
//         int xycolor = y * 128 / texHeight + x * 128 / texWidth;
//         texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y);
//         texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
//         texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor;
//         texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
//         texture[4][texWidth * y + x] = 256 * xorcolor;
//         texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16);
//         texture[6][texWidth * y + x] = 65536 * ycolor;
//         texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128;
//     }
// #else
    // int width = 64;
	// int height = 64;
	// void *texture_img[8];
	int bpp, line_len, endian;
	int width, height;

	// texture_img[0] = mlx_png_file_to_image(game->mlx, "pics/eagle.png", &width, &height);
	// texture[0] = (Uint32 *)mlx_get_data_addr(texture_img[0], &bpp, &size_line, &endian);
    // texture[0] = mlx_png_file_to_image(game, "pics/eagle.png", &height, &width);
	// texture[0] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[1] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[2] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[3] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[4] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[5] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[6] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	// texture[7] = mlx_xpm_file_to_image(game->mlx, "pics/wall1_w.xpm", &width, &height);
	texture[0] = mlx_xpm_file_to_image(game->mlx, "pics/brick_hi.xpm", &width, &height);
	printf("1\n");
	texture[1] = mlx_xpm_file_to_image(game->mlx, "pics/stone_hi.xpm", &width, &height);
	texture[2] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	texture[3] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	texture[4] = mlx_xpm_file_to_image(game->mlx, "pics/brick_hi.xpm", &width, &height);
	texture[5] = mlx_xpm_file_to_image(game->mlx, "pics/stone_hi.xpm", &width, &height);
	texture[6] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	texture[7] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	for (int i = 0; i < 8; i++)
		texture[i] = mlx_get_data_addr(texture[i], &line_len, &bpp, &endian);

	// texture[0] = mlx_png_file_to_image(game->mlx, "pics/redbrick.png", &height, &width);
    // texture[1] = mlx_png_file_to_image(game->mlx, "pics/redbrick.png", &height, &width);
//     texture[2] = mlx_png_file_to_image(game->mlx, "pics/purplestone.png", &height, &width);
//     texture[3] = mlx_png_file_to_image(game->mlx, "pics/greystone.png", &height, &width);
//     texture[4] = mlx_png_file_to_image(game->mlx, "pics/bluestone.png", &height, &width);
//     texture[5] = mlx_png_file_to_image(game->mlx, "pics/mossy.png", &height, &width);
//     texture[6] = mlx_png_file_to_image(game->mlx, "pics/wood.png", &height, &width);
//     texture[7] = mlx_png_file_to_image(game->mlx, "pics/colorstone.png", &height, &width);
// // #endif
	// void *texture_img[8];
	// Uint32 *texture[8];
	// int bpp, size_line, endian;
	// int width, height;
	// char *texture_paths[8] = {
	// 	"pics/eagle.png",
	// 	"pics/redbrick.png",
	// 	"pics/purplestone.png",
	// 	"pics/greystone.png",
	// 	"pics/bluestone.png",
	// 	"pics/mossy.png",
	// 	"pics/wood.png",
	// 	"pics/colorstone.png"
	// };

	// for (int i = 0; i < 8; i++)
	// {
	// 	texture_img[i] = mlx_png_file_to_image(game->mlx, texture_paths[i], &width, &height);
	// 	texture[i] = (Uint32 *)mlx_get_data_addr(texture_img[i], &bpp, &size_line, &endian);
	// }

    // for(int i = 0; i < 8; i++) free(texture[i]);

}

int	draw(t_game *game)
{
	for(int x = 0; x < SCREEN_WIDTH; x++) {
		double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
		double rayDirX = game->dirX + game->planeX * cameraX;
		double rayDirY = game->dirY + game->planeY * cameraX;

		int mapX = (int)(game->posX);
		int mapY = (int)(game->posY);

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double sideDistX, sideDistY;
		int stepX, stepY;
		int hit = 0, side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (game->posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (game->posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
		}

		while (hit == 0) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}

		double perpWallDist = (side == 0)
			? (sideDistX - deltaDistX)
			: (sideDistY - deltaDistY);

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int pitch = 100;
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2 + pitch;
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		int texNum = worldMap[mapX][mapY] - 1;
		double wallX = (side == 0)
			? game->posY + perpWallDist * rayDirY
			: game->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - pitch - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;

		for(int y = drawStart; y < drawEnd; y++) {
			int texY = ((int)texPos) & (texHeight - 1);
			texPos += step;
			Uint32 color = texture[texNum][texHeight * texY + texX];
			if (side == 1) color = (color >> 1) & 8355711;
			put_pixel(game, x, y, color);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);


	game->oldTime = game->time;
	game->time = getTicks();
	double frameTime = (game->time - game->oldTime) / 1000.0;


	game->moveSpeed = frameTime * 5.0;
	game->rotSpeed = frameTime * 3.0;
	
	return (0);
}

int key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	if (keycode == XK_Escape)
		exit_program(game);
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

int update(t_game *game)
{
	if (game->keys[XK_Up]) {
		if (worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)game->posY] == 0)
			game->posX += game->dirX * game->moveSpeed;
		if (worldMap[(int)game->posX][(int)(game->posY + game->dirY * game->moveSpeed)] == 0)
			game->posY += game->dirY * game->moveSpeed;
	}
	if (game->keys[XK_Down]) {
		if (worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)game->posY] == 0)
			game->posX -= game->dirX * game->moveSpeed;
		if (worldMap[(int)game->posX][(int)(game->posY - game->dirY * game->moveSpeed)] == 0)
			game->posY -= game->dirY * game->moveSpeed;
	}
	if (game->keys[65363]) {
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
	}
	if (game->keys[65361]) {
		double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
		game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
		game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw(game);
	return (0);
}


int	main(void)
{
	t_game	*game;

	game = init();
	for (int i = 0; i < 65536; i++)
		game->keys[i] = 0;
	ray_caster_init(game);
	mlx_hook(game->win, 2, 1L<<0, key_press, game);
	mlx_hook(game->win, 3, 1L<<1, key_release, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	exit_program(game);
	return (0);
}
