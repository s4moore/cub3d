/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:14:01 by samoore           #+#    #+#             */
/*   Updated: 2025/05/12 17:22:27 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	set_star_colour(t_game *game, int i)
{
	int	r;
	int	g;
	int	b;

	g = rand() % 36 + 140;
	b = rand() % 36 + 140;
	r = rand() % 36 + 140;
	game->stars[i].color = (r << 16) | (g << 8) | b;
	game->stars[i].twinkle_color
		= ((int)(r / 1.5) << 16) | ((int)(g / 1.5) << 8) | b;
	game->stars[i].twinkle = ((rand() % 1000) + 5) * 10;
	game->stars[i].timer = 0;
}

void	create_stars(t_game *game)
{
	double	theta;
	int		i;
	double	phi;
	int		w;
	int		h;

	h = 0;
	w = 0;
	game->stars = malloc(sizeof(t_star) * NUM_STARS);
	if (!game->stars)
		return ;
	i = -1;
	while (++i < NUM_STARS)
	{
		theta = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
		phi = acos(2.0 * ((double)rand() / RAND_MAX) - 1.0);
		game->stars[i].x = 100 * sin(phi) * cos(theta);
		game->stars[i].y = 100 * cos(phi);
		game->stars[i].z = 100 * sin(phi) * sin(theta);
		game->stars[i].size = rand() % 3;
		set_star_colour(game, i);
	}
}

void	put_planet_in_3d(t_game *game)
{
	double	theta;
	double	height;
	int		i;

	i = -1;
	while (++i < NUM_PLANETS)
	{
		theta = ((double)rand() / RAND_MAX) * 2.0 * M_PI;
		height = ((double)rand() / RAND_MAX) * SCREEN_H - SCREEN_H / 2.0;
		game->planets[i].orbit_radius = SCREEN_W;
		game->planets[i].orbit_height = height;
		game->planets[i].orbit_angle = theta;
		game->planets[i].pos.x = SCREEN_W * cos(theta);
		game->planets[i].pos.z = SCREEN_W * sin(theta);
		game->planets[i].pos.y = height;
	}
}

void	load_planets(t_game *game)
{
	int	i;
	int	j;
	int	bpp;
	int	line_len;
	int	endian;

	i = -1;
	while (++i < 1)
		game->planets[i].img = malloc(
				sizeof(Uint32) * TEXTURE_SIZE * TEXTURE_SIZE);
	game->planets[0].img = mlx_xpm_file_to_image(
			game->mlx, "pics/mars.xpm",
			&game->planets[i].w, &game->planets[i].h);
	i = -1;
	while (++i < 1)
		game->planets[i].img = mlx_get_data_addr(
				game->planets[i].img, &line_len, &bpp, &endian);
	game->planets[0].w = 800;
	game->planets[0].h = 800;
	game->planets[0].pos.x = 1;
	game->planets[0].pos.y = 15;
	game->planets[0].pos.z = 100;
	put_planet_in_3d(game);
}

t_game	*init(void)
{
	t_game	*game;
	int		i;

	game = malloc(sizeof(t_game));
	game->stars = malloc(sizeof(t_star) * NUM_STARS);
	game->mlx = mlx_init();
	create_stars(game);
	load_planets(game);
	game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H, "cub3d");
	game->img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	game->addr = mlx_get_data_addr(
			game->img, &game->bpp, &game->line_len, &game->endian
			);
	game->props = malloc(sizeof(t_draw_props));
	i = -1;
	while (++i < 65536)
		game->keys[i] = 0;
	return (game);
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

static inline int	pixel_pos(int x, int y, int size_line, int bpp)
{
	return (y * size_line + x * (bpp / 8));
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
		return ;
	dst = game->addr + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *) dst = color;
}

unsigned int	get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned int)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	set_view_direction(t_game *game, char direction)
{
	double	old_dir_x;
	double	old_plane_x;

	if (direction == 'N')
		game->rot_speed = 0;
	if (direction == 'W')
		game->rot_speed = 1.5;
	if (direction == 'S')
		game->rot_speed = 3;
	if (direction == 'E')
		game->rot_speed = -1.5;
	old_dir_x = game->dir.x;
	game->dir.x = game->dir.x * cos(game->rot_speed)
		- game->dir.y * sin(game->rot_speed);
	game->dir.y = old_dir_x * sin(game->rot_speed)
		+ game->dir.y * cos(game->rot_speed);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(game->rot_speed)
		- game->plane_y * sin(game->rot_speed);
	game->plane_y = old_plane_x * sin(game->rot_speed)
		+ game->plane_y * cos(game->rot_speed);
}

void	load_textures(t_game *game)
{
	int	i;
	int	j;
	int	bpp;
	int	line_len;
	int	endian;

	i = -1;
	while (++i < 5)
		texture[i] = malloc(sizeof(Uint32) * TEXTURE_SIZE * TEXTURE_SIZE);
	texture[0] = mlx_xpm_file_to_image(game->mlx, "pics/slate.xpm", &i, &j);
	texture[1] = mlx_xpm_file_to_image(game->mlx, "pics/rusty1.xpm", &i, &j);
	texture[2] = mlx_xpm_file_to_image(game->mlx, "pics/rock1.xpm", &i, &j);
	texture[3] = mlx_xpm_file_to_image(game->mlx, "pics/cobble.xpm", &i, &j);
	texture[4] = mlx_xpm_file_to_image(game->mlx, "pics/rubber.xpm", &i, &j);
	i = -1;
	while (++i < 5)
		texture[i] = mlx_get_data_addr(texture[i], &line_len, &bpp, &endian);
}

void	ray_caster_init(t_game *game)
{
	game->player.x = 22.0;
	game->player.y = 22.0;
	game->dir.x = -1;
	game->dir.y = 0;
	game->plane_x = 0;
	game->plane_y = 0.6;
	game->time = 0;
	game->old_time = 0;
	set_view_direction(game, 'N');
	load_textures(game);
}

t_xy_int	calculate_gridline_distance(t_game *game, t_draw_props *props)
{
	if (props->ray_dir.x < 0)
	{
		props->step.x = -1;
		props->ray_dist.x = (game->player.x - game->map_x) * props->delta.x;
	}
	else
	{
		props->step.x = 1;
		props->ray_dist.x
			= (game->map_x + 1.0 - game->player.x) * props->delta.x;
	}
	if (props->ray_dir.y < 0)
	{
		props->step.y = -1;
		props->ray_dist.y
			= (game->player.y - game->map_y) * props->delta.y;
	}
	else
	{
		props->step.y = 1;
		props->ray_dist.y
			= (game->map_y + 1.0 - game->player.y) * props->delta.y;
	}
}

void	get_floor_start_position(t_game *game)
/*Determines where to start drawing the floor from*/
{
	t_draw_props	*props;

	props = game->props;
	if (props->side == 0 && props->ray_dir.x > 0)
	{
		props->floor_start.x = game->map_x;
		props->floor_start.y = game->map_y + props->wall_x;
	}
	else if (props->side == 0 && props->ray_dir.x < 0)
	{
		props->floor_start.x = game->map_x + 1.0;
		props->floor_start.y = game->map_y + props->wall_x;
	}
	else if (props->side == 1 && props->ray_dir.y > 0)
	{
		props->floor_start.x = game->map_x + props->wall_x;
		props->floor_start.y = game->map_y;
	}
	else
	{
		props->floor_start.x = game->map_x + props->wall_x;
		props->floor_start.y = game->map_y + 1.0;
	}
}

void	calculate_wall_distance(t_game *game, t_draw_props *props)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (props->ray_dist.x < props->ray_dist.y)
		{
			props->ray_dist.x += props->delta.x;
			game->map_x += props->step.x;
			props->side = 0;
		}
		else
		{
			props->ray_dist.y += props->delta.y;
			game->map_y += props->step.y;
			props->side = 1;
		}
		if (g_world_map[game->map_x][game->map_y] > 0)
			hit = 1;
	}
	if (props->side == 0)
		props->wall_dist = props->ray_dist.x - props->delta.x;
	else
		props->wall_dist = props->ray_dist.y - props->delta.y;
}

void	select_texture_by_wall_direction(t_draw_props *props)
{
	if (props->side == 0)
	{
		if (props->ray_dir.x > 0)
			props->tex_num = 0;
		else
			props->tex_num = 1;
	}
	else
	{
		if (props->ray_dir.y > 0)
			props->tex_num = 2;
		else
			props->tex_num = 3;
	}
}

void	calcualte_slice_properties(t_game *game)
{
	t_draw_props	*props;

	props = game->props;
	props->line_height = (int)(SCREEN_H / props->wall_dist);
	props->draw_start = -props->line_height / 2 + SCREEN_H / 2;
	if (props->draw_start < 0)
		props->draw_start = 0;
	props->draw_end = props->line_height / 2 + SCREEN_H / 2;
	if (props->draw_end >= SCREEN_H)
		props->draw_end = SCREEN_H - 1;
	if (props->side == 0)
		props->wall_x = game->player.y + props->wall_dist * props->ray_dir.y;
	else
		props->wall_x = game->player.x + props->wall_dist * props->ray_dir.x;
	props->wall_x -= floor(props->wall_x);
}

void	calcualte_texture_properties(t_draw_props *props)
{
	props->tex.x = (int)(props->wall_x * (double)TEXTURE_SIZE);
	if (props->side == 0 && props->ray_dir.x > 0)
		props->tex.x = TEXTURE_SIZE - props->tex.x - 1;
	if (props->side == 1 && props->ray_dir.y < 0)
		props->tex.x = TEXTURE_SIZE - props->tex.x - 1;
	props->tex_step = 1.0 * TEXTURE_SIZE / props->line_height;
	props->tex_offset = (props->draw_start - SCREEN_H / 2
			+ props->line_height / 2) * props->tex_step;
}

void	draw_walls(t_game *game, int x)
{
	t_draw_props	*props;
	Uint32			color;
	int				y;

	props = game->props;
	y = props->draw_start - 1;
	while (++y < props->draw_end)
	{
		props->tex.y = ((int)props->tex_offset);
		props->tex_offset += props->tex_step;
		color = texture[props->tex_num][TEXTURE_SIZE
			* props->tex.y + props->tex.x];
		color = (color >> 1) & 4355711;
		put_pixel(game, x, y, color);
	}
}

void	calculate_initial_props(t_game *game, int x)
{
	t_draw_props	*props;

	props = game->props;
	props->col = 2 * x / (double)SCREEN_W - 1;
	props->ray_dir.x = game->dir.x + game->plane_x * props->col;
	props->ray_dir.y = game->dir.y + game->plane_y * props->col;
	game->map_x = (int)(game->player.x);
	game->map_y = (int)(game->player.y);
	if (props->ray_dir.x == 0)
		props->delta.x = 1e30;
	else
		props->delta.x = fabs(1 / props->ray_dir.x);
	if (props->ray_dir.y == 0)
		props->delta.y = 1e30;
	else
		props->delta.y = fabs(1 / props->ray_dir.y);
}

void	draw_floor(t_game *game, t_draw_props *props, int x)
{
	t_xy_dbl	current_floor;
	double		current_dist;
	double		weight;
	int			y;

	y = props->draw_end;
	while (++y < SCREEN_H)
	{
		current_dist = SCREEN_H / (2.0 * y - SCREEN_H);
		weight = current_dist / props->wall_dist;
		current_floor.x = weight * props->floor_start.x
			+ (1.0 - weight) * game->player.x;
		current_floor.y = weight * props->floor_start.y
			+ (1.0 - weight) * game->player.y;
		put_pixel(
			game,
			x,
			y,
			texture[4][1024 * ((int)(current_floor.y * 1024) % 1024)
			+ ((int)(current_floor.x * 1024) % 1024)]);
	}
}
/*// Ceiling (mirror y)
// Uint32 ceilColor = 
	ceilTexture[floorgame->tex.y * TEXTURE_SIZE + floorgame->Tex.x];
// put_pixel(game, x, screenHeight - y, ceilColor);*/

void	update_speed(t_game *game)
{
	double	frame_time;

	game->old_time = game->time;
	game->time = get_ticks();
	frame_time = (game->time - game->old_time) / 1000.0;
	game->move_speed = frame_time * 5.0;
	game->rot_speed = frame_time * 2.5;
}

void	draw_star(t_game *game, t_star s, int color)
{
	int	y;
	int	err;

	y = 0;
	err = 0;
	while (s.size >= y)
	{
		put_pixel(game, s.screen_x + s.size, s.screen_y + y, color);
		put_pixel(game, s.screen_x + y, s.screen_y + s.size, color);
		put_pixel(game, s.screen_x - y, s.screen_y + s.size, color);
		put_pixel(game, s.screen_x - s.size, s.screen_y + y, color);
		put_pixel(game, s.screen_x - s.size, s.screen_y - y, color);
		put_pixel(game, s.screen_x - y, s.screen_y - s.size, color);
		put_pixel(game, s.screen_x + y, s.screen_y - s.size, color);
		put_pixel(game, s.screen_x + s.size, s.screen_y - y, color);
		y += 1;
		if (err <= 0)
			err += 2 * y + 1;
		if (err > 0)
		{
			s.size -= 1;
			err -= 2 * s.size + 1;
		}
	}
}

void	put_image(t_game *game)
{
	t_xy_int	pos;
	int			clear;
	int			size;
	int			i;
	int			j;

	clear = game->planets[0].img[0];
	if (game->planets[0].pos.z < 0)
		return ;
	size = 2;
	i = 0;
	while (i < game->planets[0].h)
	{
		j = 0;
		while (j < game->planets[0].w)
		{
			if (game->planets[0].img[i * game->planets[0].w + j] != clear)
				put_pixel(game,
					SCREEN_W / 2 + game->planets[0].pos.x + j / size,
					100 + i / size,
					game->planets[0].img[i * game->planets[0].w + j]);
			j += size;
		}
		i += size;
	}
}

void	draw_stars(t_game *game)
{
	t_star	s;
	int		i;

	i = -1;
	while (++i < NUM_STARS)
	{
		s = game->stars[i];
		game->stars[i].timer++;
		if (s.z <= 1)
			continue ;
		s.screen_x = (s.x / s.y) * (SCREEN_W / 2) + (SCREEN_W / 2);
		s.screen_y = (s.z / s.y) * (SCREEN_H / 2) + (SCREEN_H / 2);
		if (s.screen_x >= 0 && s.screen_x < SCREEN_W
			&& s.screen_y >= 0 && s.screen_y < SCREEN_H / 2)
		{
			if (s.timer > 1)
				draw_star(game, s, (int)s.color);
			else
				draw_star(game, s, 0xffffffff);
			if (s.timer >= s.twinkle)
				game->stars[i].timer = 0;
		}
	}
}

double	get_player_rotation_angle(t_game *game)
{
	return (atan2(game->dir.y, game->dir.x));
}

int	draw(t_game *game)
{
	int	x;

	x = -1;
	draw_stars(game);
	put_image(game);
	while (++x < SCREEN_W)
	{
		calculate_initial_props(game, x);
		calculate_gridline_distance(game, game->props);
		calculate_wall_distance(game, game->props);
		calcualte_slice_properties(game);
		calcualte_texture_properties(game->props);
		select_texture_by_wall_direction(game->props);
		draw_walls(game, x);
		get_floor_start_position(game);
		draw_floor(game, game->props, x);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	update_speed(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 1;
	if (keycode == XK_Escape)
		exit_program(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

void	check_up_down_arrows(t_game *game)
{
	if (game->keys[XK_Up] || game->keys[XK_w])
	{
		if (g_world_map[(int)(game->player.x + game->dir.x
				* game->move_speed)][(int)game->player.y] == 0)
			game->player.x += game->dir.x * game->move_speed;
		if (g_world_map[(int)game->player.x][(int)(game->player.y
			+ game->dir.y * game->move_speed)] == 0)
			game->player.y += game->dir.y * game->move_speed;
	}
	if (game->keys[XK_Down] || game->keys[XK_s])
	{
		if (g_world_map[(int)(game->player.x - game->dir.x
				* game->move_speed)][(int)game->player.y] == 0)
			game->player.x -= game->dir.x * game->move_speed;
		if (g_world_map[(int)game->player.x][(int)(game->player.y
			- game->dir.y * game->move_speed)] == 0)
			game->player.y -= game->dir.y * game->move_speed;
	}
}

void	check_strafe(t_game *game)
{
	double	x;
	double	y;

	if (game->keys[XK_d])
	{
		x = game->dir.y;
		y = -game->dir.x;
		if (g_world_map[(int)(game->player.x + x * game->move_speed)]
				[(int)game->player.y] == 0)
			game->player.x += x * game->move_speed;
		if (g_world_map[(int)game->player.x][(int)(game->player.y + y
			* game->move_speed)] == 0)
			game->player.y += y * game->move_speed;
	}
	if (game->keys[XK_a])
	{
		x = -game->dir.y;
		y = game->dir.x;
		if (g_world_map[(int)(game->player.x + x * game->move_speed)]
				[(int)game->player.y] == 0)
			game->player.x += x * game->move_speed;
		if (g_world_map[(int)game->player.x][(int)(game->player.y + y
			* game->move_speed)] == 0)
			game->player.y += y * game->move_speed;
	}
}

void	rotate_stars(t_game *game, t_star *stars, int direction)
{
	double	cos_rot;
	double	sin_rot;
	double	old_x;
	double	old_y;
	int		i;

	cos_rot = cos(direction * game->rot_speed * 0.5);
	sin_rot = sin(direction * game->rot_speed * 0.5);
	i = -1;
	while (++i < NUM_STARS)
	{
		old_x = stars[i].x;
		old_y = stars[i].y;
		stars[i].x = old_x * cos_rot - old_y * sin_rot;
		stars[i].y = old_x * sin_rot + old_y * cos_rot;
	}
}

void	rotate_planets(t_game *game, int direction)
{
	double	a;
	double	r;

	game->planets[0].orbit_angle += game->rot_speed * direction;
	a = game->planets[0].orbit_angle;
	r = game->planets[0].orbit_radius;
	game->planets[0].pos.x = r * cos(a);
	game->planets[0].pos.z = r * sin(a);
	game->planets[0].pos.y = game->planets[0].orbit_height;
}

void	check_left_arrow(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->keys[0xff51])
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(game->rot_speed)
			- game->dir.y * sin(game->rot_speed);
		game->dir.y = old_dir_x * sin(game->rot_speed)
			+ game->dir.y * cos(game->rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(game->rot_speed)
			- game->plane_y * sin(game->rot_speed);
		game->plane_y = old_plane_x * sin(game->rot_speed)
			+ game->plane_y * cos(game->rot_speed);
		rotate_stars(game, game->stars, LEFT);
		game->planet_angle += game->rot_speed;
		rotate_planets(game, LEFT);
	}
}

void	check_right_arrow(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	if (game->keys[0xff53])
	{
		old_dir_x = game->dir.x;
		game->dir.x = game->dir.x * cos(-game->rot_speed)
			- game->dir.y * sin(-game->rot_speed);
		game->dir.y = old_dir_x * sin(-game->rot_speed)
			+ game->dir.y * cos(-game->rot_speed);
		old_plane_x = game->plane_x;
		game->plane_x = game->plane_x * cos(-game->rot_speed)
			- game->plane_y * sin(-game->rot_speed);
		game->plane_y = old_plane_x * sin(-game->rot_speed)
			+ game->plane_y * cos(-game->rot_speed);
		rotate_stars(game, game->stars, RIGHT);
		game->planet_angle -= game->rot_speed;
		rotate_planets(game, RIGHT);
	}
}

int	update(t_game *game)
{
	check_up_down_arrows(game);
	check_left_arrow(game);
	check_right_arrow(game);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, SCREEN_W, SCREEN_H);
	draw(game);
	return (0);
}

int	main(void)
{
	t_game	*game;

	game = init();
	ray_caster_init(game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
	exit_program(game);
	return (0);
}
