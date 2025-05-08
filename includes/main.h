/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:25:08 by samoore           #+#    #+#             */
/*   Updated: 2025/05/08 13:52:29 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <mlx.h>
# include <math.h>
# include <stdlib.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

typedef struct t_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_game;

#endif