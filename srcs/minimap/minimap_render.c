/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* minimap_render.c                                   :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: pserre-s <priaserre@gmail.com>             +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/06/01 16:56:26 by ylebee            #+#    #+#             */
/* Updated: 2026/06/03 15:38:45 by pserre-s         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "Cub3d.h"

void draw_player(t_data *data)
{
	int px;
	int py;
	int i;
	int j;
	int len;

	px = data->player_x * data->coef_minimap;
	py = data->player_y * data->coef_minimap;
	i = 0;
	while (i < data->coef_player)
	{
		j = 0;
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
	len = data->coef_minimap * 2;
	i = 0;
	while (i < len)
	{
		ft_put_pixel(&data->img,
			px + (int)(data->dir_x * i),
			py + (int)(data->dir_y * i),
			0x00FF00);
		i++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
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
	int     i;
	int     j;
	int     max_width;
	t_data  *data;

	data = (t_data *)param;
	
	max_width = find_biggest(data->map.map_grid);
	
	i = 0;
	y = 0;
	while (data->map.map_grid[i] && y < HEIGHT)
	{
		j = 0;
		x = 0;
		while (j < max_width && x < WIDTH)
		{
			if (j < (int)ft_strlen(data->map.map_grid[i]) && data->map.map_grid[i][j] == '1')
				draw_square(data, x, y, 0xffffff);
			else if (j < (int)ft_strlen(data->map.map_grid[i]) && ft_strchr("0PNSEW", data->map.map_grid[i][j]))
				draw_square(data, x, y, 0x808080);
			else
				draw_square(data, x, y, 0x000000);
			j++;
			x += data->coef_minimap;
		}
		i++;
		y += data->coef_minimap;
	}
	draw_player(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

void ft_render_and_display(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L<<0, (int (*)())(void *)key_press, data);
	mlx_hook(data->win_ptr, 3, 1L<<1, (int (*)())(void *)key_release, data);
	mlx_hook(data->win_ptr, 17, 0, (int (*)())(void *)ft_exit, data);
	mlx_loop_hook(data->mlx_ptr, (int (*)())(void *)loop, data);
	mlx_loop(data->mlx_ptr);
}