/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:25:08 by samoore           #+#    #+#             */
/*   Updated: 2025/05/12 17:22:30 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <X11/keysym.h> //keysym
# include <sys/time.h>

#define SCREEN_W 1800
#define SCREEN_H 1080
#define TEXTURE_SIZE 1024
#define NUM_STARS 30000
#define NUM_PLANETS 1
#define STAR_SPHERE_RADIUS 10.0
#define MAP_W 24
#define MAP_H 24
#define LEFT -1
#define RIGHT 1
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

typedef unsigned int Uint32;
Uint32	buffer[SCREEN_H][SCREEN_W];
Uint32*	texture[5];

typedef struct s_xyz {
    double x;
    double y;
    double z;
} t_xyz;

typedef struct s_star {
    double	x;
    double	y;
    double	z;
    double	size;
	double	screen_x;
	double	screen_y;
    int		color;
	int		twinkle;
	int		timer;
	int		twinkle_color;
} t_star;



int	g_world_map[MAP_W][MAP_H] = \
{
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 7, 7, 7, 7, 7, 7, 7, 7},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 7},
{4, 0, 4, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 0, 7, 7, 7, 7, 7},
{4, 0, 5, 0, 0, 0, 0, 5, 0, 5, 0, 5, 0, 5, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 6, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 4},
{4, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 4, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 0, 0, 0, 4},
{4, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 5, 7, 0, 0, 0, 7, 7, 7, 1},
{4, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 5, 5, 5, 7, 7, 7, 7, 7, 7, 7, 1},
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4},
{6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
{4, 4, 4, 4, 4, 4, 0, 4, 4, 4, 6, 0, 6, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 2},
{4, 0, 0, 5, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2},
{4, 0, 6, 0, 6, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 5, 0, 0, 2, 0, 0, 0, 2},
{4, 0, 0, 0, 0, 0, 0, 0, 0, 4, 6, 0, 6, 2, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2},
{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3}
};



typedef struct s_xy_dbl
{
	double	x;
	double	y;
}	t_xy_dbl;

typedef struct s_xy_int
{
	int	x;
	int	y;
}	t_xy_int;

typedef struct s_draw_props
{
	t_xy_dbl	ray_dir;
	t_xy_dbl	delta;
	t_xy_dbl	ray_dist;
	t_xy_int	step;
	t_xy_int	tex;
	t_xy_dbl	floor_start;
	double		wall_x;
	double		wall_dist;
	int			side;
	int			tex_num;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		tex_step;
	double		tex_offset;
	double		col;
}	t_draw_props;

// typedef struct s_star{
// 	double	x;
// 	double	y;
// 	double	z;
// }	t_star;

typedef struct s_planet{
	Uint32		*img;
	int			w;
	int			h;
	t_xyz		pos;
	t_xy_int	screen;
	double orbit_radius;
	double orbit_height;
	double orbit_angle;
}	t_planet;

typedef struct t_game
{
	t_draw_props	*props;
	t_star			*stars;
	t_xy_dbl		player;
	// t_xy_dbl		dir;
	t_xyz			dir;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				line_len;
	int				endian;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;
	double			move_speed;
	double			rot_speed;
	double			yaw;
	double			pitch;
	int				map_x;
	int				map_y;
	double			planet_angle;
	t_planet		planets[3];
	int 			keys[65536];
}	t_game;

#endif