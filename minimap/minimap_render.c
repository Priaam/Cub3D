/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:56:26 by ylebee            #+#    #+#             */
/*   Updated: 2026/06/02 20:24:34 by pserre-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void draw_player(t_mlx *data)
{
	int px;
	int py;
	//int len;
	int i;

	px = data->player_x * data->coef_minimap;
	py = data->player_y * data->coef_minimap;
	i = 0;
	while (i < data->coef_player)
	{
		int j = 0;
		while (j < data->coef_player)
		{
			ft_put_pixel(&data->img,
				px + j - data->coef_player / 2,
				py + i - data->coef_player / 2,
				0xff2c2c);
			j++;
		}
		i++;
	}
	// len = data->coef_minimap * 2;
	// i = 0;
	// while (i < len)
	// {
	// 	ft_put_pixel(&data->img,
	// 		px + (int)(data->dir_x * i), py + (int)(data->dir_y * i), 0x00FF00);
	// 	i++;
	// }
}

void	draw_square(t_mlx *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->coef_minimap)
	{
		j = 0;
		while (j < data->coef_minimap)
		{
			ft_put_pixel(&data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

int render(void *param)
{
	int     x;
	int     y;
	int     len;
	int     i;
	int     j;
	t_mlx   *data;
	t_dda   ray;

	data = (t_mlx *)param;
	i = 0;
	y = 0;
	while (data->map_grid[i] && y < HEIGHT)
	{
		len = ft_strlen(data->map_grid[i]);
		j = 0;
		x = 0;
		while (j < len && x < WIDTH)
		{
			if (data->map_grid[i][j] == '1')
				draw_square(data, x, y, 0xffffff);
			else
				draw_square(data, x, y, 0x808080);
			j++;
			x += data->coef_minimap;
		}
		i++;
		y += data->coef_minimap;
	}
	draw_player(data);
	dda(data, ray);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (0);
}

void ft_render_and_display(t_mlx *data)
{
	mlx_hook(data->win, 2, 1L<<0, (int (*)())(void *)key_press, data);
	mlx_hook(data->win, 3, 1L<<1, (int (*)())(void *)key_release, data);
	mlx_hook(data->win, 17, 0, (int (*)())(void *)ft_exit, data);
	mlx_loop_hook(data->mlx, (int (*)())(void *)loop, data);
	mlx_loop(data->mlx);
}