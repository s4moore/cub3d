/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:25:08 by samoore           #+#    #+#             */
/*   Updated: 2025/05/08 18:17:01 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <X11/keysym.h> //keysym

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct t_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	moveSpeed;
	double	rotSpeed;
	int keys[65536];
}	t_game;

#endif