/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:14:01 by samoore           #+#    #+#             */
/*   Updated: 2025/05/09 13:06:26 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 960
#define texWidth 1024
#define texHeight 1024
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
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,4},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,4,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,4},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
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
Uint32* texture[5];


#include <sys/time.h>

unsigned int getTicks() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned int)(tv.tv_sec * 1000 + tv.tv_usec / 1000); // ms
}

void	set_view_direction(t_game *game, char direction)
{
	if (direction == 'N')
		game->rot_speed = 0;
	if (direction == 'W')
		game->rot_speed = 1.5;
	if (direction == 'S')
		game->rot_speed = 3;
	if (direction == 'E')
		game->rot_speed = -1.5;
	
	double old_dir_x = game->dir_x;
	game->dir_x = game->dir_x * cos(game->rot_speed) - game->dir_y * sin(game->rot_speed);
	game->dir_y = old_dir_x * sin(game->rot_speed) + game->dir_y * cos(game->rot_speed);
	double old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(game->rot_speed) - game->planeY * sin(game->rot_speed);
	game->planeY = old_plane_x * sin(game->rot_speed) + game->planeY * cos(game->rot_speed);
}

void	ray_caster_init(t_game *game)
{
	game->x_pos = 22.0;
	game->y_pos = 22.0;
    game->dir_x = -1;
	game->dir_y = 0;
    game->plane_x = 0.0;
	game->planeY = 0.66;
    game->time = 0;
    game->old_time = 0;

	set_view_direction(game, 'E');
	
    for(int i = 0; i < 5; i++) {
        texture[i] = (Uint32*)malloc(sizeof(Uint32) * texWidth * texHeight);
    }

	int bpp, line_len, endian;
	int width, height;

	// texture[0] = mlx_xpm_file_to_image(game->mlx, "pics/brick_hi.xpm", &width, &height);
	// texture[1] = mlx_xpm_file_to_image(game->mlx, "pics/stone_hi.xpm", &width, &height);
	// texture[2] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	// texture[3] = mlx_xpm_file_to_image(game->mlx, "pics/metal_hi.xpm", &width, &height);
	// texture[4] = mlx_xpm_file_to_image(game->mlx, "pics/floor.xpm", &width, &height);
	texture[0] = mlx_xpm_file_to_image(game->mlx, "pics/rusty1.xpm", &width, &height);
	texture[1] = mlx_xpm_file_to_image(game->mlx, "pics/stone2.xpm", &width, &height);
	texture[2] = mlx_xpm_file_to_image(game->mlx, "pics/rmetal.xpm", &width, &height);
	texture[3] = mlx_xpm_file_to_image(game->mlx, "pics/rmetal.xpm", &width, &height);
	texture[4] = mlx_xpm_file_to_image(game->mlx, "pics/rock1.xpm", &width, &height);
	// texture[5] = mlx_xpm_file_to_image(game->mlx, "pics/stone_hi.xpm", &width, &height);
	// texture[6] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	// texture[7] = mlx_xpm_file_to_image(game->mlx, "pics/wood_hi.xpm", &width, &height);
	for (int i = 0; i < 5; i++)
		texture[i] = mlx_get_data_addr(texture[i], &line_len, &bpp, &endian);

}

int	draw(t_game *game)
{
	for(int x = 0; x < SCREEN_WIDTH; x++) {
		game->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		game->ray_dir_x = game->dir_x + game->plane_x * game->camera_x;
		game->ray_dir_y = game->dir_y + game->planeY * game->camera_x;

		game->map_x = (int)(game->x_pos);
		game->map_y = (int)(game->y_pos);

		double delta_x = (game->ray_dir_x == 0) ? 1e30 : fabs(1 / game->ray_dir_x);
		double delta_y = (game->ray_dir_y == 0) ? 1e30 : fabs(1 / game->ray_dir_y);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int hit = 0;
		int side;

		if (game->ray_dir_x < 0) {
			step_x = -1;
			side_dist_x = (game->x_pos - game->map_x) * delta_x;
		} else {
			step_x = 1;
			side_dist_x = (game->map_x + 1.0 - game->x_pos) * delta_x;
		}

		if (game->ray_dir_y < 0) {
			step_y = -1;
			side_dist_y = (game->y_pos - game->map_y) * delta_y;
		} else {
			step_y = 1;
			side_dist_y = (game->map_y + 1.0 - game->y_pos) * delta_y;
		}

		while (hit == 0) {
			if (side_dist_x < side_dist_y) {
				side_dist_x += delta_x;
				game->map_x += step_x;
				side = 0;
			} else {
				side_dist_y += delta_y;
				game->map_y += step_y;
				side = 1;
			}
			if (worldMap[game->map_x][game->map_y] > 0) hit = 1;
		}

		double perpWallDist = (side == 0)
			? (side_dist_x - delta_x)
			: (side_dist_y - delta_y);

		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		// int texNum = worldMap[game->map_x][game->map_y] - 1;
		double wallX = (side == 0)
			? game->y_pos + perpWallDist * game->ray_dir_y
			: game->x_pos + perpWallDist * game->ray_dir_x;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if(side == 0 && game->ray_dir_x > 0) texX = texWidth - texX - 1;
		if(side == 1 && game->ray_dir_y < 0) texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;

		int texNum;
		if (side == 0) {
			if (game->ray_dir_x > 0)
				texNum = 0;
			else
				texNum = 1;
		} else {
			if (game->ray_dir_y > 0)
				texNum = 2;
			else
				texNum = 3;
		}

		for(int y = drawStart; y < drawEnd; y++) {
			int texY = ((int)texPos);
			// int texY = ((int)texPos) & (texHeight - 1);
			texPos += step;
			Uint32 color = texture[texNum][texHeight * texY + texX];
			if (side == 1) color = (color >> 1) & 4355711;
			put_pixel(game, x, y, color);
		}
		double floorXWall, floorYWall;

		// Determine floor position based on wall hit
		if (side == 0 && game->ray_dir_x > 0) {
			floorXWall = game->map_x;
			floorYWall = game->map_y + wallX;
		} else if (side == 0 && game->ray_dir_x < 0) {
			floorXWall = game->map_x + 1.0;
			floorYWall = game->map_y + wallX;
		} else if (side == 1 && game->ray_dir_y > 0) {
			floorXWall = game->map_x + wallX;
			floorYWall = game->map_y;
		} else {
			floorXWall = game->map_x + wallX;
			floorYWall = game->map_y + 1.0;
		}
		for (int y = drawEnd + 1; y < SCREEN_HEIGHT; y++) {
			double currentDist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);

			double weight = currentDist / perpWallDist;

			double currentFloorX = weight * floorXWall + (1.0 - weight) * game->x_pos;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * game->y_pos;

			int floorTexX = (int)(currentFloorX * 1024) % 1024;
			int floorTexY = (int)(currentFloorY * 1024) % 1024;

			Uint32 color = texture[4][1024 * floorTexY + floorTexX];
			put_pixel(game, x, y, color);

			// Ceiling (mirror y)
			// Uint32 ceilColor = ceilTexture[floorTexY * texWidth + floorTexX];
			// put_pixel(game, x, screenHeight - y, ceilColor);
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);


	game->old_time = game->time;
	game->time = getTicks();
	double frameTime = (game->time - game->old_time) / 1000.0;


	game->move_speed = frameTime * 5.0;
	game->rot_speed = frameTime * 3.0;
	
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
		if (worldMap[(int)(game->x_pos + game->dir_x * game->move_speed)][(int)game->y_pos] == 0)
			game->x_pos += game->dir_x * game->move_speed;
		if (worldMap[(int)game->x_pos][(int)(game->y_pos + game->dir_y * game->move_speed)] == 0)
			game->y_pos += game->dir_y * game->move_speed;
	}
	if (game->keys[XK_Down]) {
		if (worldMap[(int)(game->x_pos - game->dir_x * game->move_speed)][(int)game->y_pos] == 0)
			game->x_pos -= game->dir_x * game->move_speed;
		if (worldMap[(int)game->x_pos][(int)(game->y_pos - game->dir_y * game->move_speed)] == 0)
			game->y_pos -= game->dir_y * game->move_speed;
	}
	if (game->keys[65363]) {
		double old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(-game->rot_speed) - game->dir_y * sin(-game->rot_speed);
		game->dir_y = old_dir_x * sin(-game->rot_speed) + game->dir_y * cos(-game->rot_speed);
		double old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-game->rot_speed) - game->planeY * sin(-game->rot_speed);
		game->planeY = old_plane_x * sin(-game->rot_speed) + game->planeY * cos(-game->rot_speed);
	}
	if (game->keys[65361]) {
		double old_dir_x = game->dir_x;
		game->dir_x = game->dir_x * cos(game->rot_speed) - game->dir_y * sin(game->rot_speed);
		game->dir_y = old_dir_x * sin(game->rot_speed) + game->dir_y * cos(game->rot_speed);
		double old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(game->rot_speed) - game->planeY * sin(game->rot_speed);
		game->planeY = old_plane_x * sin(game->rot_speed) + game->planeY * cos(game->rot_speed);
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
